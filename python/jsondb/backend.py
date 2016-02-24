#!/usr/bin/env python
# -*- coding: utf-8 -*-

### intialize the json database we work on
from os.path import dirname, realpath, sep, pardir
import sys
sys.path.append(dirname(realpath(__file__)) + sep  + "jsondatabase-0.1.1")
print dirname(realpath(__file__)) + sep  + "jsondatabase-0.1.1"
from jsondb.db import Database

if __name__ == '__main__':
	print sys.argv
	#db = Database(sys.argv[1])
	pass
