import math
import random

shutter_speeds = [30, 60, 125, 250, 500, 1000]
apertures = [2.8, 4, 5.6, 8, 11, 16]

len_shutter_speeds = len(shutter_speeds)
len_apertures = len(apertures)

shutter_speeds_max_index = len_shutter_speeds - 1
apertures_max_index = len_apertures - 1

CODE_MIN_EV = -1
CODE_MAX_EV = -2
CODE_NO_MORE_PAIRS = -3
CODE_EV_OK = -4

def calculate_ev(shutter_speed, aperture):
    return int(math.log2(aperture ** 2 * shutter_speed) + 0.5)

min_ev = calculate_ev(shutter_speeds[0], apertures[0])
max_ev = calculate_ev(shutter_speeds[-1], apertures[-1])


def indexes_of_time_shutter(ev, count):
    if ev < min_ev:
        return 0, 0, CODE_MIN_EV
    if ev > max_ev:
        return shutter_speeds_max_index, apertures_max_index, CODE_MAX_EV

    first_shutter_speed_index, first_aperture_index = first_indexes(ev)

    total_pairs_count = total_pairs_amount(first_shutter_speed_index, first_aperture_index)
    if count + 1 > total_pairs_count:
        return 0, 0, CODE_NO_MORE_PAIRS

    time_index = first_shutter_speed_index - count
    shutter_index = first_aperture_index + count

    return time_index, shutter_index, CODE_EV_OK


def total_pairs_amount(first_shutter_speed_index, first_aperture_index):
    total_pairs_count = min(first_shutter_speed_index, apertures_max_index - first_aperture_index) + 1
    return total_pairs_count


def first_indexes(ev):
    delta_ev = ev - min_ev
    first_shutter_speed_index = min(delta_ev, shutter_speeds_max_index)
    first_aperture_index = max(delta_ev - shutter_speeds_max_index, 0)
    return first_shutter_speed_index, first_aperture_index


def find_pairs(ev):
    for i in range(7):
        t, s, code = indexes_of_time_shutter(ev, i)
        if code == CODE_NO_MORE_PAIRS:
            break
        err_str = ""
        if code == CODE_MAX_EV:
            err_str = "+"
        if code == CODE_MIN_EV:
            err_str = "-"
        print(f"ev: {ev}, t: {shutter_speeds[t]}, s: {apertures[s]} {err_str}")
        if code != CODE_EV_OK:
            break



for ev in range(7, 19):
    find_pairs(ev)

for i in range(10):
    lux = random.random() * 2**32
    ev = math.log2(lux / 2.5)

