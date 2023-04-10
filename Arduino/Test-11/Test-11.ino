

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);



#define TRIG_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 200 // Maximum distance we want to measure (in centimeters)

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

int counter = 0;
bool belowThreshold = false;
bool aboveThreshold = false;

void setup() {
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
display.print("Counter: ");
display.print(counter);

display.display(); // Display content
  delay(0); // Delay for readability, adjust as necessary
}
