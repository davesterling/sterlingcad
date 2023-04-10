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

  // Initialize servo positions to 90 degrees
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
      servo1.write(servo1.read() - 18);  // 360 degrees / 20 positions = 18 degrees per position
    } else {
      servo1.write(servo1.read() + 18);
    }
    lastCounter1 = currentStateCLK1;
  }

  // Handle encoder 2
  if (currentStateCLK2 != lastCounter2) {
    if (digitalRead(DT2) != currentStateCLK2) {
      servo2.write(servo2.read() - 18);
    } else {
      servo2.write(servo2.read() + 18);
    }
    lastCounter2 = currentStateCLK2;
  }

  // Handle encoder 3
  if (currentStateCLK3 != lastCounter3) {
    if (digitalRead(DT3) != currentStateCLK3) {
      servo3.write(servo3.read() - 18);
    } else {
      servo3.write(servo3.read() + 18);
    }
    lastCounter3 = currentStateCLK3;
  }

  // Handle encoder 4
  if (currentStateCLK4 != lastCounter4) {
    if (digitalRead(DT4) != currentStateCLK4) {
      servo4.write(servo4.read() - 18);
    } else {
      servo4.write(servo4.read() + 18);
    }
    lastCounter4 = currentStateCLK4;
  }
}
