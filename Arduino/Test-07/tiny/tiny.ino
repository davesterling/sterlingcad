#include <Wire.h>
#include <NewPing.h>

#define TRIG_PIN 2    // Connect the TRIG pin of the ultrasonic sensor to digital pin 2
#define ECHO_PIN 3    // Connect the ECHO pin of the ultrasonic sensor to digital pin 3
#define BUZZER_PIN 5  // Connect the positive (longer) leg of the buzzer to digital pin 5

#define MAX_DISTANCE 100  // Maximum distance we want to measure (in centimeters)
#define DIRECTION_CHANGE_THRESHOLD 10  // Threshold for direction change in centimeters

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

int counter = 0;
bool belowThreshold = false;
bool aboveThreshold = false;
bool lowToneDirectionChange = false;
int lastDistance = 0;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  Wire.begin();  // Initialize I2C communication
}

void loop() {
  delay(50);  // Delay for stable readings and smoother operation

  int distance = sonar.ping_cm();  // Get the distance in centimeters

  // Check for upward movement (from 10cm or lower to above 40cm)
  if (distance <= 10 && !belowThreshold) {
    belowThreshold = true;
    aboveThreshold = false;
    lowToneDirectionChange = false;
  }

  // Check for downward movement after an upward movement of 10cm or more
  if (distance >= 40 && belowThreshold && !aboveThreshold) {
    belowThreshold = false;
    aboveThreshold = true;
    counter++;  // Increment the counter
    playHighPitchedBeep();
    lowToneDirectionChange = false;
  }

  // Check for downward movement after an upward movement without completing the cycle
  if (distance <= 10 && aboveThreshold) {
    belowThreshold = false;
    aboveThreshold = false;
    playLowPitchedBeep();
    lowToneDirectionChange = false;
  }

  // Check for direction change of more than 10cm
  if (abs(distance - lastDistance) > DIRECTION_CHANGE_THRESHOLD) {
    // Check if the change is happening between 10cm and 40cm
    if (distance > 10 && distance < 40) {
      if (lowToneDirectionChange) {
        playLowPitchedBeep();
        lowToneDirectionChange = false;
      } else {
        lowToneDirectionChange = true;
      }
    }
  }

  lastDistance = distance;  // Update last distance
}

void playHighPitchedBeep() {
  tone(BUZZER_PIN, 1000, 100);  // Play a short high-pitched beep
  delay(100);  // Delay before turning off the buzzer
  noTone(BUZZER_PIN);  // Turn off the buzzer
}

void playLowPitchedBeep() {
  tone(BUZZER_PIN, 500, 500);  // Play a low-pitched beep for 0.5 seconds
  delay(500);  // Delay before turning off the buzzer
  noTone(BUZZER_PIN);  // Turn off the buzzer
}
