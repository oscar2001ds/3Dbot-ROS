#!/usr/bin/env python3

# ROS Node that handles the CNC Code parsing and publishes the required commands such as velocity and temperature to print a component.

# Importations.
from geometry_msgs.msg import Twist
from std_msgs.msg import Float32, Float64, Int16
from cnc.gcode import GCode, GCodeException
from cnc.coordinates import *
from math import sin, cos, pi, atan, acos
from threading import Thread
import threading
import cmath
import numpy as np

import sys
import rospy
import time
import os
        

class robot_control:
    def __init__(self):
        # Class constructor.
        # Initiliazise robot_control node with arguments from the command line.
        rospy.init_node('robot_control', anonymous=True, argv=sys.argv)

        # Set up publishers.
        self.velPub = rospy.Publisher('/cmd_vel', Twist, queue_size = 1)            # Velocity command for navigation.
        self.tempPub = rospy.Publisher('/cmd_extTemp', Int16, queue_size = 1)     # Extruder temperature command.
        self.zaxisPub = rospy.Publisher('cmd_zAxisPos', Float32, queue_size = 1)    # Z axis position command.
        self.powerStagePub = rospy.Publisher('/powerStage', Float32, queue_size = 1)
        self.E_distancePub = rospy.Publisher('/cmd_e_distance', Float32, queue_size = 1)

        #Arm
        self.joint1_arm = rospy.Publisher('/robot1/joint1_position_controller/command', Float32, queue_size=1)
        self.joint2_arm = rospy.Publisher('/robot1/joint2_position_controller/command', Float32, queue_size=1) 
        
        # Set up subscriber.
        self.tempSubs = rospy.Subscriber('/extTemp', Int16, callback=self.tempCallback)   # Actual extruder temperature.
        self.TargetReachedSub = rospy.Subscriber('/TargetReached',Float32,callback=self.TargetReachedCB)
     
        # Create message objects.
        self.velMsg = Twist()
        self.tempMsg = Int16() 
        self.zAxisPosMsg = Float32()
        self.TargetReachedMsg = Float32()
        self.E_distanceMsg = Float32()

        # Init class instances.
        self._position = Coordinates(0, 0, 0, 0)                        # TODO Replace with state estimator.
        self.extTemp = 0                                                # Extruder temperature, °C.
        self._velocity = 0                                              # Nozzle velocity, mm/sec.
        self._local = Coordinates(0.0, 0.0, 0.0, 0.0)                   # CNC code, local coordinates.
        self._convertCoordinates = 1.0                                  # CNC code, milimeters by default.
        self._absoluteCoordinates = True                                # CNC code, absolute coordinates, enabled by default.
        self._plane = None                                              # CNC code, plane.
        self.linnu = 0                                                  # Line counter.
                
        self.vx = 0
        self.vy = 0
        self.a = 0
        self.b = 1
        self.offset= 0
        self.offset2= 0
        self.J = 99

        self.l1arm = 225
        self.l2arm = 120

        self.dir = 0

        self.px_1 = self.l1arm+self.l2arm
        self.py_1 = 0

        self.E_distance = 0

    def powerStagePublisher(self, state):
        # powerStage commands publisher.
        self.powerStageMsg = Float32(state)
        self.powerStagePub.publish(self.powerStageMsg)

    def tempCallback(self, data):
        # Temperature callback function.
        self.extTemp = data.data

    def TargetReachedCB(self,data):
        self.TargetReachedMsg.data = data.data

        if data.data != float(1.0):
            print(abs(float(self.TargetReachedMsg.data)))

    def tempPublisher(self, temp):
        # Temperature publisher.
        self.tempMsg = temp
        self.tempPub.publish(self.tempMsg)

    def zAxisPosPublisher(self, pos):
        # Z axis position publisher.
        self.zAxisPosMsg = pos
        self.zaxisPub.publish(self.zAxisPosMsg)

    def EdistancePublisher(self, dis):
        # Extrusor distance publisher.
        self.E_distanceMsg = dis
        self.E_distancePub.publish(self.E_distanceMsg)

    def velPublisher(self, Vx, Vy):
        # Velocity publisher.
        self.velMsg.linear.x = Vx
        self.velMsg.linear.y = Vy
        self.velMsg.linear.z = 0

        self.velMsg.angular.x = 0
        self.velMsg.angular.y = 0
        self.velMsg.angular.z = 0

        self.velPub.publish(self.velMsg)
    
    def linearMovement(self, delta, velocity,coord,xaux,yaux):
        # Performs linear movements.

        if (xaux!=0 or yaux!=0):
            coorX=xaux
            coorY=yaux
            totalDist = cmath.sqrt(coorX**2+coorY**2)
            totalDist = totalDist.real
            #print(coorX)
            #print(coorY)
        else:
            coorX=delta.x
            coorY=delta.y
            distance = abs(delta)
            totalDist = distance.length()
            #print(delta)

        
        lin_time = totalDist/velocity
        velocity = velocity/1000

        if (coorX == 0):
            tetha = pi/2
        else:
            tetha = atan(abs(coorY)/abs(coorX))
            
        self.vx = velocity*cos(tetha)
        self.vy = velocity*sin(tetha)
        

        if (coorX >= 0 and coorY>= 0):
            self.vx = self.vx
            self.vy = self.vy
        elif (coorX < 0 and coorY >= 0):
            self.vx = -self.vx
            self.vy = self.vy
        elif (coorX < 0 and coorY < 0):
            self.vx = -self.vx
            self.vy = -self.vy
        elif (coorX >= 0 and coorY < 0):
            self.vx = self.vx
            self.vy = -self.vy

        self.velPublisher(self.vx,self.vy)

        self._position += delta

        time.sleep(lin_time)

        self.velPublisher(0,0)


    def armMovement(self, delta, coord, velocity,offset):

        px = coord.x+self.offset2
        py = coord.y-offset
        pz = coord.z

        l1 = self.l1arm
        l2 = self.l2arm

        if px == 0 or py == 0:
            px = self.px_1
            py = self.py_1

        print("px:",px)
        print("py:",py)
        print("pz:",pz)
        print("")

        tetha2 = cmath.acos((px**2+py**2-l1**2-l2**2)/(2*l1*l2))
        if px == 0:
            tetha1 = pi/2-cmath.atan((l2*cmath.sin(tetha2))/(l1+l2*cmath.cos(tetha2)))
        else:
            tetha1 = cmath.atan(py/px)-cmath.atan((l2*cmath.sin(tetha2))/(l1+l2*cmath.cos(tetha2)))

        #time.sleep(lin_time) 
        
        #print("Enviando coordenadas")
        # print("Tetha1:",tetha1.real*180/pi)
        # print("Tetha2:",tetha2.real*180/pi) 
        #event = threading.Event()

        # while (self.TargetReachedMsg.data!= float(2.0)): 
        #     print("Publicando...") 
        #     self.joint1_arm.publish(tetha1.real)
        #     time.sleep(0.001)
        #     self.joint2_arm.publish(tetha2.real)
        #     time.sleep(0.001)
        #     self.zaxisPub.publish(pz)
        #     time.sleep(0.001)

            #event.wait(0.5)
            #print("Target: ",float(int(self.TargetReachedMsg.data*10**n)/10**n))
            #print("Tetha: ", float(int(tetha1.real*10**n)/10**n))
            
        # print("Moviendo Brazo") 
        
        # a=abs(tetha1.real*180/pi+tetha2.real*180/pi)
        # print("Tetha1_2:",a)
        # ov=10
        # while (abs(self.TargetReachedMsg.data) < float(a-ov) or abs(self.TargetReachedMsg.data) > float(a+ov)): 
        #     #print("Publicando...") 
        #     self.joint1_arm.publish(tetha1.real)
        #     time.sleep(0.01)
        #     self.joint2_arm.publish(tetha2.real)
        #     time.sleep(0.01)
        #     self.zaxisPub.publish(pz)
        #     time.sleep(0.01)

        

        a=abs(tetha1.real*180/pi+tetha2.real*180/pi)
        print("Tetha1_2:",a)
            
        ts=0.01

        for num in range(1, 5, 1):
            self.joint1_arm.publish(tetha1.real)
            time.sleep(ts)
            self.joint2_arm.publish(tetha2.real)
            time.sleep(ts)
            self.zaxisPub.publish(pz)
            time.sleep(ts)
            self.EdistancePublisher(self.E_distance)
            time.sleep(ts)

        while (self.TargetReachedMsg.data != float(1.0)):
            time.sleep(0.000001)

        self.px_1 = px
        self.py_1 = py

        

    def gcodeReader(self, file, sim):
        # Read and publish CNC code lines.
        try:
            for line in file:
                line = line.strip()

                self.linnu += 1
                print(self.linnu)

                if not self.gcodeParser(line, sim):
                    break
            
        except (rospy.ROSInterruptException, KeyboardInterrupt):
            pass
        print("\r\nExiting...")

    def gcodeParser(self, line, sim):
        # Extract the data within the CNC code.
        try:
            gcode = GCode.parse_line(line)
            ans = self.gcodeCommands(gcode, sim)
        except (GCodeException) as e:
            print('ERROR ' + str(e))
            return False
        if ans is not None:
            print('OK ' + ans)
        else:
            print('OK')
        return True

    def gcodeCommands(self, gcode, sim):
        # Perform a CNC command, taken and modified from the method do_command of the GMachine class by Nikolay Khabarov.
        if gcode is None:
            return None
        answer = None

        # Read command.
        c = gcode.command()

        if c is None and gcode.has_coordinates():
            c = 'G1'

        # Read parameters.
        if self._absoluteCoordinates:
            coord = gcode.coordinates(self._position - self._local,
                                      self._convertCoordinates)
            coord = coord + self._local
            delta = coord - self._position

        else:
            delta = gcode.coordinates(Coordinates(0.0, 0.0, 0.0, 0.0),
                                      self._convertCoordinates)

        velocity = gcode.get('F', self._velocity)

        # Check that the velocity is within operation parameters.
        if velocity > 120:
            print("Maximum speed exceeded, maximum speed: 120 mm/sec.")
            self.velPublisher(0,0)
            sys.exit()

        radius = gcode.radius(Coordinates(0.0, 0.0, 0.0, 0.0),
                              self._convertCoordinates)

        if c == 'G0':  # Rapid move.
            self.linearMovement(delta,50,coord,0,0)
            #self.armMovement(delta, coord,120,0)

        elif c == 'G1':  # Linear interpolation.
            
           #self.linearMovement(delta, velocity,coord,0,0)
           self.armMovement(delta,coord,velocity,0)
            
        elif c == 'G2':  # Circular interpolation, clockwise.
            # TODO Implement.
            pass

        elif c == 'G3':  # Circular interpolation, counterclockwise.
            # TODO Implement.
            pass

        elif c == 'G4':  # Delay in seconds.
            if not gcode.has('P'):
                print("P is not specified")
                self.velPublisher(0,0)
                sys.exit()

            pause = gcode.get('P', 0)
            if pause < 0:
                print("bad delay")
                self.velPublisher(0,0)
                sys.exit()

            time.sleep(pause)

        elif c == 'G20':  # Switch to inches.
            self._convertCoordinates = 25.4

        elif c == 'G21':  # Switch to mm.
            self._convertCoordinates = 1.0

        elif c == 'G28':  # Home.
            pass

        elif c == 'G53':  # Switch to machine coordinates.
            self._local = Coordinates(0.0, 0.0, 0.0, 0.0)

        elif c == 'G90':  # Switch to absolute coordinates.
            self._absoluteCoordinates = True

        elif c == 'G91':  # Switch to relative coordinates.
            self._absoluteCoordinates = False

        elif c == 'G92':  # Switch to local coordinates.
            if gcode.has_coordinates():
                self._local = self._position - gcode.coordinates(
                    Coordinates(self._position.x - self._local.x,
                                self._position.y - self._local.y,
                                self._position.z - self._local.z,
                                self._position.e - self._local.e),
                    self._convertCoordinates)
            else:
                self._local = self._position

        elif c == 'M84':  # Disable motors.
            self.velPublisher(0,0)

        elif c == 'M114':  # Get current position.
            p = self.position()
            answer = "X:{} Y:{} Z:{} E:{}".format(p.x, p.y, p.z, p.e)
        
        # Extruder control.
        elif c == 'M104' or c == 'M109':
            if (sim == 1) or (sim == "true"):
                pass
            elif (sim == 0) or (sim == "false"):
                if not gcode.has_key('S'):
                    print("temperature is not specified")
                    self.velPublisher(0,0)
                    sys.exit()

                if c == 'M104':  
                    temp = gcode.get('S', 0)  
                    self.tempPub.publish(temp) #Set the hottend temperature in °C

                if c == 'M109': #Set the hottend temperature in °C and do nothing until reached 
                    temp = gcode.get('S', 0)  
                    self.tempPub.publish(temp)
                    print("Waiting for extruder to heat up.")
                    while(self.extTemp.data != temp):
                        pass                 

        elif c is None:  # Command not specified(ie just F was passed)
            pass
        
        # Save parameters on success.
        self._velocity = velocity
        return answer

