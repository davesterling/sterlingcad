#include <Servo.h>

// Rotary Encoder Inputs
#define CLK1 21
#define DT1 20
#define CLK2 19
#define DT2 18
#define CLK3 17
#define DT3 16
#define CLK4 15
#define DT4 14

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

const int duration = 200;  // Adjust the duration (in milliseconds) as needed
const int moveIncrement = 4; // Adjust the increment (1/10 of 180 degrees) as needed

void setup() {
  // Set encoder pins as inputs
  pinMode(CLK1, INPUT);
  pinMode(DT1, INPUT);
  pinMode(CLK2, INPUT);
  pinMode(DT2, INPUT);
  pinMode(CLK3, INPUT);
  pinMode(DT3, INPUT);
  pinMode(CLK4, INPUT);
  pinMode(DT4, INPUT);

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
  int currentStateCLK2 = digitalRead(CLK2);
  int currentStateCLK3 = digitalRead(CLK3);
  int currentStateCLK4 = digitalRead(CLK4);

  // Handle encoder 1
  if (currentStateCLK1 != lastCounter1) {
    if (digitalRead(DT1) != currentStateCLK1) {
      // Move servo1 clockwise
      servo1.write(servo1.read() + moveIncrement);
    } else {
      // Move servo1 counterclockwise
      servo1.write(servo1.read() - moveIncrement);
    }
    previousMillis1 = millis();
    lastCounter1 = currentStateCLK1;
  }

  // Handle encoder 2
  if (currentStateCLK2 != lastCounter2) {
    if (digitalRead(DT2) != currentStateCLK2) {
      // Move servo2 clockwise
      servo2.write(servo2.read() + moveIncrement);
    } else {
      // Move servo2 counterclockwise
      servo2.write(servo2.read() - moveIncrement);
    }
    previousMillis2 = millis();
    lastCounter2 = currentStateCLK2;
  }

  // Handle encoder 3
  if (currentStateCLK3 != lastCounter3) {
    if (digitalRead(DT3) != currentStateCLK3) {
      // Move servo3 clockwise
      servo3.write(servo3.read() + moveIncrement);
    } else {
      // Move servo3 counterclockwise
      servo3.write(servo3.read() - moveIncrement);
    }
    previousMillis3 = millis();
    lastCounter3 = currentStateCLK3;
  }

  // Handle encoder 4
  if (currentStateCLK4 != lastCounter4) {
    if (digitalRead(DT4) != currentStateCLK4) {
      // Move servo4 clockwise
      servo4.write(servo4.read() + moveIncrement);
    } else {
      // Move servo4 counterclockwise
      servo4.write(servo4.read() - moveIncrement);
    }
    previousMillis4 = millis();
    lastCounter4 = currentStateCLK4;
  }

  // Check if the duration has passed, then stop the servos
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis1 >= duration) {
    // Stop servo1
    servo1.write(90);  // Middle position (stop)
  }
  if (currentMillis - previousMillis2 >= duration) {
    // Stop servo2
    servo2.write(90);
  }
  if (currentMillis - previousMillis3 >= duration) {
    // Stop servo3
    servo3.write(90);
  }
  if (currentMillis - previousMillis4 >= duration) {
    // Stop servo4
    servo4.write(90);
  }
}
