#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>

#define OLED_RESET    -1
Adafruit_SSD1306 display(OLED_RESET);

#define TRIG_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 200 // Maximum distance we want to measure (in centimeters)

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

int counter = 0;
bool belowThreshold = false;
bool aboveThreshold = false;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
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
  }
  
  // Reset thresholds when distance is below 10cm again
  if (distance <= 10 && aboveThreshold) {
    aboveThreshold = false;
  }
  
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(distance);
  display.print(" cm");
  display.setCursor(100, 0); // Set cursor to the right side of the screen
  display.print(counter); // Print the counter value
  display.display();
}
