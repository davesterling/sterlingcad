#include <Servo.h>

// Define servo and encoder pins
const int servoPin = 9;
const int encoderCLK = 2;
const int encoderDT = 3;
const int encoderSW = 4;

Servo myServo;

int encoderPos = 0;
int lastEncoderPos = 0;
bool isLooping = false;
bool isButtonPressed = false;
unsigned long buttonPressTime = 0;

void setup() {
  myServo.attach(servoPin);
  pinMode(encoderCLK, INPUT);
  pinMode(encoderDT, INPUT);
  pinMode(encoderSW, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoderCLK), readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderSW), checkButtonPress, FALLING);
}

void loop() {
  if (isLooping) {
    int targetPos = map(encoderPos, 0, 1023, 0, 180);
    myServo.write(targetPos);
  }

  if (millis() - buttonPressTime > 500 && isButtonPressed) {
    if (!isLooping) {
      isLooping = true;
      encoderPos = 0;
      lastEncoderPos = 0;
      myServo.write(0);
    } else {
      isLooping = false;
    }
    isButtonPressed = false;
  }
}

void readEncoder() {
  int reading = digitalRead(encoderCLK);
  if (digitalRead(encoderDT) != reading) {
    encoderPos--;
  } else {
    encoderPos++;
  }
}

void checkButtonPress() {
  if (millis() - buttonPressTime > 200) {
    isButtonPressed = true;
    buttonPressTime = millis();
  }
}
