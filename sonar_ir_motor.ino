
#define sensor A0 



int S_A = 10;  //speed motor a
int M_A1 = 9; //motor a = +
int M_A2 = 8; //motor a = -
int M_B1 = 7; //motor b = -
int M_B2 = 6; //motor b = +
int S_B = 5;  //speed motor b
const int trigPin = 11;
const int echoPin = 12;
long duration,distance;



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

analogWrite(S_A, 100); 
analogWrite(S_B, 220); 

delay(200);

 Serial.begin(9600);
} 

void loop() { 
   demo1();
  // demo2();
  
}

void demo2(){
  forword();
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
      if(distance<15)
      {
        stopp();
      }
      else if(distance<70)
      {
        //found something in area

        forword();
        delay(200);
        
      }
      else
      {
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
}

void normal(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);  

}

void forword(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);  
delay(100);
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
}

void back(){
digitalWrite(M_A1, HIGH);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, HIGH); 
delay(2000); 
}
