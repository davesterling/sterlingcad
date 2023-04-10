#include <Servo.h>

// Rotary Encoder Inputs
#define CLK 2
#define DT 3

Servo servo;
int lastCounter = 0;

void setup() {
  // Set encoder pins as inputs
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  // Setup Serial Monitor
  Serial.begin(9600);

  // Attach servo on pin 9 to the servo object
  servo.attach(9);
  servo.write(90);  // Initialize servo position to 90 degrees
}

void loop() {
  int currentStateCLK = digitalRead(CLK);

  if (currentStateCLK != lastCounter) {
    if (digitalRead(DT) != currentStateCLK) {
      servo.write(servo.read() - 12);  // Increment servo position
    } else {
      servo.write(servo.read() + 12);  // Decrement servo position
    }
    lastCounter = currentStateCLK;
  }
}
