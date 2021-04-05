#include "Arduino.h"
#include <BH1750.h>
#include "lightsensor.h"


float luxToUncalibratedEv(float lux){
    return (log(lux / 2.5) / log(2.));
}

float calibratedEv(float uncalibrated){
//    first attempt to linear fit
    float calibrated = uncalibrated * 2.45 - 5.03;
    return calibrated;
}

int luxToEv(float lux){
    return int(calibratedEv(luxToUncalibratedEv(lux)) * 100);
}
