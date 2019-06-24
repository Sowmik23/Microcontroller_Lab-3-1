
#define sensor A0 



int S_A = 10;  //speed motor a
int M_A1 = 9; //motor a = +
int M_A2 = 8; //motor a = -
int M_B1 = 7; //motor b = -
int M_B2 = 6; //motor b = +
int S_B = 5;  //speed motor b



void setup() { 
  
  pinMode(sensor, INPUT); 
  pinMode(M_B1, OUTPUT);
pinMode(M_B2, OUTPUT);
pinMode(M_A1, OUTPUT);
pinMode(M_A2, OUTPUT);
pinMode(S_B, OUTPUT);
pinMode(S_A, OUTPUT);

analogWrite(S_A, 150); 
analogWrite(S_B, 150); 
delay(200);

 Serial.begin(9600);
} 

void loop() { 
   demo1();
   //demo2();
  
}

void demo2(){
  forword();
}

void demo1(){
   int   readsen = analogRead(sensor); 
  if(readsen < 100)
  {
    stopp();
    delay(1000);

    back();
    

    turnRight();
   

//    turnLeft();
//    delay(1000);

    stopp();
    delay(1000);

    forword();
    

  }
  else
  {
    forword();
  }
  
}

void forword(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);  
delay(4000);
}


void turnRight(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW); 
 delay(1000); 
}

void turnLeft(){
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);
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
