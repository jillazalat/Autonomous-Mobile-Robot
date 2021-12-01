#include<Servo.h>  //need servo library to access functions
#include<Stepper.h> // include stepper libraries
#include<IRremote.h> //need this for the ir remote and receiver functions

//declare servo pins
Servo myServo; //declaring servo object

int servo_pin = 6;
int straight_pos = 95; //160 works
int left_pos = 50;
int right_pos = 140;

//declaring stepper pins
int stepper_pin1 = 11;
int stepper_pin2 = 10;
int stepper_pin3 = 9;
int stepper_pin4 = 8;

int stepsPerRevolution = 2048;
int stepper_speed = 10;

//declare object stepper
Stepper myStepper(stepsPerRevolution, stepper_pin4, stepper_pin2, stepper_pin3, stepper_pin1);

//IR Receiver pins
int IR_Receiver_Pin = 12;
IRrecv myReceiver (IR_Receiver_Pin); //creating an object called myReceiver and connecting it to pin 2
decode_results results; //this is used to store the receiver button code

void setup() {
  //start serial communication
  Serial.begin(9600);
  Serial.println("Start IR Receiver!");

  myReceiver.enableIRIn(); //start the IR receiver
  Serial.println("IR Receiver Active...!");

  //setting stepper pins as output
  pinMode (stepper_pin1, OUTPUT);
  pinMode (stepper_pin2, OUTPUT);
  pinMode (stepper_pin3, OUTPUT);
  pinMode (stepper_pin4, OUTPUT);

  //attach servo pin
  myServo.attach(servo_pin);
  myServo.write(straight_pos);
}

void loop() {
  //if a signal is received then put it in the memory location of variable results
  if (myReceiver.decode(&results)) {

    switch (results.value) {
      case 0xFFFFFFFF: //forward
        Serial.println("Vol +");
        myStepper.setSpeed (stepper_speed);
        myStepper.step(-256);
        //myServo.write(100);
        break;
      case 0xFFC23D: //right
        Serial.println(">>");
        myServo.write(right_pos);
        break;
      case 0xFF30CF: //straighten wheels
        Serial.println("1");
        myServo.write(straight_pos);
        break;
      case 0xFF22DD: //left
        Serial.println("<<");
        myServo.write(left_pos);
        break;
    }
    //resume the IR receiver for next signal
    myReceiver.resume();
  }



  /*myStepper.setSpeed (stepper_speed);
    myStepper.step (256);*/
  //delay (100);
  //for (pos = 0; pos <= 10; pos ++) {
  //myServo.write(pos);
  //delay(100);
  //}
}
// put your setup code here, to run once:
/*myServo.attach(servo_pin);
  myServo.write(20);
  delay(1000);
  myServo.write(40);
  delay(1000);
  myServo.write(60);
  delay(1000);
  myServo.write(80);
  delay(1000);
  myServo.write(60);*/
