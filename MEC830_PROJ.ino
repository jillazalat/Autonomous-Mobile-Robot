#include <IRremote.h>

#include "SR04.h"
#define TRIG_PIN 4
#define ECHO_PIN 5
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
int dist, flag=0;
long totalDist = 38000;

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
  stepper.setSpeed(10); //Set as Maximum possible stepper speed
  myservo.attach(13);
  irrecv.enableIRIn(); //Enable IR reciever
}

void loop() {
  int pos = constrain(pos, 60, 120); // Limit servo position 
  if (irrecv.decode(&results)) {

    if (results.value == 0XFFFFFFFF) // IF button held, repeat previous input
      results.value = key_value;

    switch (results.value) { // TASK 2
      case 0xFF18E7:
        Serial.println("2");
        stepper.step(-15000);
        myservo.write(120);
        stepper.step(-7300);
        myservo.write(90);
        stepper.step(-8000);
        myservo.write(60);
        stepper.step(-8300);
        myservo.write(90);
        stepper.step(-15000);
        break;                // END OF TASK 2
      case 0xFF629D:          // TASK 1 USER COMMANDS
        Serial.println("VOL+"); //Move Forwards
        stepper.step(-1000);
        break;
      case 0xFFE21D:
        Serial.println("FUNC / STOP"); //Straighten wheels
        myservo.write(90);
        break;
      case 0xFF22DD:
        Serial.println("|<<");  //Turn Left
        myservo.write(60);
        break;
      case 0xFF02FD:
        Serial.println(">||"); //Move Backwards
        stepper.step(1000);
        break ;
      case 0xFFC23D:
        Serial.println(">>|");// Turn Right
        myservo.write(120);
        break ;                       // END OF TASK 1
      case 0xFF7A85:                  // TASK 3 
        Serial.println("3");
        for (long i = 0; i <= totalDist; i = i + 500) {
          dist = sr04.Distance();
              Serial.println(dist);
          if (dist > 40) {              //If no object detected
            stepper.step(-500);
            Serial.println(i);
          } 
            if ((flag==0)&&(dist<40)){ //If object detected
            myservo.write(120);
            stepper.step(-4000);
            myservo.write(60);
            stepper.step(-9000);
            myservo.write(120);
            stepper.step(-3500);
            myservo.write(90);
            i = i + 10000;
            flag=1;
            Serial.println(i);
          }
        }
        break ;                      //END OF TASK 3

    }
    key_value = results.value;
    irrecv.resume();
  }
}
