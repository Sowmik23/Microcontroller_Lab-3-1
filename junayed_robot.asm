#include<Servo.h>
Servo servo1;
int servo_round;
int flag=0;
int trig=3;
int echo=2;
int servo_angle=4;

int IN1=6;
int IN2=7;
int IN3=8;
int IN4=9;
int ENA1=5;
int ENA2=10;
int LEFT_SPEED;
int RIGHT_SPEED;
int led=12;
int cnt =0;
long duration,distance;
int car_stat=1;

void control_servo(){
   servo1.write(servo_angle);
  
   
   if(flag==0) {
    servo_angle+=10;
    if(servo_angle>90) flag=1;
   }
   if(flag==1) {
    servo_angle-=10;
    if(servo_angle<10) flag=0;
   }
}

void forward(){
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
   analogWrite(ENA1,255);
   analogWrite(ENA2,255);
   LEFT_SPEED=255;
   RIGHT_SPEED=255;
}

void back(){
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   analogWrite(ENA1,150);
   analogWrite(ENA2,150);
   LEFT_SPEED=150;
   RIGHT_SPEED=150;
}
void left(){
  forward();
  analogWrite(ENA1,255);
  analogWrite(ENA2,50);
  LEFT_SPEED=255;
   RIGHT_SPEED=50;
}

void right(){
  forward();
  analogWrite(ENA1,50);
  analogWrite(ENA2,255);
  LEFT_SPEED=50;
   RIGHT_SPEED=255;
}

void stop(){
  analogWrite(ENA1,0);
  analogWrite(ENA2,0);
  LEFT_SPEED=0;
  RIGHT_SPEED=0;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo1.attach(4);
  
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(12,OUTPUT);
  stop();
}

void speedUp(){
  if(LEFT_SPEED<205)LEFT_SPEED+=50;
  else LEFT_SPEED=255;
  if(RIGHT_SPEED<205)LEFT_SPEED+=50;
  else RIGHT_SPEED=255;
  
}

void speedDown(){
  if(LEFT_SPEED>50)LEFT_SPEED-=50;
  else LEFT_SPEED=0;

  if(RIGHT_SPEED>50)RIGHT_SPEED-=50;
  else RIGHT_SPEED=0;
  
}

void stopcar(){
  digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   analogWrite(ENA1,0);
   analogWrite(ENA2,0);
  LEFT_SPEED=0;
  RIGHT_SPEED=0;
}


void response_to_sonar(){
  
  digitalWrite(trig,HIGH);
  delayMicroseconds(100);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=(duration/2)/29.1;

  if(servo_angle>=40 and servo_angle<=45 and distance <20 and car_stat==1){
    stopcar();
    car_stat=0;
    
  }

  if(car_stat==0 and servo_angle >=80 and distance >30){
    right();
    delay(1000);
    forward();
    car_stat=1;
  }
  else if(car_stat==0 and servo_angle <=30 and distance >30){
    left();
    delay(1000);
    forward();
    car_stat=1;
  }
  Serial.print(distance);
  Serial.println("");
  delay(10);
  
}

void loop() {
  // put your main code here, to run repeatedly:
 // Serial.println("hi");
  cnt++;
  response_to_sonar();
  control_servo();
  if(Serial.available()){
    
    
    char data=Serial.read();
    if(data=='f')forward();
    if(data=='l')left();
    if(data=='b')back();
    if(data=='r')right();
    if(data=='u')speedUp();
    if(data=='d')speedDown();
    if(data=='s')stopcar();
    digitalWrite(12,HIGH);
  }
  delay(100);
  digitalWrite(12,LOW);
}
