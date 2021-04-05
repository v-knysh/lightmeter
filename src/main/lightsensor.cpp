#include "Arduino.h"
#include <BH1750.h>
#include "lightsensor.h"

BH1750 lightMeter;
//
//int prev_lux_scan_time = 0;
float prev_lux_scan_value = 0;

void lightsensorSetup(){
    lightMeter.begin();
}

float getlux(){
    prev_lux_scan_value = lightMeter.readLightLevel();


//    int curr_time = millis();
//    if (prev_lux_scan_time + 1000 < curr_time) {
//        prev_lux_scan_time = curr_time;
//        prev_lux_scan_value = lightMeter.readLightLevel();
//    }
    return prev_lux_scan_value;
}
