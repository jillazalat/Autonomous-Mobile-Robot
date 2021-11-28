#include <IRremote.h>

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
   stepper.setSpeed(15);
   myservo.attach(5);
   irrecv.enableIRIn();
   myservo.write(70);
}

void loop() {
   int pos=constrain(pos,30,110);
   if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

    if (results.value == 0xFF629D) // Move Forward
    {
      Serial.println("VOL+");
      stepper.step(1000);
    }
    if (results.value == 0xFFE21D)// Straighten Wheels
    {
      Serial.println("FUNC / STOP");
      stepper.step(1000);
      myservo.write(70);
    }
    if (results.value == 0xFF22DD)// Left Turn
    {
      Serial.println("|<<");
      myservo.write(30);
    }
    if (results.value == 0xFFC23D)// Right Turn
    {
      Serial.println(">>|");
      myservo.write(110);
    }
    if (results.value == 0xFFA857)// Move Backward
    {
       Serial.println("VOL-");
      stepper.step(-1000);
    }
      
        key_value = results.value;
        irrecv.resume(); 
  }
  Serial.println (results.value, HEX); 
}
