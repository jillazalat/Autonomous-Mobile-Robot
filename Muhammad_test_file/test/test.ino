#include<Servo.h>  //need servo library to access functions
#include <Stepper.h> // include stepper libraries

//declare servo pins
Servo myServo; //declaring servo object

int servo_pin = 6;
int pos = 0;

//declaring stepper pins
int stepper_pin1 = 11;
int stepper_pin2 = 10;
int stepper_pin3 = 9;
int stepper_pin4 = 8;

int stepsPerRevolution = 2048; 
int stepper_speed = 10;

//declare object stepper

Stepper myStepper(stepsPerRevolution, stepper_pin4, stepper_pin2, stepper_pin3, stepper_pin1);

void setup() {
  // put your setup code here, to run once:
  myServo.attach(servo_pin);
  myServo.write(70);

  Serial.begin(9600);
  
  //setting stepper pins as output
  pinMode (stepper_pin1, OUTPUT);
  pinMode (stepper_pin2, OUTPUT);
  pinMode (stepper_pin3, OUTPUT);
  pinMode (stepper_pin4, OUTPUT);
}

void loop() {
    myStepper.setSpeed (stepper_speed);
    myStepper.step (256);
    //delay (100);
    //for (pos = 0; pos <= 10; pos ++) {
      //myServo.write(pos);
      //delay(100);
    //}
}
