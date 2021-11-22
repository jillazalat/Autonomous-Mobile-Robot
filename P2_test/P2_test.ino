#include <Stepper.h>
#include <Servo.h>

Servo servo;
const int stepsPerRevolution = 2048;
Stepper stepper(stepsPerRevolution, 9, 11, 10, 12);

int joyx = A0;
int joyY = A1;

void setup() {
  servo.attach(6);
  stepper.setSpeed(4);
}

void loop() {
  int joyVal;
  joyVal = analogRead(joyx);

  if ((joyVal > 500) && (joyVal < 523)) {
    digitalWrite(6, LOW);
  }
  else if (joyVal >= 523)
  {
    joyVal = map(joyVal, 523, 1023, 90, 180);
    servo.write(joyVal);
  } else
  {
    joyVal = map(joyVal, 500, 0, 90, 0);
    servo.write(joyVal);
  }
  
  digitalWrite(9, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(12, LOW);
  int val = analogRead(joyY);
  if( val >= 523) {
    stepper.step(10);
  } else if (val <= 500) {
    stepper.step(-10);
  }
}
