import json
import math
import os
import sys
from dataclasses import dataclass, asdict


def calculate_ev(shutter_speed, aperture):
    return int(math.log2(aperture ** 2 * shutter_speed) + 0.5)

def array_str(arr):
    return ", ".join((str(i) for i in arr))


header_file_template = """
#ifndef SHUTTERS_TABLE
    #define SHUTTERS_TABLE
#endif

#define LEN_SHUTTER_SPEEDS {len_shutter_speeds}
#define LEN_APERTURES {len_apertures}
#define SHUTTER_SPEEDS_MAX_INDEX {shutter_speeds_max_index}
#define APERTURES_MAX_INDEX {apertures_max_index}
#define MIN_EV {min_ev}
#define MAX_EV {max_ev}

extern int shutter_speeds[LEN_SHUTTER_SPEEDS];
extern int apertures[LEN_APERTURES];
"""


impl_file_template = """
#include "constants.h"

int shutter_speeds[] = {{{shutter_speeds_array_str}}};
int apertures[] = {{{apertures_array_str}}};
"""


@dataclass
class Context:
    len_shutter_speeds: int
    len_apertures: int
    shutter_speeds_max_index: int
    apertures_max_index: int
    min_ev: int
    max_ev: int
    shutter_speeds_array_str: str
    apertures_array_str: str

    @classmethod
    def build(cls, config):

        shutter_speeds = config['shutter_speeds']
        apertures = config['apertures']

        len_shutter_speeds = len(shutter_speeds)
        len_apertures = len(apertures)
        return cls(
            len_shutter_speeds=len(shutter_speeds),
            len_apertures=len(apertures),
            shutter_speeds_max_index=len_shutter_speeds - 1,
            apertures_max_index=len_apertures - 1,
            min_ev=calculate_ev(shutter_speeds[0], apertures[0]),
            max_ev=calculate_ev(shutter_speeds[-1], apertures[-1]),
            shutter_speeds_array_str=array_str(shutter_speeds),
            apertures_array_str=array_str([int(a * 10) for a in apertures]),
        )
    def collect_header(self):
        return header_file_template.format(**asdict(self))

    def collect_impl(self):
        return impl_file_template.format(**asdict(self))


if __name__ == "__main__":
    filename = sys.argv[1]
    header_filename = os.path.join('src', 'main', 'constants.h')
    impl_filename = os.path.join('src', 'main', 'constants.cpp')
    # filename = "fed5.json"
    with open(os.path.join("configs", filename)) as f:
        conf = json.load(f)
    context = Context.build(conf)

    with open(header_filename, "w") as f:
        f.write(context.collect_header())

    with open(impl_filename, "w") as f:
        f.write(context.collect_impl())
