#include <Servo.h>

Servo servoMotor;
 
void setup() {
 
 servoMotor.attach(9);
}
 
void loop() {

  for(int i = 0; i <= 120; i += 60) {
    servoMotor.write(i);
    delay(1000);
  }

  for(int i = 180; i >= 60; i -= 60) {
    servoMotor.write(i);
    delay(1000);
  }
}
