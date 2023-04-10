#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

#define TRIG_PIN 6  // Connect the TRIG pin of the ultrasonic sensor to digital pin 4
#define ECHO_PIN 4  // Connect the ECHO pin of the ultrasonic sensor to digital pin 6
#define BUZZER_PIN 9 // Connect the positive (longer) leg of the buzzer to digital pin 9

#define MAX_DISTANCE 200 // Maximum distance we want to measure (in centimeters)

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
  delay(100); // Delay for stable readings

  int distance = sonar.ping_cm(); // Get the distance in centimeters

  // Check if distance is below 10cm
  if (distance <= 10 && !belowThreshold) {
    belowThreshold = true;
  }

  // Check if distance is above 40cm
  if (distance >= 40 && belowThreshold && !aboveThreshold) {
    aboveThreshold = true;
    belowThreshold = false;
    counter++; // Increment the counter
    beep(); // Call the function to beep
  }

  // Reset thresholds when distance is below 10cm again
  if (distance <= 10 && aboveThreshold) {
    aboveThreshold = false;
  }

  display.clearDisplay();
  display.setTextSize(1); // Reduce text size for other text
  display.setTextColor(WHITE);
  
  // Print distance
  display.setCursor(0, 0);
  display.print("Distance: ");
  display.print(distance);
  display.print(" cm");
  
  // Print counter with larger font size (2) and moved up (Y-coordinate adjusted)
  display.setTextSize(2);
  display.setCursor(0, 10); // Move cursor up a bit
  display.print(counter);

  display.display(); // Display content
  delay(0); // Delay for readability, adjust as necessary
}

void beep() {
  tone(BUZZER_PIN, 1000, 100); // Play a short beep at 1000 Hz for 100 ms (0.1 second)
  delay(100); // Add a small delay before returning to avoid overlapping beeps
  noTone(BUZZER_PIN); // Turn off the buzzer after the beep
}
