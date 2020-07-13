#include <math.h>
#include <Wire.h>
#include "lightsensor.h"
#include "light_calc.h"
#include "monitor.h"
#include <Servo.h>



float lux = 0;
float ev = 0;

Servo servo;
int angle = 10;


void setup() {
    Serial.begin(9600);
    lightsensorSetup();
    monitorSetup();
    servo.attach(7);
}

void loop() {
    lux = getlux();
    ev = luxToEv(lux);
    print(" lux: ", lux);
    print(" ev: ", ev);
    showOneDecimalPrecision(ev);
   // Expect: ev with one decimal precision
    delay(1000);
    
    servo.write(22.5 * ev);   
    delay(1000);            
}

void print(String key, String val) {
    Serial.print(key);
    Serial.print(val);
    Serial.println(";");
}
void print(String key, int val) {
    print(key, String(val));
}
void print(String key, float val) {
    print(key, String(val));
}
void print(String key, double val) {
    print(key, String(val));
}
