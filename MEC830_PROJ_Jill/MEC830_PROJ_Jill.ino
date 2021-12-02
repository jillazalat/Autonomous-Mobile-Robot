#include <IRremote.h>

#include <Stepper.h>
#define STEPS 2048
Stepper stepper(STEPS, 8, 10, 9, 11);
#include <NewPing.h>

#include <Servo.h>
Servo myservo;

#define echoPin 12
#define trigPin 13
#define PULSE_TIMEOUT 150000
NewPing sonar(trigPin, echoPin);
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;
int distance, flag=0;
long totaldistance = 38000;
int straight = 96;
int right = 65;
int left = 130;
int walk = 1000;
void setup() {
   Serial.begin(9600);
   stepper.setSpeed(15);
   myservo.attach(6);
   irrecv.enableIRIn();
   myservo.write(straight);
}

void loop() {
  // int pos=constrain(pos,30,110);
   if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

    if (results.value == 0xFF629D) // Move Forward
    {
      Serial.println("VOL+");
      stepper.step(-walk);
    }
    if (results.value == 0xFFE21D)// Straighten Wheels
    {
      Serial.println("FUNC / STOP");
      myservo.write(straight);
    }
    if (results.value == 0xFF22DD)// Left Turn
    {
      Serial.println("|<<");
      myservo.write(left);
    }
    if (results.value == 0xFFC23D)// Right Turn
    {
      Serial.println(">>|");
       Serial.println("|<<");
      myservo.write(right);

    }
    if (results.value == 0xFFA857)// Move Backward
    {
       Serial.println("VOL-");
      stepper.step(walk);
    }
    if (results.value == 0xFF30CF) // Task 4/Task 2
    {
      stepper.step(-12*walk);
      
 
      myservo.write(right);
      stepper.step(-6*walk);


      myservo.write(straight);
      stepper.step(-8*walk);

      myservo.write(left);
      stepper.step(-6*walk);

      myservo.write(straight);
      stepper.step(-12*walk);
    }
    if (results.value == 0xFF18E7)
     {
      for (long i = 0; i <= totaldistance; i = i + 500) {
          distance = sonar.ping_cm();
              Serial.println(distance);
          if (distance > 40) {              //If no object detected
            stepper.step(-500);
            Serial.println(i);
          } 
            if ((flag==0)&&(distance<40)){ //If object detected
            myservo.write(right);
            stepper.step(-3.5*walk);

            myservo.write(left);
            stepper.step(-2*walk);

            myservo.write(straight);
            stepper.step(-3*walk);

            myservo.write(left);
            stepper.step(-4*walk);
            myservo.write(right);
            stepper.step(-2.2*walk);
 
            myservo.write(straight);
            
            i = i + 10000;
            flag=1;
            Serial.println(i);
          }
        }
     }
        key_value = results.value;
        irrecv.resume(); 
  }
  Serial.println (results.value, HEX); 
 // Serial.print(sonar.ping_cm());
}
