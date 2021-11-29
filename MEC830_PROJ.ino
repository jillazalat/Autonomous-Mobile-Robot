#include <IRremote.h>

#include "SR04.h"
#define TRIG_PIN 4
#define ECHO_PIN 5
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
int dist;
long totalDist = 38000
;

#include <Stepper.h>
#define STEPS 2048
Stepper stepper(STEPS, 8, 10, 9, 11);

#include <Servo.h>
Servo myservo;

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(10);
  myservo.attach(13);
  irrecv.enableIRIn();
}

void loop() {
  int pos = constrain(pos, 60, 120);
  if (irrecv.decode(&results)) {

    if (results.value == 0XFFFFFFFF)
      results.value = key_value;

    switch (results.value) {
      case 0xFFA25D:
        Serial.println("ON / OFF");
        stepper.step(-15000);
        myservo.write(120);
        stepper.step(-7300);
        myservo.write(90);
        stepper.step(-8000);
        myservo.write(60);
        stepper.step(-8300);
        myservo.write(90);
        stepper.step(-15000);
        break;
      case 0xFF629D:
        Serial.println("VOL+");
        stepper.step(-1000);
        break;
      case 0xFFE21D:
        Serial.println("FUNC / STOP");
        myservo.write(90);
        break;
      case 0xFF22DD:
        Serial.println("|<<");
        myservo.write(60);
        break;
      case 0xFF02FD:
        Serial.println(">||");
        stepper.step(1000);
        break ;
      case 0xFFC23D:
        Serial.println(">>|");
        myservo.write(120);
        break ;
      case 0xFF7A85:
        Serial.println("3");
        for (int i = 0; i <= totalDist; i = i + 500) {
          dist = sr04.Distance();

          if (dist > 35) {
            stepper.step(-500);
          } else {
            myservo.write(120);
            stepper.step(-4000);
            myservo.write(60);
            stepper.step(-9000);
            myservo.write(120);
            stepper.step(-2000);
            myservo.write(90);
            i = i + 18000;
          }
        }
        break ;

    }
    key_value = results.value;
    irrecv.resume();
  }
}
