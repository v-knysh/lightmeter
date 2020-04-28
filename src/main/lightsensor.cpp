#include "Arduino.h"
#include <BH1750.h>
#include "lightsensor.h"

BH1750 lightMeter;

void lightsensorSetup(){
    lightMeter.begin();
}

float getlux(){
    return lightMeter.readLightLevel();
}
