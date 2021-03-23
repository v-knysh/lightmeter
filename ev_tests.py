import math
import random

times = [30, 60, 125, 250, 500, 1000]
shutters = [2.8, 4, 5.6, 8, 11, 16]
len_times = len(times)
len_shutters = len(shutters)

times_max_index = len_times - 1
shutters_max_index = len_shutters - 1

CODE_MIN_EV = -1
CODE_MAX_EV = 1
CODE_EV_OK = 0
CODE_NO_MORE_PAIRS = 4


min_ev = int(math.log2(shutters[0] ** 2 * times[0]) + 0.5)
max_ev = int(math.log2(shutters[-1] ** 2 * times[-1]) + 0.5)


def indexes_of_time_shutter(ev, count):
    if ev < min_ev:
        return 0, 0, CODE_MIN_EV
    if ev > max_ev:
        return times_max_index, shutters_max_index, CODE_MAX_EV

    first_shutter_index, first_time_index = first_indexes(ev)

    total_pairs_count = total_pairs_amount(first_shutter_index, first_time_index)
    if count + 1 > total_pairs_count:
        return 0, 0, CODE_NO_MORE_PAIRS

    time_index = first_time_index - count
    shutter_index = first_shutter_index + count

    return time_index, shutter_index, CODE_EV_OK


def total_pairs_amount(first_shutter_index, first_time_index):
    total_pairs_count = min(first_time_index, shutters_max_index - first_shutter_index) + 1
    return total_pairs_count


def first_indexes(ev):
    delta_ev = ev - min_ev
    first_time_index = min(delta_ev, times_max_index)
    first_shutter_index = max(delta_ev - times_max_index, 0)
    return first_shutter_index, first_time_index


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
        print(f"ev: {ev}, t: {times[t]}, s: {shutters[s]} {err_str}")
        if code != CODE_EV_OK:
            break



for ev in range(7, 19):
    find_pairs(ev)

for i in range(10):
    lux = random.random() * 2**32
    ev = math.log2(lux / 2.5)

