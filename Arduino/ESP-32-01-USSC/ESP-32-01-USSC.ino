#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <NewPing.h>

#define TRIG_PIN 2  // GPIO2 for Ultrasonic Trig
#define ECHO_PIN 15 // GPIO15 for Ultrasonic Echo
#define TFT_CS 5    // GPIO5 for TFT CS
#define TFT_DC 4    // GPIO4 for TFT DC
#define TFT_RST 18  // GPIO18 for TFT RST
#define TFT_SDA 21  // GPIO21 for TFT SDA
#define TFT_SCL 22  // GPIO22 for TFT SCL

Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST, TFT_SDA, TFT_SCL);

NewPing sonar(TRIG_PIN, ECHO_PIN);

bool belowThreshold = false;
bool aboveThreshold = false;
int counter = 0;

void setup() {
  Serial.begin(115200);

  // Initialize TFT display
  display.begin();
  display.setRotation(3); // Adjust the rotation as needed
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
    // beep(); // Call the function to beep - add your beep function here if needed
  }

  // Reset thresholds when distance is below 10cm again
  if (distance <= 10 && aboveThreshold) {
    aboveThreshold = false;
  }

  display.fillScreen(ILI9341_BLACK); // Clear the screen
  display.setTextSize(1);            // Reduce text size for other text
  display.setTextColor(ILI9341_WHITE);

  // Print distance
  display.setCursor(0, 0);
  display.print("Distance: ");
  display.print(distance);
  display.print(" cm");

  // Print counter with larger font size (2) and moved up (Y-coordinate adjusted)
  display.setTextSize(2);
  display.setCursor(0, 20); // Adjust Y-coordinate
  display.print(counter);

 // Display content
  delay(0);          // Delay for readability, adjust as necessary
}
