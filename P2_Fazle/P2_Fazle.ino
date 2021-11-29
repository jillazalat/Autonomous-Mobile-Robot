#include <IRremote.h>           //Include libraries
#include <Stepper.h>
#define STEPS 4096
#include <Servo.h>

Stepper stepper(STEPS, 9, 11, 10, 12);  //Initialize Stepper and Servo
Servo myservo;

int trig = 4;                 // trig pin for HC-SR04
int echo = 3;                 // echo pin for HC-SR04
float duration, distance;

const int RECV_PIN = 13;      //Initialize IR Receiver
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(15);      //Set Stepper speed
  myservo.attach(6);         //Set Servo pin
  myservo.write(102);
  irrecv.enableIRIn();
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

float dist_calc(int pos) {  // trigger 40kHz pulse for ranging
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // convert from duration for pulse to reach detector (microseconds) to range (in cm)
  duration = pulseIn(echo, HIGH); // duration for pulse to reach detector (in microseconds)
  distance = 100.0 * (343.0 * (duration / 2.0)) / 1000000.0; // 100.0*(speed of sound*duration/2)/microsec conversion
}

void loop() {
  int pos = constrain(pos, 60, 144); //define servo limits for steering
  if (irrecv.decode(&results)) {

    if (results.value == 0XFFFFFFFF)    //define IR Remote buttons and corresponding actions
      results.value = key_value;

    switch (results.value) {
      case 0xFF18E7:                 //Task 2, motion in a predefined path
        Serial.println("2");
        stepper.step(33437);
        myservo.write(144);
        stepper.step(4096);
        myservo.write(102);
        stepper.step(30000);
        myservo.write(60);
        stepper.step(4096);
        myservo.write(102);
        stepper.step(30000);
        break;
      case 0xFF629D:                //Manual motion Forward
        Serial.println("VOL+");
        stepper.step(279);
        break;
      case 0xFF30CF:                //Manual motion wheels straight
        Serial.println("1");
        myservo.write(102);
        break;
      case 0xFF22DD:                //Manual motion wheels Left
        Serial.println("|<<");
        myservo.write(60);
        break;
      case 0xFFA857:                //Manual motion Backward
        Serial.println("VOL-");
        stepper.step(-279);
        break ;
      case 0xFFC23D:                //Manual motion wheels Right
        Serial.println(">>|");
        myservo.write(144);
        break ;
      case 0xFF7A85:                //Task 3
        Serial.println("3");
        int endpoint;
        endpoint = 66874;
        for (int i = 0; i <= endpoint; i + 290) {
          if (distance > 10) {
            stepper.step(290);
          } else {
            myservo.write(144);
            stepper.step(279);
            myservo.write(60);
            stepper.step(279);
            myservo.write(102);
            stepper.step(558);
            myservo.write(60);
            stepper.step(279);
            myservo.write(144);
            stepper.step(279);
            myservo.write(102);
            i = i + 1412;
          }
        }
        break;
        key_value = results.value;
        irrecv.resume();
    }
  }
}
