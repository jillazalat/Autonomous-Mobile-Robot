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
void setup() {
   Serial.begin(9600);
   stepper.setSpeed(15);
   myservo.attach(6);
   irrecv.enableIRIn();
   myservo.write(90);
}

int straight = 96;
int right = 45;
int left = 130;
int walk = 1000;
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
    if (results.value == 0xFF30CF)
    {
      stepper.step(-8*walk);
      
//      myservo.write(left); 
//      stepper.step(-walk);
      
//      myservo.write(straight);
//      stepper.step(-4*walk);
      
      myservo.write(right);
      stepper.step(-6*walk);


      myservo.write(straight);
      stepper.step(-8*walk);

      myservo.write(right);
      stepper.step(-4*walk);

      myservo.write(straight);
      stepper.step(-8*walk);

      myservo.write(right);
      stepper.step(-4*walk);

      myservo.write(straight);
      stepper.step(-8*walk);

    }
      
        key_value = results.value;
        irrecv.resume(); 
  }
  Serial.println (results.value, HEX); 
 // Serial.print(sonar.ping_cm());
}
