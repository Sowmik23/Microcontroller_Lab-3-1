#include <Servo.h>

Servo myservo;

int pos =0;



void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);

}

void loop() {
  // put your mai code here, to run repeatedly:
 // myservo.write(90);
  for(pos = 45;pos<=150; pos++)
 {
   myservo.write(pos);
    delay(25);
  }

  for(pos = 150; pos>=45 ;pos--)
  {
    myservo.write(pos);
    delay(25);
  }

}
