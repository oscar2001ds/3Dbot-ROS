/*
 * 3drobot firmware.
 * 
 */

#define F_CPU 12000000
#define pi 3.1415926535897932384626433832795
#include <AccelStepper.h>

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int16.h>

// Voor de Arduino Mega + shield Ramps 1.4
#define MOTOR_X_STEP_PIN 54
#define MOTOR_X_DIR_PIN 55
#define MOTOR_X_ENABLE_PIN 38
 
#define MOTOR_Y_STEP_PIN 60
#define MOTOR_Y_DIR_PIN 61
#define MOTOR_Y_ENABLE_PIN 56
 
#define MOTOR_Z_STEP_PIN 46
#define MOTOR_Z_DIR_PIN 48
#define MOTOR_Z_ENABLE_PIN 62

#define X_ENDSTOP 3   /* X axis endstop input pin */
#define Y_ENDSTOP 14  /* Y axis endstop input pin */
#define Z_ENDSTOP 18  /* Z axis endstop input pin */

#define E_STEP_PIN 26
#define E_DIR_PIN 28
#define E_ENABLE_PIN 24

#define MOTOR_E_STEP_PIN 26
#define MOTOR_E_DIR_PIN 28
#define MOTOR_E_ENABLE_PIN 24


AccelStepper motorX(1, MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN); 
AccelStepper motorY(1, MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN); 
AccelStepper motorZ(1, MOTOR_Z_STEP_PIN, MOTOR_Z_DIR_PIN); 
AccelStepper motorE(1, MOTOR_E_STEP_PIN, MOTOR_E_DIR_PIN); 

int speedX=6400;
int speedY=6400;
int speedZ=6400;
int speedE=6400;

int targetX=0;
int targetY=0;
int targetZ=0;
int targetE=0;

float targetXpure=0;
float targetYpure=0;
float targetZpure=0;
String str;

unsigned char XendStop=0;
unsigned char YendStop=0;
unsigned char ZendStop=0;
unsigned char calcomp=0;

float microstep=1/32;

// Set up ROS node.
ros::NodeHandle  nh;

void xCB(const std_msgs::Float32& x_msg){
  targetX=(x_msg.data*180/pi)*4/(1.8*microstep);
  targetX=-targetX;
  targetXpure = x_msg.data*180/pi;

  if(x_msg.data==999){
      CalibrationX();
    }
}

void yCB(const std_msgs::Float32& y_msg){
  targetY=((y_msg.data*180/pi)*4/(1.8*microstep));
  targetY=-targetY+targetX;
  targetYpure = y_msg.data*180/pi;
  if(y_msg.data==999){
      CalibrationY();
    }
}

void zCB(const std_msgs::Float32& z_msg){
  targetZ=z_msg.data*(360/(1.8*microstep))/8;  // 8 milimetros de avance por vuelta, y como el paso del motor es de 1.8°.
                      // 8 mm de avance es igual a 200 pasos (360°/1.8). Si el paso del motor cambia
                      // será necesario dividir 360 entre el nuevo paso y reemplazar el 200 por este valor
  targetZpure = z_msg.data;
  if(z_msg.data==999){
      CalibrationZ();
    }
//  else{
//    goToTargetXYZE();
//  }
}

void eCB(const std_msgs::Int16& e_msg){
 
  targetE = (360*e_msg.data)/(1.8*microstep*11*pi); //11 es el diametro de la rueda de extrución
  goToTargetXYZE(); 
  }

// Set up subscibers.
ros::Subscriber<std_msgs::Float32> x_sub("/robot1/joint1_position_controller/command", &xCB);
ros::Subscriber<std_msgs::Float32> y_sub("/robot1/joint2_position_controller/command", &yCB);
ros::Subscriber<std_msgs::Float32> z_sub("/cmd_zAxisPos", &zCB);
ros::Subscriber<std_msgs::Int16> e_sub("/cmd_e_distance", &eCB);

// Set up publishers.
std_msgs::Float32 TargetReachedMsg;
ros::Publisher TargetReachedPub("/TargetReached", &TargetReachedMsg);



void setup() {

  Serial.begin(115200);
  nh.getHardware()->setBaud(115200);
  
  // Initialize ROS node.
  nh.initNode();
  
  // Advertise publishers.
  nh.advertise(TargetReachedPub);

  pinMode(MOTOR_X_STEP_PIN  , OUTPUT);
  pinMode(MOTOR_X_DIR_PIN    , OUTPUT);
  pinMode(MOTOR_X_ENABLE_PIN    , OUTPUT);

  pinMode(MOTOR_Y_STEP_PIN  , OUTPUT);
  pinMode(MOTOR_Y_DIR_PIN    , OUTPUT);
  pinMode(MOTOR_Y_ENABLE_PIN    , OUTPUT);

  pinMode(MOTOR_Z_STEP_PIN  , OUTPUT);
  pinMode(MOTOR_Z_DIR_PIN    , OUTPUT);
  pinMode(MOTOR_Z_ENABLE_PIN    , OUTPUT);
  
  pinMode(MOTOR_E_STEP_PIN  , OUTPUT);
  pinMode(MOTOR_E_DIR_PIN    , OUTPUT);
  pinMode(MOTOR_E_ENABLE_PIN    , OUTPUT);
  
  digitalWrite(MOTOR_X_ENABLE_PIN    , LOW);
  digitalWrite(MOTOR_Y_ENABLE_PIN    , LOW);
  digitalWrite(MOTOR_Z_ENABLE_PIN    , LOW);

  
  motorX.setMaxSpeed(10000);
  motorX.setSpeed(speedX);
  motorX.setCurrentPosition(0);
  
  motorY.setMaxSpeed(10000);
  motorY.setSpeed(speedY);
  motorY.setCurrentPosition(0);
 
  motorZ.setMaxSpeed(10000);
  motorZ.setSpeed(speedZ);
  motorZ.setCurrentPosition(0);
  
  motorE.setMaxSpeed(10000);
  motorE.setSpeed(speedE);
  motorE.setCurrentPosition(0);
  
  pinMode(X_ENDSTOP, INPUT_PULLUP);
  pinMode(Y_ENDSTOP, INPUT_PULLUP);
  pinMode(Z_ENDSTOP, INPUT_PULLUP);

  nh.subscribe(x_sub); 
  nh.subscribe(y_sub); 
  nh.subscribe(z_sub);  
  nh.subscribe(e_sub);
}
 
