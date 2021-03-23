#include <math.h>
#include "Arduino.h" 
#include "shutter_table.h"


int shutter_speeds[] = {30, 60, 125, 250, 500};
int apertures[] = {28, 40, 56, 80, 110, 160};

int len_shutter_speeds = 5;
int len_apertures = 6;
int shutter_speeds_max_index = len_shutter_speeds - 1;
int apertures_max_index = len_apertures - 1;


int MIN_EV = 8;
int MAX_EV = 17;

int CODE_MIN_EV = -1;
int CODE_MAX_EV = -2;
int CODE_EV_OK = -4;
int CODE_NO_MORE_PAIRS = -3;


int first_shutter_speed_index(int ev){
  int delta_ev = ev - MIN_EV;
  return min(delta_ev, shutter_speeds_max_index);
}

int first_aperture_index(int ev){
  int delta_ev = ev - MIN_EV;
  int delta = delta_ev - shutter_speeds_max_index;
  return max(delta, 0);
}

int total_pairs_amount(int first_shutter_speed_index, int first_aperture_index){
  int delta = apertures_max_index - first_aperture_index;
  return min(first_shutter_speed_index, delta);
}

ShutterAperturePair::ShutterAperturePair(){
    _status = 0;
    _first_shutter_speed_index = 0;
    _first_aperture_index = 0;
    _amount_pairs = 0;
}

int ShutterAperturePair::shutter_speed(int index){
    return shutter_speeds[_first_shutter_speed_index - index];
}

int ShutterAperturePair::aperture_value(int index){
    return apertures[_first_aperture_index + index];
}

int ShutterAperturePair::status(){
    return _status;
}

int ShutterAperturePair::amount_pairs(){
    return _amount_pairs;
}

void ShutterAperturePair::update(int ev){
  if (ev < MIN_EV){
    _status = CODE_MIN_EV;
    _first_shutter_speed_index = 0;
    _first_aperture_index = 0;
    _amount_pairs = 1;
    return 0;
  }
  if (ev > MAX_EV){
    _status = CODE_MAX_EV;
    _first_shutter_speed_index = shutter_speeds_max_index;
    _first_aperture_index = apertures_max_index;
    _amount_pairs = 1;
    return 0;
  }
  _first_shutter_speed_index = first_shutter_speed_index(ev);
  _first_aperture_index = first_aperture_index(ev);
  _amount_pairs = total_pairs_amount(_first_shutter_speed_index, _first_aperture_index);
  _status = CODE_EV_OK;
  return 0;
}
