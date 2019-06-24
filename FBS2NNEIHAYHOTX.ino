//this program is written to fine an red object and turn the bot right and left to make it center

const int rp=11;
const int rn=10;
const int lp=9;
const int ln=6;
int h=150,l=150;

void setup()
{
Serial.begin(9600);
pinMode(13,OUTPUT);
pinMode(rp,OUTPUT);
pinMode(rn,OUTPUT);
pinMode(lp,OUTPUT);
pinMode(ln,OUTPUT);
}

void loop()
{
  int a=0;
if (Serial.available())
{
  
a=Serial.read();
if(a=='L')
{
analogWrite(rp,h);
digitalWrite(rn,LOW);
digitalWrite(lp,LOW);
analogWrite(ln,h);
digitalWrite(13,LOW);
}
else if(a=='R')
{
digitalWrite(rp,LOW);
analogWrite(rn,h);
analogWrite(lp,h);
digitalWrite(ln,LOW);
digitalWrite(13,LOW);

}
else if(a=='C')
{
digitalWrite(rp,LOW);
digitalWrite(rn,LOW);
digitalWrite(lp,LOW);
digitalWrite(ln,LOW);
digitalWrite(13,HIGH);
}
else if(a=='F')
{
analogWrite(rp,l);
digitalWrite(rn,LOW);
analogWrite(lp,l);
digitalWrite(ln,LOW);
digitalWrite(13,HIGH);

}
else if(a=='B')
{
digitalWrite(rp,LOW);
analogWrite(rn,l);
digitalWrite(lp,LOW);
analogWrite(ln,l);
digitalWrite(13,HIGH);

}
else
digitalWrite(13,LOW);
}
//Serial.println(a);
}
