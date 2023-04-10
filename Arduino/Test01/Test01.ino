
#include <Stepper.h>
int motorSpeed =10;
Stepper myStepper(2048,8,10,9,11);
void setup() {
}
void loop() {
myStepper.setSpeed(motorSpeed);
myStepper.step(-2000);
delay(5000); // 1000 milliseconds (1 second)
myStepper.step(-2000); 
delay(5000);
}
