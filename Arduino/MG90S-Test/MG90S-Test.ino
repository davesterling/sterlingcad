#include <Servo.h>

Servo myServo;  // create a servo object to control a servo

void setup() {
  myServo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  myServo.write(0);  // sets the servo position according to the value of 90
  delay(1000);        // waits for a second
  myServo.write(0);   // sets the servo position according to the value of 0
  delay(1000);        // waits for a second
}
