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
int g_delay=2;
int chk=0;
int state=1;
int   IR_value ;
int S_state = 100,pos;
int A_speed=150;
int B_speed=150;

int Speed=80;

int test_dis=40;

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

analogWrite(S_A, Speed); 
analogWrite(S_B, Speed); 

delay(200);

 Serial.begin(9600);
} 

void loop() { 

  //Forward();
 // servoState();


  //object();

 // servoState();
  
  Stop();
  check_state();
  
}

void object()
{
  servoState();
  delay(1000);
  servo1Down();
  delay(1000);
  servo2Keep();
  delay(1000);
  
  servo1Up();
  delay(2000);
  servo1Down();
  delay(1000);
  servo2Out();
  delay(1000);
  servo1Up();
}

void check_state()
{
  while(state==1)
  {
    readIrSonar();
      
    if(IR_value > 800)
    {
      Stop();
      
      delay(1000);

      Back();

      turnLeft();
      Stop();
    }
    else
    {
        if(distance<test_dis)
        {
          state=2;
        }
        else
        {
          turnLeft();

          Stop();
        }
    }
    
  }
  while(state==2)
  {
    readIrSonar();

    if(IR_value > 800)
    {
      Stop();
      
      delay(1000);

      Back();

      turnLeft();

      state=1;
    }
    else
    {
        if(distance<10)
        {
          state=3;
        }
        else
        {
          Forward();
          delay(100);
          Stop_l();
        }
    }
    
  }
  while(state==3)
  {
    Stop();
    
    int value = readColor();

    if(value==1)
    {
       state=4;
        
    }
    else
    {
      Back();

      turnLeft();

      state=1;
    }
    
  }
  while(state==4)
  {
     motorRun();
     state = 1;
  }
  
}

int readColor()
{
  return 1;
}

void motorRun()
{
  servo1Down();

  servo2Keep();

  servo1Up();

  goOutside();
  
}

void servo1Down()
{
  for(pos = S_state; pos>=55 ;pos--)
  {
    servo1.write(pos);
    delay(25);
  }
}

void servo1Up()
{
  for(pos = 55;pos<=S_state; pos++)
 {  
   servo1.write(pos);
    delay(25);
  }
  //S_state=90;
}

void servoState()
{
  servo1.write(S_state);
  servo2.write(55);
}

void servo2Keep()
{
  for(pos = 55;pos<=120; pos++)
 {  
   servo2.write(pos);
    delay(25);
  }
}

void servo2Out()
{
  for(pos = 120; pos>=55 ;pos--)
  {
    servo2.write(pos);
    delay(25);
  }
}

void goOutside()
{
  while(1)
  {
    IR_value = analogRead(sensor); 

    if(IR_value>800)
    {
      break;
    }
    else
    {
     // Forward();
      //delay(100);
     // Stop_l();

      Forward();
          delay(100);
          Stop_l();
      
    }
  }

//  Forward();
//  delay(50);

     Stop();
//  delay(1000);

  servo1Down();
  servo2Out();
  servo1Up();
  servoState();

  Back();
 // delay(2000);
  Stop();

  turnLeft();

  state=1;
  
}

void readIrSonar()
{
    IR_value = analogRead(sensor); 

    
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
    Serial.println(IR_value);

    Serial.print("Distance : ");
    Serial.println(distance);
}
void Forward(){
  
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);  

}

void Stop(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);
delay(1000);
}

void Stop_l(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);
delay(100);
}

void Back(){
digitalWrite(M_A1, HIGH);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, HIGH); 

Speed = 30;

delay(500); 
Stop_l();

digitalWrite(M_A1, HIGH);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, HIGH); 

Stop_l();

Speed = 80;

}

void turnLeft(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);
delay(100); 
}
