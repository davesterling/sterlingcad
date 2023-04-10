#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

#define TRIG_PIN 6  // Connect the TRIG pin of the ultrasonic sensor to digital pin 4
#define ECHO_PIN 4  // Connect the ECHO pin of the ultrasonic sensor to digital pin 6
#define BUZZER_PIN 9 // Connect the positive (longer) leg of the buzzer to digital pin 9

#define MAX_DISTANCE 100 // Maximum distance we want to measure (in centimeters)

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

int counter = 0;
bool belowThreshold = false;
bool aboveThreshold = false;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize display with I2C address 0x3C
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  int distance = sonar.ping_cm(); // Get the distance in centimeters

  // Prevent distances greater than MAX_DISTANCE from being displayed as 0
  if (distance > MAX_DISTANCE) {
    distance = MAX_DISTANCE + 1; // Set distance to a value greater than MAX_DISTANCE
  }

  // Check if distance is below 10cm
  if (distance <= 10 && !belowThreshold) {
    belowThreshold = true;
    beep(); // Call the function to beep
  } else if (distance > 10 && belowThreshold) {
    belowThreshold = false;
  }

  // Check if distance is above 40cm
  if (distance >= 40 && !aboveThreshold) {
    aboveThreshold = true;
    counter++; // Increment the counter
  } else if (distance < 40 && aboveThreshold) {
    aboveThreshold = false;
  }

  display.clearDisplay();
  display.setTextSize(1); // Reduce text size for other text
  display.setTextColor(WHITE);
  
  // Print distance (or "Out of Range" if distance is over MAX_DISTANCE)
  display.setCursor(0, 0);
  if (distance > MAX_DISTANCE) {
    display.print("Out of Range");
  } else {
    display.print("Distance: ");
    display.print(distance);
    display.print(" cm");
  }
  
  // Print counter with larger font size (2) and moved up (Y-coordinate adjusted)
  display.setTextSize(2);
  display.setCursor(0, 10); // Move cursor up a bit
  display.print(counter);

  display.display(); // Display content
}

void beep() {
  tone(BUZZER_PIN, 1000, 100); // Play a short beep at 1000 Hz for 100 ms (0.1 second)
  delay(100); // Add a small delay before returning to avoid overlapping beeps
  noTone(BUZZER_PIN); // Turn off the buzzer after the beep
}
