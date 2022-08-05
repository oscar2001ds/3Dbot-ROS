
 
/*
 * 3drobot firmware.
 * 
 */
 
#define F_CPU 12000000
#define pi 3.1415926535897932384626433832795

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include <AccelStepper.h>

#define X_STEP_PIN         A0
#define X_DIR_PIN          A1
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         A6
#define Y_DIR_PIN          A7
#define Y_ENABLE_PIN       A2
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       A8
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24

#define PWM_pin            10
#define termistorPin A13
#define termistorNominalRes 100000
#define termistorNominalTemp 25
#define termistorBValue 3950
#define VoltageDividerResistor 4700 // configurar el valor de la resistencia que va en serie con el termistor NTC en ohms

//PID
float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;


int kp = 90;   int ki = 30;   int kd = 80;
int PID_p = 0;    int PID_i = 0;    int PID_d = 0;
int PID_value = 0;

// Define stepper motors connection pins (Type:driver, STEP, DIR).
AccelStepper LeftFrontWheel(1, E_STEP_PIN, E_DIR_PIN);  // Stepper1
AccelStepper LeftBackWheel(1, Z_STEP_PIN, Z_DIR_PIN);   // Stepper2
AccelStepper RightBackWheel(1, Y_STEP_PIN, Y_DIR_PIN);  // Stepper3
AccelStepper RightFrontWheel(1, X_STEP_PIN, X_DIR_PIN); // Stepper4
//AccelStepper Zaxis(1, Z_STEP_PIN, Z_DIR_PIN);                           // Stepper5. 

// Global variables.
int wheelSpeed = 0, contseg = 0, cont = 1, load = 0;
int r = 42;                                                                 // Wheel radius.r
int thermistorPin = A13;

float vX = 0, vY = 0;                                                       // Linear speed [m/s].
float vA = 0;                                                               // Angular speed [rad/s].
float stepDelay = 0.005;                                                     // Stepper motor step delay [seconds].
float cmdExtTemp = 0, extTemp = 0;                                          // Command extruder temperature and actual value [°C].

float a1 = pi/4, a2 = 3*pi/4, a3 = 5*pi/4, a4 = 7*pi/4, w = pi, R = 181.07; // Kinematics parameters.
float v1 = 0, v2 = 0, v3 = 0, v4 = 0;                                       //Wheel angular speed [rad/s].
float vs1 = 0, vs2 = 0, vs3 = 0, vs4 = 0;                                   //Wheel angular speed [step/s].

unsigned long timeNow = 0;
int period = stepDelay*1000;
float microstep=1/32;


// Set up ROS node.
ros::NodeHandle  nh;

// Callback functions.
void velocityCB(const geometry_msgs::Twist& vel_msg){
  vX = vel_msg.linear.x*1000;
  vY = vel_msg.linear.y*1000;
}

void temperatureCB(const std_msgs::Float32& temp_msg){
  cmdExtTemp = temp_msg.data;
}

// Set up subscibers.
ros::Subscriber<geometry_msgs::Twist> vel_sub("/cmd_vel", &velocityCB);
ros::Subscriber<std_msgs::Int16> temp_sub("/cmd_extTemp", &temperatureCB);
//
//// Set up publishers.
std_msgs::Float32 extTempMsg;
ros::Publisher extTempPub("/extTemp", &extTempMsg);

void setup(){
  // Set up baud rate.
  Serial.begin(115200);
  nh.getHardware()->setBaud(115200);

  // Pin configuration.
  
  pinMode(X_STEP_PIN  , OUTPUT);
  pinMode(X_DIR_PIN    , OUTPUT);
  pinMode(X_ENABLE_PIN    , OUTPUT);

  pinMode(Y_STEP_PIN  , OUTPUT);
  pinMode(Y_DIR_PIN    , OUTPUT);
  pinMode(Y_ENABLE_PIN    , OUTPUT);

  pinMode(Z_STEP_PIN  , OUTPUT);
  pinMode(Z_DIR_PIN    , OUTPUT);
  pinMode(Z_ENABLE_PIN    , OUTPUT);

  pinMode(E_STEP_PIN  , OUTPUT);
  pinMode(E_DIR_PIN    , OUTPUT);
  pinMode(E_ENABLE_PIN    , OUTPUT);

  pinMode(PWM_pin, OUTPUT);
  pinMode(termistorPin, INPUT);
  
  digitalWrite(X_ENABLE_PIN    , LOW);
  digitalWrite(Y_ENABLE_PIN    , LOW);
  digitalWrite(Z_ENABLE_PIN    , LOW);
  digitalWrite(E_ENABLE_PIN    , LOW);

  // Initialize ROS node.
  nh.initNode();

  // Advertise publishers.
  //nh.advertise(extTempPub);

  // Set maximum speeds per motor.
  LeftFrontWheel.setMaxSpeed(15000);
  LeftBackWheel.setMaxSpeed(15000);
  RightBackWheel.setMaxSpeed(15000);
  RightFrontWheel.setMaxSpeed(15000);
}

