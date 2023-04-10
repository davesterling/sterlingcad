#include <Stepper.h>

// Define the number of steps per revolution for the stepper motor
const int stepsPerRevolution = 2048; // Adjust this based on your stepper motor specification

// Initialize the Stepper library
Stepper stepper(stepsPerRevolution, 8, 9, 10, 11); // Pins: IN1, IN2, IN3, IN4

void setup() {
  // Set the speed of the stepper motor (adjust as needed)
  stepper.setSpeed(5); // RPM
}

void loop() {
  // Rotate the stepper motor clockwise continuously
  stepper.step(stepsPerRevolution);
}
