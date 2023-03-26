#include <Servo.h>

//distance detector
int echoPin=7;
int trigPin=6;
int pingTravelTime;
float pingTravelDistance;

float distanceToTarget;
float resultDistance;
float leftDistance;
float rightDistance;
float fwdDistance;

int servoPin=13;
int servoVal;

String command;
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

Servo Xservo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Xservo.attach(servoPin);
}

void loop() {
  
  //reading input from serial monitor
  if (Serial.available() > 0) {
    command = Serial.read();
  }
  
  if (command != "fwd" {
    motorControl(255, 255, 1, 0);
    delay(500);
  }
  
  if (command = "fwd") {
    motorControl(255, 255, 1, 1);
  } else {
    pass;
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

}

void autoMovement() {
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

}

void servoControl() {
  Xservo.write(50);
  leftDistance = distanceControl();
  delay(1000);

  Xservo.write(130);
  rightDistance = distanceControl();
  delay(1000);

  servoVal = 90;
  fwdDistance = distanceControl();
  delay(1000);
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
  

