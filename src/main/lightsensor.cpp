#include "Arduino.h"
#include <BH1750.h>
#include "lightsensor.h"
#include <Wire.h>

BH1750 lightMeter;

void lightsensorSetup(){
    lightMeter.begin();
}

float getlux(){
    return lightMeter.readLightLevel();
}
