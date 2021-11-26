#include <IRremote.h>

#include <Stepper.h>
#define STEPS 2048
Stepper stepper(STEPS, 9, 11, 10, 12);

#include <Servo.h>
Servo myservo;

const int RECV_PIN = 13;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup() {
   Serial.begin(9600);
   stepper.setSpeed(10);
   myservo.attach(6);
   irrecv.enableIRIn();
}

void loop() {
   int pos=constrain(pos,50,140);
   if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
          case 0xFFA25D:
          Serial.println("ON / OFF");
          stepper.step(-14500);
          myservo.write(140);
          stepper.step(-9000);
          myservo.write(102);
          stepper.step(-8000);
          myservo.write(50);
          stepper.step(-10000);
          myservo.write(102);
          stepper.step(-10000);
          break;
          case 0xFF629D:
          Serial.println("VOL+");
          stepper.step(-1000);
          break;
          case 0xFFE21D:
          Serial.println("FUNC / STOP");
          myservo.write(102);
          break;
          case 0xFF22DD:
          Serial.println("|<<");
          myservo.write(50);
          break;
          case 0xFF02FD:
          Serial.println(">||");
          stepper.step(1000);
          break ;  
          case 0xFFC23D:
          Serial.println(">>|");
          myservo.write(140);
          break ;               
               
        }
        key_value = results.value;
        irrecv.resume(); 
  }
}
