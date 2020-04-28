#include "SevSeg.h"
#include <math.h>  
#include <Wire.h>
#include <BH1750.h>
#include <Servo.h>


BH1750 lightMeter;
Servo servo;  
SevSeg sevseg; //Instantiate a seven segment object

int loopDelay = 1000;
int lux = 0;
int ev = 0;
int lastTimerLoop = 0;
int servoAngle = 0;
int servoPin = 12;


byte evMin = 5;
byte evRange = 9; // 9 marks in circle

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  // setup sevenseg  
  byte numDigits = 2;
  byte digitPins[] = {7, 2};
  byte segmentPins[] = {9, 3, 4, 6, 5, 8, 11, 10};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
   Wire.begin();
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(100);

  //  setup lightmeter
  lightMeter.begin();

  //  setup servo
  servo.attach(servoPin);


}

void loop() {
  // run sevseg in external loop, delay for timers
  
  
  
  sevseg.setNumber(ev, 0);
  sevseg.refreshDisplay();


  if (millis() - lastTimerLoop > loopDelay) {

    
    lux = (int) lightMeter.readLightLevel();
    ev = (int) (log(lux / 2.5) / log(2));
//    lux ++;

    byte evNormalized = min(max(ev - evMin, 0), evRange);
    servoAngle = ((evNormalized)  * (172 / evRange)) + 4;
//    if (servoAngle < 176 && servoAngle > 4){
    servo.write(servoAngle);
//    }
  
    
    Serial.print(" lux: ");
    Serial.print(lux);
    Serial.print(" ev: ");
    Serial.print(ev);
    Serial.print(" servoAngle: ");
    Serial.println(servoAngle);
    
    lastTimerLoop =   millis();
  
  }


}
