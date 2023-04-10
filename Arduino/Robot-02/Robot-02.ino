#include <Servo.h>

// Rotary Encoder Inputs
#define CLK1 21
#define DT1 20
#define SW1 19 // Button for resetting position
#define CLK2 18
#define DT2 17
#define SW2 16
#define CLK3 15
#define DT3 14
#define SW3 13
#define CLK4 12
#define DT4 11
#define SW4 10

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int lastCounter1 = 0;
int lastCounter2 = 0;
int lastCounter3 = 0;
int lastCounter4 = 0;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;

const int duration = 500;        // Adjust the duration (in milliseconds) as needed
const int moveIncrement = 5;     // Adjust the increment (smaller degree of rotation) as needed

// Variables to store the target positions for each servo
int targetPosition1 = 90;
int targetPosition2 = 90;
int targetPosition3 = 90;
int targetPosition4 = 90;

// Variables to store start positions for each servo
int startPosition1 = 90;
int startPosition2 = 90;
int startPosition3 = 90;
int startPosition4 = 90;

void setup() {
  // Set encoder pins as inputs
  pinMode(CLK1, INPUT);
  pinMode(DT1, INPUT);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(CLK2, INPUT);
  pinMode(DT2, INPUT);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(CLK3, INPUT);
  pinMode(DT3, INPUT);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(CLK4, INPUT);
  pinMode(DT4, INPUT);
  pinMode(SW4, INPUT_PULLUP);

  // Setup Serial Monitor
  Serial.begin(9600);

  // Attach servos to the servo objects
  servo1.attach(4);  // Adjust pin numbers as needed
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(7);

  // Initialize servo positions to the middle (stop)
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
}

void loop() {
  // Read each encoder state and control servos
  int currentStateCLK1 = digitalRead(CLK1);
  int currentStateDT1 = digitalRead(DT1);
  int currentStateSW1 = digitalRead(SW1);
  int currentStateCLK2 = digitalRead(CLK2);
  int currentStateDT2 = digitalRead(DT2);
  int currentStateSW2 = digitalRead(SW2);
  int currentStateCLK3 = digitalRead(CLK3);
  int currentStateDT3 = digitalRead(DT3);
  int currentStateSW3 = digitalRead(SW3);
  int currentStateCLK4 = digitalRead(CLK4);
  int currentStateDT4 = digitalRead(DT4);
  int currentStateSW4 = digitalRead(SW4);

  // Handle encoder 1
  if (currentStateCLK1 != lastCounter1) {
    if (currentStateDT1 != currentStateCLK1) {
      // Move servo1 clockwise
      targetPosition1 += moveIncrement;
    } else {
      // Move servo1 counterclockwise
      targetPosition1 -= moveIncrement;
    }
    lastCounter1 = currentStateCLK1;
  }

  // Handle encoder 2
  if (currentStateCLK2 != lastCounter2) {
    if (currentStateDT2 != currentStateCLK2) {
      // Move servo2 clockwise
      targetPosition2 += moveIncrement;
    } else {
      // Move servo2 counterclockwise
      targetPosition2 -= moveIncrement;
    }
    lastCounter2 = currentStateCLK2;
  }

  // Handle encoder 3
  if (currentStateCLK3 != lastCounter3) {
    if (currentStateDT3 != currentStateCLK3) {
      // Move servo3 clockwise
      targetPosition3 += moveIncrement;
    } else {
      // Move servo3 counterclockwise
      targetPosition3 -= moveIncrement;
    }
    lastCounter3 = currentStateCLK3;
  }

  // Handle encoder 4
  if (currentStateCLK4 != lastCounter4) {
    if (currentStateDT4 != currentStateCLK4) {
      // Move servo4 clockwise
      targetPosition4 += moveIncrement;
    } else {
      // Move servo4 counterclockwise
      targetPosition4 -= moveIncrement;
    }
    lastCounter4 = currentStateCLK4;
  }

  // Check if the reset button is pressed
  if (currentStateSW1 == LOW) {
    // Log the current positions as start positions
    startPosition1 = targetPosition1;
    startPosition2 = targetPosition2;
    startPosition3 = targetPosition3;
    startPosition4 = targetPosition4;
  }

  // Control servos based on target positions
  servo1.write(targetPosition1);
  servo2.write(targetPosition2);
  servo3.write(targetPosition3);
  servo4.write(targetPosition4);

  // Check if the duration has passed, then reset target positions
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis1 >= duration) {
    targetPosition1 = startPosition1;  // Move back to start position
  }
  if (currentMillis - previousMillis2 >= duration) {
    targetPosition2 = startPosition2;
  }
  if (currentMillis - previousMillis3 >= duration) {
    targetPosition3 = startPosition3;
  }
  if (currentMillis - previousMillis4 >= duration) {
    targetPosition4 = startPosition4;
  }

  // Update previousMillis variables
  previousMillis1 = currentMillis;
  previousMillis2 = currentMillis;
  previousMillis3 = currentMillis;
  previousMillis4 = currentMillis;
}
