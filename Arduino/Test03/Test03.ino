#include <Stepper.h>

int motorSpeed = 10;
Stepper myStepper(2048, 8, 10, 9, 11);

const int solenoidPin1 = 40;
const int solenoidPin2 = 41;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  pinMode(solenoidPin1, OUTPUT);
  pinMode(solenoidPin2, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Toggle the solenoid state
    digitalWrite(solenoidPin1, !digitalRead(solenoidPin1));
    digitalWrite(solenoidPin2, !digitalRead(solenoidPin2));
  }

  myStepper.setSpeed(motorSpeed);
  myStepper.step(-1024);

  // Wait a short time before starting the next motor movement
  delay(100);

  myStepper.step(2048);
}
