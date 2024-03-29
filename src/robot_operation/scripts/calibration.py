#!/usr/bin/env python3

from std_msgs.msg import Float32, Float64
import rospy
import time

class calibration:
    def __init__(self):       
        self.TargetReachedSub = rospy.Subscriber('/TargetReached',Float32,callback=self.TargetReachedCB)
        
        self.zaxisPub = rospy.Publisher('/cmd_zAxisPos', Float32, queue_size = 1)
        self.joint1_arm = rospy.Publisher('/robot1/joint1_position_controller/command', Float32, queue_size=10)
        self.joint2_arm = rospy.Publisher('/robot1/joint2_position_controller/command', Float32, queue_size=10) 
        self.powerStagePub = rospy.Publisher('/powerStage', Float32, queue_size = 1)

        self.TargetReachedMsg = Float32()
        self.zAxisPosMsg = Float32()
        self.xAxisPosMsg = Float32()
        self.yAxisPosMsg = Float32()
        self.powerStageMsg = Float32()
        

        self.calibrationOrder()

    def TargetReachedCB(self,data):
        self.TargetReachedMsg.data = data
        
    
    def calibrationOrder(self):
        time.sleep(4)
        print("\nEncenciendo Motores Plataforma")
        self.powerStageMsg = Float32(1.0)
        self.powerStagePub.publish(self.powerStageMsg)
        time.sleep(2)

        print("\nEncenciendo Motores Brazo")
        self.powerStageMsg = Float32(2.0)
        self.powerStagePub.publish(self.powerStageMsg)
        time.sleep(2)

        self.TargetReachedMsg.data = 0
        self.zAxisPosMsg.data = 999
        self.zaxisPub.publish(self.zAxisPosMsg)
        print("Calibrando eje Z")
        while (self.TargetReachedMsg.data != Float32(1.0)):
            # print("Calibrando eje Z")
            time.sleep(0.000001)
 
        self.TargetReachedMsg.data = 0
        self.xAxisPosMsg.data = 999
        self.joint1_arm.publish(self.xAxisPosMsg)
        print("Calibrando articulacion 1")
        while (self.TargetReachedMsg.data != Float32(1.0)):
            # print("Calibrando articulacion 1")
            # time.sleep(0.001)
            time.sleep(0.000001)
 
        self.TargetReachedMsg.data = 0
        self.yAxisPosMsg.data = 999
        self.joint2_arm.publish(self.yAxisPosMsg)
        print("Calibrando articulacion 2")
        while (self.TargetReachedMsg.data != Float32(1.0)):
            # print("Calibrando articulacion 2")
            # time.sleep(0.001)
            time.sleep(0.000001)



if __name__ == "__main__":
    rospy.init_node('calibration',anonymous=True)

    c = calibration()
    print("Calibracion Exitosa")
    