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
      
//        switch(results.value){
////          case 0xFFA25D:
////          Serial.println("ON / OFF");
////          stepper.step(-15000);
////          myservo.write(120);
////          stepper.step(-7300);
////          myservo.write(90);
////          stepper.step(-8000);
////          myservo.write(60);
////          stepper.step(-8300);
////          myservo.write(90);
////          stepper.step(-15000);
////          break;
//          case 0xFF629D: // Move Forward
//          
//          Serial.println("VOL+");
//          stepper.step(2000);
//          break;
//          case 0xFFE21D: // Straighten Wheels
//          Serial.println("FUNC / STOP");
//          myservo.write(70);
//          break;


//          case 0xFF22DD: // Left Turn
//          Serial.println("|<<");
//          myservo.write(30);
//          break;

//          case 0xFF02FD: 
//          Serial.println(">||");
//          stepper.step(5000);
//         break ;  

//          case 0xFFC23D:
//          Serial.println(">>|"); // Right Turn
//          myservo.write(110);
//          break ;  
//          case 0xFFA857: 
//          Serial.println("VOL-");
//          stepper.step(-5000);
//          break ;  
//          case 0x73B711FF:
//          Serial.println("Return to default");
//          stepper.step(0);
//          myservo.write(70);
//          break ;
//
//          
//
//                  
//               
//        }
        key_value = results.value;
        irrecv.resume(); 
  }
  Serial.println (results.value, HEX); 
}
