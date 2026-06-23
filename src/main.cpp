#include<Arduino.h>
#include<Wire.h>
#include<ESP32Servo.h>
#include<cmath>
#include<iostream>

const int theta_dir = 18;
const int theta_pwm = 19;
const int theta_ch = 0;

const int length_dir = 26;
const int length_pwm = 27;
const int length_ch =1;

const int height_pin = 13;//z方向は360サーボ
const int hand_pin = 14;

class MotorDrive{
public:
  int dirpin;
  int motorpwm;
  int pwmch;

  MotorDrive(int pin1,int pin2,int ch){
    dirpin=pin1;
    motorpwm=pin2;
    pwmch=ch;
  }

  void setup(){
    pinMode(dirpin,OUTPUT);
    pinMode(motorpwm,OUTPUT);
    ledcAttachPin(motorpwm,pwmch);
    ledcSetup(pwmch,12800,8);
  }
  void drive(int val){
    val = constrain(val,-255,255);
    if(val<0){
      digitalWrite(dirpin,HIGH);
      ledcWrite(pwmch,-val);
    }
    else if(val>0){
      digitalWrite(dirpin,LOW);
      ledcWrite(pwmch,val);
    }
    else{
      digitalWrite(dirpin,LOW);
      ledcWrite(pwmch,0);
    }
  }
};

MotorDrive theta_M{theta_dir,theta_pwm,theta_ch};
MotorDrive length_M{length_dir,length_pwm,length_ch};
Servo height_M, hand_servo;

void setup(){
  Serial.begin(115200);
  theta_M.setup();
  length_M.setup();
  height_M.attach(height_pin);
  hand_servo.attach(hand_pin);

  theta_M.drive(0);
  length_M.drive(0);
  height_M.write(90);
  hand_servo.write(90);
  delay(100);
}

void loop(){
  theta_M.drive(50);
  length_M.drive(50);
  height_M.write(120);
  hand_servo.write(120);
  delay(10);
}