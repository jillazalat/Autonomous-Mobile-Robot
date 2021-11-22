#include <Stepper.h>
#define STEPS 2048
Stepper stepper(STEPS, 8, 10, 9, 11);
#define m 7
#include <Servo.h>
Servo myservo;

void setup() {
   Serial.begin(9600);
    stepper.setSpeed(9);
  pinMode(m, OUTPUT);
  myservo.attach(5);
}

void loop() {
     stepper.step(-10000);
     //analogWrite(m,255);
      //myservo.write(90);
}