void loop(){
  // Subscribe from /cmd_vel and /cmd_extTemp.
  nh.subscribe(vel_sub);
  nh.subscribe(temp_sub);

  //heat the hottend
  while(vX==0 && vY==0){
    hottendProcess();
    nh.spinOnce();
    }
  
  
  // Move the robot..
  calculateSpeeds();
  timeNow = millis();
  
  while (millis() < timeNow + period){
    setExSpeeds();
  }
  
  nh.spinOnce();
}

void hottendProcess(){   
  // Get extruder temperature and publish it in /extTemp.
  extTemp = readHottendTemperature();
  extTempMsg.data = extTemp;
  extTempPub.publish(&extTempMsg);
   
  PID_error = cmdExtTemp - extTemp;

  PID_p = 0.01*kp * PID_error;
  PID_i = 0.01*PID_i + (ki * PID_error);

  timePrev = Time;
  Time = millis();
  elapsedTime = (Time - timePrev) / 1000; 
  PID_d = 0.01*kd*((PID_error - previous_error)/elapsedTime);

  PID_value = PID_p + PID_i + PID_d;
  
  if(PID_value < 0){
    PID_value = 0;    
    }
  if(PID_value > 255){    
    PID_value = 255;  
    }
  
  analogWrite(PWM_pin,PID_value);
  previous_error = PID_error; 
  //delay(250);
  }

int readHottendTemperature(){
  int temperature;
  int Temp = analogRead(termistorPin);
  float resistencia = VoltageDividerResistor / ((1023.0 / Temp) - 1);
  float steinhart;
  //Steinhart–Hart equation with B parameter 
  steinhart = resistencia  / termistorNominalRes;     // (R/Ro)
  steinhart = log(steinhart);                         // ln(R/Ro)
  steinhart /= termistorBValue;                       // 1/B * ln(R/Ro)
  steinhart += 1.0 / (termistorNominalTemp + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                        // Invert  
  steinhart -= 273.15;     
  temperature = steinhart;
  return temperature;
  }
void calculateSpeeds() {
  // Calculate angular speed per wheel in rad/s.
  v1=(-sin(w+a1)*vX+cos(w+a1)*vY+R*vA)/r;
  v2=(-sin(w+a2)*vX+cos(w+a2)*vY+R*vA)/r;
  v3=(-sin(w+a3)*vX+cos(w+a3)*vY+R*vA)/r;
  v4=(-sin(w+a4)*vX+cos(w+a4)*vY+R*vA)/r;

  // Obtain angular speed in step/s.
  vs1= v1*100/microstep;
  vs2= v2*100/microstep;
  vs3= v3*100/microstep;
  vs4= v4*100/microstep;
  
  if(abs(vs1)>15000|abs(vs2)>15000|abs(vs3)>15000|abs(vs4)>15000){
    vs1= 0;
    vs2= 0;
    vs3= 0;
    vs4= 0;
  }
 }
 
void setExSpeeds() {
  LeftFrontWheel.setSpeed(vs1);
  LeftFrontWheel.runSpeed();
  LeftBackWheel.setSpeed(vs2);
  LeftBackWheel.runSpeed();
  RightBackWheel.setSpeed(vs3);
  RightBackWheel.runSpeed();
  RightFrontWheel.setSpeed(vs4);
  RightFrontWheel.runSpeed();
}

void stopMoving() {
  LeftFrontWheel.setSpeed(0);
  LeftFrontWheel.runSpeed();
  LeftBackWheel.setSpeed(0);
  LeftBackWheel.runSpeed();
  RightBackWheel.setSpeed(0);
  RightBackWheel.runSpeed();
  RightFrontWheel.setSpeed(0);
  RightFrontWheel.runSpeed();
}
