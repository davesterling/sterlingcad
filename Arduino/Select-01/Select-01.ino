#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>

#define TRIGGER_PIN   6
#define ECHO_PIN      4
#define BUTTON_PIN    2
#define BUZZER_PIN    9
#define OLED_RESET    -1
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS  0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
NewPing sonar(TRIGGER_PIN, ECHO_PIN);

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();
}

void selectProgram() {
  int distance = getDistance();
  display.clearDisplay();

  if (distance >= 0 && distance <= 3) {
    displayCenteredText("User1");
  } else if (distance > 3 && distance <= 6) {
    displayCenteredText("User2");
  } else if (distance > 6 && distance <= 9) {
    displayCenteredText("User3");
  }

  delay(5000);  // Display for 5 seconds
}

void displayCenteredText(const char* text) {
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor((SCREEN_WIDTH - display.getCursorX()) / 2, 16);
  display.println(text);
  display.display();
}

int getDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  return sonar.ping_cm();
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW) {
    tone(BUZZER_PIN, 1000, 100);  // Optional: Add a buzzer sound
    selectProgram();
    noTone(BUZZER_PIN);
  }
}
