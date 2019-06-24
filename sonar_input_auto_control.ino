#include
#include
#include
#include
#include “Adafruit_PWMServoDriver.h”

#define TRIG_PIN A4
#define ECHO_PIN A5
#define MAX_DISTANCE 200
#define MAX_SPEED 190 // sets speed of DC motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which ‘port’ M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor1 = AFMS.getMotor(3);
Adafruit_DCMotor *motor2 = AFMS.getMotor(4);

Servo myservo;

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {

AFMS.begin();

myservo.attach(10);
myservo.write(115);
delay(2000);
distance = readPing();
delay(100);
distance = readPing();
delay(100);
distance = readPing();
delay(100);
distance = readPing();
delay(100);
}

void loop() {
int distanceR = 0;
int distanceL = 0;
delay(40);

if(distance=distanceL)
{
turnRight();
moveStop();
}else
{
turnLeft();
moveStop();
}
}else
{
moveForward();
}
distance = readPing();
}

int lookRight()
{
myservo.write(50);
delay(500);
int distance = readPing();
delay(100);
myservo.write(115);
return distance;
}

int lookLeft()
{
myservo.write(170);
delay(500);
int distance = readPing();
delay(100);
myservo.write(115);
return distance;
delay(100);
}

int readPing() {
delay(70);
int cm = sonar.ping_cm();
if(cm==0)
{
cm = 250;
}
return cm;
}

void moveStop() {
motor1.run(RELEASE);
motor2.run(RELEASE);
}

void moveForward() {

if(!goesForward)
{
goesForward=true;
motor1.run(FORWARD);
motor2.run(FORWARD);
for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
{
motor1.setSpeed(speedSet);
motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
delay(5);
}
}
}

void moveBackward() {
goesForward=false;
motor1.run(BACKWARD);
motor2.run(BACKWARD);
for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
{
motor1.setSpeed(speedSet);
motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
delay(5);
}
}

void turnRight() {
motor1.run(FORWARD);
motor2.run(BACKWARD);
delay(300);
motor1.run(FORWARD);
motor2.run(FORWARD);
}

void turnLeft() {
motor1.run(BACKWARD);
motor2.run(FORWARD);
delay(300);
motor1.run(FORWARD);
motor2.run(FORWARD);
}


