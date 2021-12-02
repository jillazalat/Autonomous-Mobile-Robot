#include<Servo.h>  //need servo library to access functions
#include<Stepper.h> // include stepper libraries
#include<IRremote.h> //need this for the ir remote and receiver functions

//declare servo pins
Servo myServo; //declaring servo object

int servo_pin = 6;
int straight_pos = 95; //160 works
int left_pos = 60;
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

//ultrasonic sensor pins
int Echo_pin = 5;
int Trig_pin = 4;
float duration;
float distance;

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

  //ultrasonic sensor
  pinMode(Trig_pin,OUTPUT);
  pinMode(Echo_pin,INPUT);
}

void loop() {
  //if a signal is received then put it in the memory location of variable results
  if (myReceiver.decode(&results)) {
    switch (results.value) {
      //task 1: manually 
      case 0xFFFFFFFF: //forward
        Serial.println("Vol +");
        myStepper.setSpeed (stepper_speed);
        myStepper.step(-256);
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
        
      //task 2: automatic 
      case 0xFF18E7:
        Serial.println("2");
        myStepper.setSpeed (stepper_speed);
        myStepper.step(-14000);
        myServo.write(right_pos);
        myStepper.step(-1200);
        myServo.write(straight_pos);
        myStepper.step(-1200);
        myServo.write(right_pos);
        myStepper.step(-1100);
        myServo.write(straight_pos);
        myStepper.step(-9000);
        myServo.write(left_pos);
        myStepper.step(-1600);
        myServo.write(straight_pos);
        myStepper.step(-1000);
        myServo.write(left_pos);
        myStepper.step(-1500);
        myServo.write(straight_pos);
        myStepper.step(-7000);
        break;

     //task 3: obstacle avoidance
      case 0xFF7A85:
        Serial.println("3");
        int destination;
        destination = 4000;
        for (int i = 0; i <= destination; i + 500) {
          dist_calculation();
          if (distance > 20) {
            myStepper.setSpeed (stepper_speed);
            myStepper.step(-256);
          } 
          else {
            myStepper.setSpeed (stepper_speed);
            myServo.write(right_pos);
            myStepper.step(-2000);
            myServo.write(straight_pos);
            myStepper.step(-1000);
            myServo.write(left_pos);
            myStepper.step(-2000);
            myServo.write(straight_pos);
            myStepper.step(-2200);
            myServo.write(left_pos);
            myStepper.step(-2000);
            myServo.write(straight_pos);
            myStepper.step(-2500);
            myServo.write(right_pos);
            myStepper.step(-1200);
            myServo.write(straight_pos);
            myStepper.step(-1000);
            i = i + 2000;
          }
        }
        break;
     //task 4 implementation
     case 0xFF10EF:
      Serial.println("4");
      myStepper.setSpeed (stepper_speed);
      
      //first square path segment including first right 
      myStepper.step(-12500);
      myServo.write(right_pos);
      myStepper.step(-2200);
      myServo.write(straight_pos);
      myStepper.step(-500);
      myServo.write(straight_pos);
      myStepper.step(-10700);
      
      //2nd square path segment including 2nd right
      myServo.write(right_pos);
      myStepper.step(-1950);
      myServo.write(straight_pos);
      myStepper.step(-12000);

      //3rd square path segment including 3rd right
      myServo.write(right_pos);
      myStepper.step(-2000);
      myServo.write(straight_pos);
      myStepper.step(-14500);      
    }    
    //resume the IR receiver for next signal
    myReceiver.resume();
  }
}

float dist_calculation(){
  
  // trigger 40kHz pulse for ranging
  digitalWrite(Trig_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin,LOW);
  
  // convert from duration for pulse to reach detector (microseconds) to range (in cm)
  duration = pulseIn(Echo_pin,HIGH); // duration for pulse to reach detector (in microseconds)
  distance = 100.0*(343.0*(duration/2.0))/1000000.0; // 100.0*(speed of sound*duration/2)/microsec conversion
 
 // Serial.print(pos);
  //Serial.print(",");
  Serial.println(distance);  
}