void loop() {
  nh.spinOnce();    
}

void CalibrationX(){
  
    XendStop=digitalRead(X_ENDSTOP);
    while(XendStop==1){ 
      XendStop=digitalRead(X_ENDSTOP);  
      motorX.setSpeed(-speedX);
      motorX.runSpeed(); 
      motorX.setCurrentPosition(0);
      TargetReachedMsg.data = 0;
    }
        
    TargetReachedMsg.data = 1;
    TargetReachedPub.publish( &TargetReachedMsg );
    TargetReachedMsg.data = 0;
    TargetReachedPub.publish( &TargetReachedMsg );
}

void CalibrationY(){
  
    YendStop=digitalRead(Y_ENDSTOP);
    while(YendStop==1){ 
      YendStop=digitalRead(Y_ENDSTOP);  
      motorY.setSpeed(speedY);
      motorY.runSpeed(); 
      motorY.setCurrentPosition(0);
      TargetReachedMsg.data = 0;
    }
        
    TargetReachedMsg.data = 1;
    TargetReachedPub.publish( &TargetReachedMsg );
    TargetReachedMsg.data = 0;
    TargetReachedPub.publish( &TargetReachedMsg );

    targetX=90*4/1.8;
    targetY=(-150*4/1.8)+targetX;
    goToTargetXYZE();

    motorX.setCurrentPosition(0);
    motorY.setCurrentPosition(0);
}
  
void CalibrationZ(){
  
  ZendStop=digitalRead(Z_ENDSTOP);
    while(ZendStop==1){ 
      ZendStop=digitalRead(Z_ENDSTOP);  
      motorZ.setSpeed(-speedZ);
      motorZ.runSpeed(); 
      motorZ.setCurrentPosition(0);
      TargetReachedMsg.data = 0;
    }
    
    TargetReachedMsg.data = 1;
    TargetReachedPub.publish( &TargetReachedMsg );
    TargetReachedMsg.data = 0;
    TargetReachedPub.publish( &TargetReachedMsg );
}

void goToTargetXYZE(){

  TargetReachedMsg.data = targetXpure+targetYpure;
  TargetReachedPub.publish( &TargetReachedMsg );
//  TargetReachedMsg.data = targetYpure;
//  TargetReachedPub.publish( &TargetReachedMsg );
//  TargetReachedMsg.data = targetZpure;
//  TargetReachedPub.publish( &TargetReachedMsg );
//  TargetReachedMsg.data = 2;
//  TargetReachedPub.publish( &TargetReachedMsg );
  
  while(motorX.currentPosition()!=targetX || motorY.currentPosition()!=targetY || motorZ.currentPosition()!=targetZ || motorE.currentPosition()!=targetE){
    
    if (motorX.currentPosition()==targetX){
      motorX.setSpeed(0);
      motorX.runSpeed(); 
    }
    else if (motorX.currentPosition()<targetX){
      motorX.setSpeed(speedX);
      motorX.runSpeed(); 
    }
    else if(motorX.currentPosition()>targetX){
      motorX.setSpeed(-speedX);
      motorX.runSpeed();
    }

    if (motorY.currentPosition()==targetY){
      motorY.setSpeed(0);
      motorY.runSpeed(); 
    }
    else if (motorY.currentPosition()<targetY){
      motorY.setSpeed(speedY);
      motorY.runSpeed(); 
    }
    else if(motorY.currentPosition()>targetY){
      motorY.setSpeed(-speedY);
      motorY.runSpeed();
    }
    
    if (motorZ.currentPosition()==targetZ){
      motorZ.setSpeed(0);
      motorZ.runSpeed(); 
    }
    else if (motorZ.currentPosition()<targetZ){
      motorZ.setSpeed(speedZ);
      motorZ.runSpeed(); 
    }
    else if(motorZ.currentPosition()>targetZ){
      motorZ.setSpeed(-speedZ);
      motorZ.runSpeed();
    }

    if (motorE.currentPosition()==targetE){
      motorE.setSpeed(0);
      motorE.runSpeed(); 
    } 
    else if (motorE.currentPosition()<targetE){
      motorE.setSpeed(speedE);
      motorE.runSpeed(); 
    }
    else if(motorE.currentPosition()>targetE){
      motorE.setSpeed(-speedE);
      motorE.runSpeed();
    }
  } 

  
  TargetReachedMsg.data = 1;
  TargetReachedPub.publish( &TargetReachedMsg );
//  TargetReachedMsg.data = 0;
//  TargetReachedPub.publish( &TargetReachedMsg );
//  
}


  
