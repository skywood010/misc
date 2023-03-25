#include <Servo.h>
#include <IRremote.h>

int echoPin=7;
int trigPin=6;
int pingTravelTime;

float pingTravelDistance;

float distanceToTarget;
float resultDistance;
float leftDistance;
float rightDistance;

int receiverPin=4;

int servoPin=13;
int servoVal;

String myCom;
int dt;

int Speed=255;

int enA=3;
int in1=9;
int in2=8;

int enB=12;
int in3=11;
int in4=10;

int dir1=1;
int dir2=1;

IRrecv IR(receiverPin);
decode_results cmd;
Servo Xservo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);
  pinMode(receiverPin, INPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Xservo.attach(servoPin);
  IR.enableIRIn();
}

void loop() {

    float resultDistance = distanceControl();
    if (resultDistance >= 50) {
      myCom = "rev";
    } else {
      myCom = "stop";
    }

    if (myCom=="stop") {
      motorControl(0, 0, 0, 0);

      servoControl();

      if (leftDistance > rightDistance) {
        myCom = "left";
      }
      if (leftDistance < rightDistance) {
        myCom = "right";
      }
    }

    delay(1000);

    

    
    

//  Xservo.write(50);
//  Serial.println("Left distance is ");
//  distanceControl();
//  delay(1000);
//  
//  Xservo.write(130);
//  Serial.println("Right distance is ");
//  distanceControl();
//  delay(1000);
//
//  Xservo.write(90);
//  Serial.println("Center distance is ");
//  distanceControl();
//  delay(1000);

  //servoControl();

//  while (IR.decode(&cmd) == 0) {  
//  }

//  Serial.println(cmd.value, HEX);
//  delay(100);
//  IR.resume();

  //irControl();
  

  


//commands

  
  
//drive directions

  //default forward
  if (myCom=="zero") {
    motorControl(255, 255, 1, 1);
  }

  //stop
  if (myCom=="stop") {
    motorControl(0, 0, 0, 0);
  }

  //move forward
  if (myCom=="fwd") {
    motorControl(255, 255, 1, 1);
  }

  //move backward
  if (myCom=="rev") {
    motorControl(255, 255, 0, 0);

  }

  //decrease speed
//  if (myCom=="vol-") {
//    Speed -= 10;
//    if (Speed <= 200) {
//      Speed = 0;
//    }
//    analogWrite(enA, Speed);
//    analogWrite(enB, Speed);
//
//  }
//
//  //increase speed
//  if (myCom=="vol+") {
//    Speed += 10;
//    if (Speed >= 255) {
//      Speed=255;
//    }
//    analogWrite(enA, Speed);
//    analogWrite(enB, Speed);
//
//  }

  //left
  if (myCom=="left") {
    motorControl(255, 255, 1, 0);

  }

  //right
  if (myCom=="right") {
    motorControl(255, 255, 0, 1);
    
  }

}

void motorControl(int SpeedA, int SpeedB, int dir1, int dir2) {
  digitalWrite(in1, dir1);
  digitalWrite(in2, !dir1);
  digitalWrite(in3, dir2);
  digitalWrite(in4, !dir2);
  
  analogWrite(enA, SpeedA);
  analogWrite(enB, SpeedB);

  if (dir1 == dir2) {
    dt = 1000;
  } else {
    dt = 700;
  }

  delay(dt);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);

//  IR.resume();
//  delay(100);
}

void irControl() {
  if (cmd.value==0xFF10EF){
    myCom="left";
    Serial.println(myCom); 
  }

  if (cmd.value==0xFF5AA5){
    myCom="right";
    Serial.println(myCom); 
  }

  if (cmd.value==0xFF22DD) {
    myCom="rev";
    Serial.println(myCom);
  }
  
  if (cmd.value==0xFF02FD) {
    myCom="fwd";
    Serial.println(myCom);
  }

  if (cmd.value==0xFF6897) {
    myCom="zero";
    Serial.println(myCom);
  }
  
  if (cmd.value==0xFF30CF) {
    myCom="one";
    Serial.println(myCom);
  }

  if (cmd.value==0xFFE01F) {
    myCom="vol-";
    Serial.println(myCom);
  }

  if (cmd.value==0xFFA857) {
    myCom="vol+";
    Serial.println(myCom);
  }
}

void servoControl() {
  Xservo.write(50);
  leftDistance = distanceControl();
  delay(1000);

  Xservo.write(130);
  rightDistance = distanceControl();
  delay(1000);

  servoVal = 90;
  Xservo.write(servoVal);
  
}

float distanceControl() {
  distanceToTarget = 0;
  
  for (int a=0; a<3; a++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pingTravelTime = pulseIn(echoPin, HIGH);
    delay(25);
    
    distanceToTarget += pingTravelTime/40;
    delay(50);
  }
  

  Serial.println(String(distanceToTarget/3));
  return distanceToTarget;
  
}
