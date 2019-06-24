#include<Servo.h>
Servo servo1;
int servo_round;
int MODE=0;
int flag=1;
int trig=3;
int echo=2;
int depthTrig=13;
int depthEcho=12;
int servo_angle=10;
int mn=12344;
int IN1=6;
int IN2=7;
int IN3=8;
int IN4=9;
int ENA1=5;
int ENA2=10;
int LEFT_SPEED=200;
int RIGHT_SPEED=200;
int led=36;
int cnt =0;
int SHOOT=11;
int ara[200];
long duration,distance;
int car_stat=1;
bool isn=true;

void control_servo(){
   servo1.write(servo_angle);
  
   
   if(flag==0) {
    servo_angle+=10;
    if(servo_angle>90) {
      flag=1;
      mn=12345;
    }
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
   LEFT_SPEED=200;
   RIGHT_SPEED=200;
   analogWrite(ENA1,LEFT_SPEED);
   
   analogWrite(ENA2,RIGHT_SPEED);
  
}

void back(){
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   analogWrite(ENA1,200);
   analogWrite(ENA2,200);
   LEFT_SPEED=200;
   RIGHT_SPEED=200;
  
}
void left(){
  forward();
  analogWrite(ENA1,200);
  analogWrite(ENA2,50);
  LEFT_SPEED=200;
  RIGHT_SPEED=20;
 
}

void right(){
  forward();
  analogWrite(ENA1,20);
  analogWrite(ENA2,200);
  LEFT_SPEED=20;
  RIGHT_SPEED=200;
  
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
  pinMode(12,INPUT);
  pinMode(11,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(36,OUTPUT);
  
  stop();
}

void speedUp(){
  if(LEFT_SPEED<205)LEFT_SPEED+=50;
  else LEFT_SPEED=255;
  if(RIGHT_SPEED<205)LEFT_SPEED+=50;
  else RIGHT_SPEED=255;
  
  analogWrite(ENA1,LEFT_SPEED);
  analogWrite(ENA2,RIGHT_SPEED);
}

void speedDown(){
  if(LEFT_SPEED>50)LEFT_SPEED-=50;
  else LEFT_SPEED=0;

  if(RIGHT_SPEED>50)RIGHT_SPEED-=50;
  else RIGHT_SPEED=0;
  
  analogWrite(ENA1,LEFT_SPEED);
  analogWrite(ENA2,RIGHT_SPEED);
  
}

bool response_to_sonar2(){
  Serial.println("sonar2");
  digitalWrite(depthTrig,HIGH);
  delayMicroseconds(100);
  digitalWrite(depthTrig,LOW);
  duration=pulseIn(depthEcho,HIGH);
  distance=(duration/2)/29.1;
  Serial.println("depth:");
  Serial.println(distance);
  Serial.println("end");
  
  if(distance>30){
    if(isn)stop();
    isn=false;
    
    back();
    delay(2000);
    right();
    delay(2000);
    forward();
    return true;
    
  }
  else{
    isn=true;
  }
 return false;
  
}


void run_away(){
  right();
  delay(1500);
  forward();
  delay(1000);
}

void response_to_sonar1(){
  Serial.println("sonar1");
  
  digitalWrite(trig,HIGH);
  delayMicroseconds(100);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=(duration/2)/29.1;
  Serial.print(distance);
  Serial.print("ed" );
  Serial.println(ara[servo_angle]);
  
  if(distance<90 and distance >=30 and car_stat==1){
    stop();
    if(flag==1){
      ara[servo_angle]=distance;mn=min(mn,servo_angle);
    }
    else{
      if(servo_angle>=mn and abs(ara[servo_angle]-distance)>30 and ara[servo_angle]<90 and ara[servo_angle]>30 ){
        int turn=abs(50-servo_angle)*30;
        if(servo_angle>50){
          right();
          delay(turn);
          stop();
          shot();
          run_away();
        }
        else{
          left();
          delay(turn);
          stop();
          shot();
          run_away();
        }
      }
      else if(servo_angle >=mn and ara[servo_angle]>=90){
        car_stat=0;
        forward();
      }
    }
  }
  else{
    if(distance>90 and servo_angle>=mn and car_stat==1){
      if(ara[servo_angle]<90)
      {
        forward();
      }
   
    }
    else if(servo_angle<mn and distance>=30 and car_stat==1){
      forward();
    }
    else if(servo_angle>=40 and servo_angle<=50 and distance <30 and car_stat==1){
    stop();
    car_stat=0;

    
  }

  else if(car_stat==0 and servo_angle >=80 and distance >30){
    right();
    delay(1000);
    forward();
    delay(500);
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
  
}

void shot(){
  digitalWrite(11,HIGH);
  delay(2000);
  digitalWrite(11,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
 // Serial.println("hi");
  cnt++;
  if(MODE==0){
    if(Serial.available()){
    
   
    String data=Serial.readString();
    Serial.print("received:"+data);
    Serial.println();
    if(data.indexOf("for")>=0){forward();
    
    }
    else if(data.indexOf("l")>=0)right();
    else if(data.indexOf("b")>=0)back();
    else if(data.indexOf("ri")>=0)left();
    //else if(data=='u')speedUp();
    //else if(data=='d')speedDown();
    else if(data.indexOf("st")>=0)stop();
    else if(data.indexOf("sh")>=0)shot();
    else if(data.indexOf("mod")>=0){
      MODE=1;
    }
    digitalWrite(36,HIGH);
    delay(100);
  }
  }
  else{
    if(Serial.available()){
        String data=Serial.readString();
        Serial.print("received:"+data);
        if(data.indexOf("st")>=0)stop();
        else if(data.indexOf("mod")>=0){
        MODE=1;
    }
    }
     control_servo();
  int ffff=0;
  if(!response_to_sonar2() and car_stat==1){response_to_sonar1();ffff=1;}
  
  if(car_stat==0 or ffff==0)response_to_sonar1();
 
 
  delay(100);
  digitalWrite(36,LOW);
  }
   
 
}
