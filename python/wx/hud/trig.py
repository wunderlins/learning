#!/usr/bin/env python

from math import *

adjacent = 5
opposite = 3.0

t = degrees(atan(opposite/adjacent))

def angle_deg(adjacent, opposite):
    """ calculate the angle of a right triangle from oppsite and adjacent """
    return degrees(atan(opposite/adjacent));

print angle_deg(adjacent, opposite)