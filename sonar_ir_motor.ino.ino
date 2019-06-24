#include <Servo.h>

#define sensor A0 

Servo servo1;
Servo servo2;

int S_A = 5;  //speed motor a
int M_A1 = 6; //motor a = +
int M_A2 = 7; //motor a = -
int M_B1 = 9; //motor b = -
int M_B2 = 10; //motor b = +
int S_B = 8;  //speed motor b
const int trigPin = 11;
const int echoPin = 12;
long duration,distance;
int g_delay=10;
int chk=0;


void setup() { 
  
pinMode(sensor, INPUT); 
pinMode(M_B1, OUTPUT);
pinMode(M_B2, OUTPUT);
pinMode(M_A1, OUTPUT);
pinMode(M_A2, OUTPUT);
pinMode(S_B, OUTPUT);
pinMode(S_A, OUTPUT);

pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

servo1.attach(4);
servo2.attach(3);

analogWrite(S_A, 250); 
analogWrite(S_B, 250); 

delay(200);

 Serial.begin(9600);
} 

void loop() { 
  //demo_ck();
   demo1();
  // demo2();
  
}

void demo_ck()
{
//digitalWrite(M_A1, HIGH);
//digitalWrite(M_A2, LOW);
//digitalWrite(M_B2, LOW);
//digitalWrite(M_B1, HIGH);
forward();
delay(500); 

}

void demo2(){
  forward();
 // stopp();
// turnLeft();
//turnRight();
}

void demo1(){
    
  while(1){

    
    
    int   readsen = analogRead(sensor); 

    stopp();

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
// Calculating the distance
    distance= duration*0.034/2;

    Serial.print("Color : ");
    Serial.println(readsen);

    Serial.print("Distance : ");
    Serial.println(distance);

    


    if(readsen > 800)
    {
      stopp();
      
      delay(1000);

      back();

      //turnRight();
      turnLeft();

      
    }
    else
    {
      
      if(distance<80)
      {
        //found something in area

        forward();
        delay(g_delay*distance);
        
      }
      else if(distance<10)
      {
        stopp();
      }
      else
      {
        if(chk>300)
        {
          chk=0;
          goAhead();
        }
        tern();
        stopp();
        delay(500);
      }
      
    }
    
    
  }
  
  
}

void tern()
{
  digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW); 
 delay(100); 
 normal();

 chk+=10;
}

void normal(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);  

}

void goAhead(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);
delay(500);  

}

void forward(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);  
//delay(100);
}


void turnRight(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW); 
 delay(70); 
}

void turnLeft(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);
delay(70); 
}

void stopp(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);
delay(100);
}

void back(){
digitalWrite(M_A1, HIGH);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, HIGH); 
delay(2000); 
}

void up(){

  
 
  for(pos = 55;pos<=120; pos++)
 {  
   myservo.write(pos);
    delay(25);
  }
  
}

void down(){
  for(pos = 120; pos>=55 ;pos--)
  {
    myservo.write(pos);
    delay(25);
  }
}
