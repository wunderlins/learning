#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Serve one or many json files over a REST service

If one file is provided, then the service will mount the file at the root url
and the data is accessible at <http://ip:port/>.

If there are many files provided, the data will be made available under and uri
with the same name as the file (without extension). For example of serving 2
json files:

$ ./backend.py -i 127.0.0.1 -p 9999 file1.json file2.json

file's content will be exposed at:
http://127.0.0.1:9999/file1/
http://127.0.0.1:9999/file2/
every subequent sub-folder is a cild object of the root json node.

2016, Simon Wunderlin
"""
DESC="Serve one or many json files over a REST service"
DEFAULT_PORT=8080
DEFAULT_IP="127.0.0.1"

### intialize the json database we work on
from os.path import dirname, realpath, sep, pardir
import sys
sys.path.append(dirname(realpath(__file__)) + sep  + "jsondatabase-0.1.1")
#print dirname(realpath(__file__)) + sep  + "jsondatabase-0.1.1"
from jsondb.db import Database
import argparse
from argparse import RawTextHelpFormatter

def start_server(ip, port):
	pass

def start_database(files):
	pass


if __name__ == '__main__':
	parser = argparse.ArgumentParser(formatter_class=RawTextHelpFormatter, 
	                                 epilog=__doc__, 
	                                 description=DESC)
	parser.add_argument("-p", "--port", 
	                    type=int, 
	                    help="tcp port number, default "+str(DEFAULT_PORT),
	                    default=DEFAULT_PORT)
	parser.add_argument("-i", "--ip",
	                    help="listening ip, 0.0.0.0 all, default "+DEFAULT_IP,
	                    default=DEFAULT_IP)
	parser.add_argument("jsonfile", nargs='+', 
	                    help="One or many paths to json files to be served.")
	args = parser.parse_args()
	
	print sys.argv
	#db = Database(sys.argv[1])
	pass
