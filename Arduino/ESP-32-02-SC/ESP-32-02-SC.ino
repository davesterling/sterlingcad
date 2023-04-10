#include <Adafruit_GFX.h>
#include <TFT_eSPI.h>

#define TFT_CS   5
#define TFT_DC   21
#define TFT_RST  22
#define TFT_BL   18 // Backlight pin, change it to GPIO 18

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH); // Turn on the backlight
}

void loop() {
  tft.setCursor(10, 10);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  tft.print("Hi!");

  delay(5000);

  tft.fillScreen(TFT_BLACK);

  delay(1000); // Give some time before turning on the backlight again

  digitalWrite(TFT_BL, LOW); // Turn off the backlight
  delay(5000);

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(10, 10);
  tft.print("Bye!");

  delay(5000);

  tft.fillScreen(TFT_BLACK);

  delay(1000); // Give some time before turning on the backlight again

  digitalWrite(TFT_BL, HIGH); // Turn on the backlight
  delay(5000);
}
