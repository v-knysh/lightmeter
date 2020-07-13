#include "Arduino.h"
#include <Servo.h>
#include "servo.h"

Servo servo;

float totalWigth = 180;
float numOfStops = 8;




void servoSetup(int servoPin){
    servo.attach(servoPin);
}

void showOnServo(float num){
    servo.write(22.5 * num);
    delay(1000);
}
