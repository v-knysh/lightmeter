#include "Arduino.h"
#include <BH1750.h>
#include "lightsensor.h"


float luxToUncalibratedEv(float lux){
    return (log(lux / 2.5) / log(2.));
}

float calibratedEv(float uncalibrated){
    float calibrated = uncalibrated;
    return max(calibrated, 0.1);
}

int luxToEv(float lux){
    return int(calibratedEv(luxToUncalibratedEv(lux)) * 100);
}
