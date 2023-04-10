#include <Stepper.h>
#include <Servo.h>

// Define stepper motor pins
const int stepperMotorPins[4] = {8, 10, 9, 11};  // Adjust pin numbers as needed
const int stepsPerRevolution = 2048;  // Adjust the number of steps per revolution as needed
Stepper myStepper(stepsPerRevolution, stepperMotorPins[0], stepperMotorPins[1], stepperMotorPins[2], stepperMotorPins[3]);

// Define joystick button pins
const int sw1Pin = 12;  // Connect the button of the first joystick to D12
const int sw2Pin = 13;  // Connect the button of the second joystick to D13

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

// Initialize the state for buttons
bool wasSw1Pressed = false;
bool wasSw2Pressed = false;

void setup() {
  // Set joystick button pins as input
  pinMode(sw1Pin, INPUT);
  pinMode(sw2Pin, INPUT);

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

  // Read the current state of the joystick buttons
  bool isSw1Pressed = digitalRead(sw1Pin) == LOW;
  bool isSw2Pressed = digitalRead(sw2Pin) == LOW;

  // Check if the first button is pressed and wasn't pressed in the previous iteration
  if (isSw1Pressed && !wasSw1Pressed) {
    // Move stepper motor one way
    myStepper.setSpeed(10);  // Adjust the speed as needed
    myStepper.step(200);     // Adjust the number of steps as needed
  }

  // Check if the second button is pressed and wasn't pressed in the previous iteration
  if (isSw2Pressed && !wasSw2Pressed) {
    // Move stepper motor the other way
    myStepper.setSpeed(10);  // Adjust the speed as needed
    myStepper.step(-200);    // Adjust the number of steps as needed
  }

  // Save the current button states for the next iteration
  wasSw1Pressed = isSw1Pressed;
  wasSw2Pressed = isSw2Pressed;

  // Add a delay to control the rate of servo and stepper motor movements
  delay(15);
}
