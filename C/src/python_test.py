#!/usr/bin/env python

import pylibshift
import array

a=array.array('i',(0 for i in range(0,8)))

pylibshift.set_point(4, 4, True, a)

for i in range(len(a)):
	print a

