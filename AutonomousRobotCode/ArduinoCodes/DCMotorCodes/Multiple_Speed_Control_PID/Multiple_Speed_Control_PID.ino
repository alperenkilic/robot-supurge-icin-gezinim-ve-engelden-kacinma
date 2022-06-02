// https://github.com/curiores/ArduinoTutorials
 
#include <util/atomic.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//Pins

// Motor 1
#define ENCA 2
#define ENCB 3
#define PWM 6
#define IN1 8
#define IN2 9

// Motor 2
#define ENCA2 3
#define ENCB2 4
#define PWM2 11
#define IN3 10
#define IN4 12

/////////////////////////////////////////////////////////////////////////////////////////////////////
//Globals

//Motor 1
long prevT = 0;
int posPrev = 0;
volatile int pos_i = 0;
volatile float velocity_i = 0;
volatile long prevT_i = 0;
float v1Filt = 0;
float v1Prev = 0;
float v2Filt = 0; 
float v2Prev = 0;
float eintegral = 0;

//Motor 2
long prevT2 = 0;
int posPrev2 = 0;
volatile int pos_i2 = 0;
volatile float velocity_i2 = 0;
volatile long prevT_i2 = 0;
float v1Filt2 = 0;
float v1Prev2 = 0;
float v2Filt2 = 0; 
float v2Prev2 = 0;
float eintegral2 = 0;


/////////////////////////////////////////////////////////////////////////////////////////////////////
//Setup

void setup() {
  Serial.begin(19200);

  // Motor 1
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  pinMode(PWM,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  // Motor 2
  pinMode(ENCA2,INPUT);
  pinMode(ENCB2,INPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCA),
                  readEncoder,RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA2),
                  readEncoder2,RISING);          
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//Loop

void loop() {

  //Motor 1
  //Read the position in an atomic block to avoid potential misreads
  
  int pos = 0;
  float velocity2 = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    pos = pos_i;
    velocity2 = velocity_i;
  }

  //Compute Velocity with method 1
  
  long currT = micros();
  float deltaT = ((float) (currT-prevT))/1.0e6;
  float velocity1 = (pos - posPrev)/deltaT;
  posPrev = pos;
  prevT = currT;

  //Convert count/s to RPM
  
  float v1 = velocity1/374.0*60.0;
  float v2 = velocity2/374.0*60.0;

  // Low-pass filter (25 Hz cutoff)
  v1Filt = 0.854*v1Filt + 0.0728*v1 + 0.0728*v1Prev;
  v1Prev = v1;
  v2Filt = 0.854*v2Filt + 0.0728*v2 + 0.0728*v2Prev;
  v2Prev = v2;

  //Target
  //float vt = 100*(sin(currT/1e6)>0);
  float vt = 100;

  // Compute the control signal u
  float kp = 5;
  float ki = 10;
  float e = vt-v1Filt;
  eintegral = eintegral + e*deltaT;
  
  float u = kp*e + ki*eintegral;

  // Set the motor speed and direction
  int dir = 1;
  if (u<0){
    dir = -1;
  }
  int pwr = (int) fabs(u);
  if(pwr > 255){
    pwr = 255;
  }


  /////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //Read the position in an atomic block to avoid potential misreads
  //Motor 2
  
  int pos2 = 0;
  float velocity22 = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    pos2 = pos_i2;
    velocity22 = velocity_i2;
  }

  //Compute Velocity with method 1
  long currT2 = micros();
  float deltaT2 = ((float) (currT2-prevT2))/1.0e6;
  float velocity12 = (pos2 - posPrev2)/deltaT2;
  posPrev2 = pos2;
  prevT2 = currT2;

  // Convert count/s to RPM
  float v3 = velocity12/374.0*60.0;
  float v4 = velocity22/374.0*60.0;

  // Low-pass filter (25 Hz cutoff)
  v1Filt2 = 0.854*v1Filt2 + 0.0728*v3 + 0.0728*v1Prev2;
  v1Prev2 = v3;
  v2Filt2 = 0.854*v2Filt2 + 0.0728*v4 + 0.0728*v2Prev2;
  v2Prev2 = v4;

  // Set a target
  //float vt2 = 100*(sin(currT2/1e6)>0);
  float vt2 = -100;

  // Compute the control signal u
  float kp2 = 5;
  float ki2 = 10;
  float e2 = vt2-v1Filt2;
  eintegral2 = eintegral2 + e2*deltaT2;
  
  float u2 = kp2*e2 + ki2*eintegral2;

  // Set the motor speed and direction
  int dir2 = 1;
  if (u2<0){
    dir2 = -1;
  }
  int pwr2 = (int) fabs(u2);
  if(pwr2 > 255){
    pwr2 = 255;
  }

  setMotor(dir,pwr,PWM,IN1,IN2);
  setMotor2(dir2,pwr2,PWM2,IN3,IN4);

//
  Serial.println("Motor 1");
  Serial.println(v2);
  delay(1);

  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Motor 1

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal);
  if(dir == 1){ 
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);    
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Motor 1

void readEncoder(){
  // Read encoder B when ENCA rises
  int b = digitalRead(ENCB);
  int increment = 0;
  if(b>0){
    // If B is high, increment forward
    increment = 1;
  }
  else{
    // Otherwise, increment backward
    increment = -1;
  }
  pos_i = pos_i + increment;

  // Compute velocity with method 2
  long currT = micros();
  float deltaT = ((float) (currT - prevT_i))/1.0e6;
  velocity_i = increment/deltaT;
  prevT_i = currT;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Motor 2

void setMotor2(int dir2, int pwmVal2, int pwm2, int in3, int in4){
  analogWrite(pwm2,pwmVal2);
  if(dir2 == 1){ 
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
  }
  else if(dir2 == -1){
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
  }
  else{
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);    
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Motor 2

void readEncoder2(){
  // Read encoder B when ENCA rises
  int b2 = digitalRead(ENCB2);
  int increment2 = 0;
  if(b2>0){
    // If B is high, increment forward
    increment2 = 1;
  }
  else{
    // Otherwise, increment backward
    increment2 = -1;
  }
  pos_i2 = pos_i2 + increment2;

  // Compute velocity with method 2
  long currT2 = micros();
  float deltaT2 = ((float) (currT2 - prevT_i2))/1.0e6;
  velocity_i2 = increment2/deltaT2;
  prevT_i2 = currT2;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
