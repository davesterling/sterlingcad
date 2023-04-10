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

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  delay(500); // Wait for a short time before taking the reading
  int distance = sonar.ping_cm(); // Get the distance in centimeters
  
  display.clearDisplay();
  display.setTextSize(3); // Increase text size for better visibility
  display.setTextColor(WHITE);
  display.setCursor(0, 0); // Set cursor to top-left corner
  display.print(distance); // Print the distance value
  display.print(" cm"); // Print unit
  display.display();
}