if __name__ == "__main__":
    try:
        #Create an instance of the robot_control class.
        rc = robot_control()

        # Get arguments.
        args = rospy.myargv(argv=sys.argv)

        if len(args) < 2:
            print("\nERROR: no file provided.")
            sys.exit()
            
        file_path = args[1]
        sim = args[2]

        if (sim == 1) or (sim == "true"):
            print('\nSimulation only.')

        op = None
        while (op != "yes"):
            print("\n--------------------------------------")
            op = input("Are you ready to print? options: yes, no, exit: ")
            if (op == "exit"):
                sys.exit
        
    
        # print("\nEncenciendo Motores Plataforma")
        # rc.powerStagePublisher(1.0)
        # time.sleep(4)

        # print("\nEncenciendo Motores Brazo")
        # rc.powerStagePublisher(2.0)
        # time.sleep(4)

        print("\nPrinting file on: " + file_path) 
        file = open(file_path, 'r')
        rc.gcodeReader(file, sim)
        print("\nFile printed.")
        
        time.sleep(2)

        print("\nApagando Motores Plataforma")
        rc.powerStagePublisher(3.0)
        time.sleep(4)

        print("\nApagando Motores Brazo")
        rc.powerStagePublisher(4.0)
        time.sleep(4)
        
    except rospy.ROSInterruptException: 
        pass

