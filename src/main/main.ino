#include <math.h>
#include <Wire.h>
// #include "lightsensor.h"
#include "light_calc.h"
// #include "monitor.h"
// #include "servo.h"
#include "expopairs.h"
#include "oled_monitor.h"

float lux = 0;
float ev = 0;

int servoPin = 7;

int qwe = 0;

Expopair expopair;
OledMonitor oled_monitor;

void setup() {
    Serial.begin(9600);
//    lightsensorSetup();
//    monitorSetup();
//    servoSetup(7);
    oled_monitor.setup();


}

void loop() {
//     lux = getlux();
    ev = luxToEv(10.);
    print(" lux: ", lux);
    expopair.update(ev);
    int pairs = expopair.amount_pairs();

    print(" ev: ", ev);
    print(" aperture_value: ", String(expopair.aperture_value(0) / 10) + '.' + String(expopair.aperture_value(0) % 10));
    print(" shutter_speed: ", expopair.shutter_speed(0));
    print(" status: ", expopair.status_str());
    print("------------------------------: ", 0);

    oled_monitor.set_iso(200);
    oled_monitor.set_top_av(28);
    oled_monitor.set_top_t(125);
    oled_monitor.set_main_av(40);
    oled_monitor.set_main_t(60);
    oled_monitor.set_bottom_av(56);
    oled_monitor.set_bottom_t(30);
    oled_monitor.set_status_str("+");

    oled_monitor.render();
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
void print(String key, char val) {
    print(key, String(val));
}
