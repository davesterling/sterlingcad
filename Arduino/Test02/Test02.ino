#include <Stepper.h>

// Define motor parameters
int motor1Speed = 10;
int motor1StepsPerIteration = 1024;
int motor1Iterations = 2;
Stepper motor1(2048, 4, 6, 5, 7); // Pins for Stepper Motor 1

int motor2Speed = 10;
int motor2StepsPerIteration = 2048;
int motor2Iterations = 10;
Stepper motor2(2048, 8, 10, 9, 11); // Pins for Stepper Motor 2

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
const long interval1 = 1000; // Interval for Motor 1 (1 second)
const long interval2 = 1000; // Interval for Motor 2 (1 second)

void setup() {
}

void loop() {
  unsigned long currentMillis = millis();

  // Motor 1: Rotate Positive 1024 Steps (Continuous)
  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;
    motor1.setSpeed(motor1Speed);

    for (int i = 0; i < motor1Iterations; i++) {
      for (int j = 0; j < motor1StepsPerIteration; j++) {
        motor1.step(1);
        delayMicroseconds(100); // Add a small delay between steps (adjust this value as needed)
      }
    }
  }

  // Motor 2: Rotate Negative 2048 Steps (Continuous)
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;
    motor2.setSpeed(motor2Speed);

    for (int i = 0; i < motor2Iterations; i++) {
      for (int j = 0; j < motor2StepsPerIteration; j++) {
        motor2.step(-1);
        delayMicroseconds(100); // Add a small delay between steps (adjust this value as needed)
      }
    }
  }
}
