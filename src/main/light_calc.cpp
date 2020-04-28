#include "Arduino.h"
#include <BH1750.h>
#include "lightsensor.h"


float luxToUncalibratedEv(float lux){
    return (log(lux / 2.5) / log(2.));
}

float calibratedEv(float uncalibrated){
    float calibrated = uncalibrated;
    return calibrated;
}

float luxToEv(float lux){
    return calibratedEv(luxToUncalibratedEv(lux));
}
