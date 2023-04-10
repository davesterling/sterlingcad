#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

// Define the pin configurations
#define TRIG_PIN 6  
#define ECHO_PIN 4  
#define BUZZER_PIN 9 
#define BUTTON_PIN 2 
#define MAX_DISTANCE 200 
#define DIRECTION_CHANGE_THRESHOLD 10 

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

int counter = 0;
bool belowThreshold = false;
bool aboveThreshold = false;
bool lowToneDirectionChange = false;
int lastDistance = 0;
int upperThreshold = 40;
int currentState = 0;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Initialize OLED with I2C address 0x3C
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Set Distance");
  display.display();  // Display the "Set Distance" message

  while (digitalRead(BUTTON_PIN) == HIGH) {
    delay(100);
  }

  upperThreshold = sonar.ping_cm();
  currentState = 1;

  // Clear the display after setting the threshold
  display.clearDisplay();
  display.display();
}

void loop() {
  delay(50);

  int distance = sonar.ping_cm();

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
    counter++;
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
    if (distance > 10 && distance < 40) {
      if (lowToneDirectionChange) {
        playLowPitchedBeep();
        lowToneDirectionChange = false;
      } else {
        lowToneDirectionChange = true;
      }
    }
  }

  lastDistance = distance;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // Print distance
  display.setCursor(0, 0);
  display.print("Distance: ");
  display.print(distance);
  display.print(" cm");
  
  // Print counter with larger font size (2) and moved up (Y-coordinate adjusted)
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print(counter);

  display.display();
}

void playHighPitchedBeep() {
  tone(BUZZER_PIN, 1000, 100);
  delay(100);
  noTone(BUZZER_PIN);
}

void playLowPitchedBeep() {
  tone(BUZZER_PIN, 500, 500);
  delay(500);
  noTone(BUZZER_PIN);
}
