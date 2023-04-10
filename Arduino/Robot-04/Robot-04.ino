#include <Servo.h>

// Define servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Define joystick pins
const int joy1XPin = A0;
const int joy1YPin = A1;
const int joy2XPin = A2;
const int joy2YPin = A3;

void setup() {
  // Attach servos to corresponding pins
  servo1.attach(4);  // Adjust pin numbers as needed
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(7);
}

void loop() {
  // Read joystick values
  int joy1X = analogRead(joy1XPin);
  int joy1Y = analogRead(joy1YPin);
  int joy2X = analogRead(joy2XPin);
  int joy2Y = analogRead(joy2YPin);

  // Map joystick values to servo angles (adjust the mapping range as needed)
  int angle1 = map(joy1X, 0, 1023, 0, 180);
  int angle2 = map(joy1Y, 0, 1023, 0, 180);
  int angle3 = map(joy2X, 0, 1023, 0, 180);
  int angle4 = map(joy2Y, 0, 1023, 0, 180);

  // Control servos with joystick values
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servo4.write(angle4);

  // Add a delay to smooth out servo movements
  delay(15);
}
