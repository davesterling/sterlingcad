#include <Servo.h>

Servo myservo;  // Create a servo object

void setup() {
  myservo.attach(22);  // Attach the servo to digital pin 9 (you can change this to your servo's pin)
}

void loop() {
  // Move the servo to 0 degrees (fully counter-clockwise)
  myservo.write(0);
  delay(1000);  // Wait for 1 second
  
  // Move the servo to 180 degrees (fully clockwise)
  myservo.write(180);
  delay(1000);  // Wait for 1 second
}
