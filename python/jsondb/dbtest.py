#!/usr/bin/python
# https://pypi.python.org/pypi/jsondatabase/

from os.path import dirname, realpath, sep, pardir
import sys
sys.path.append(dirname(realpath(__file__)) + sep  + "jsondatabase-0.1.1")
#print dirname(realpath(__file__)) + sep  + "jsondb-0.1.2"
from jsondb.db import Database

def main():
	# Create tmp db file in /tmp
	#db = jsondb.create({}) 
	# Create sqlite database
	#db = jsondb.create({}, url='data.db')
	
	# load database
	db = Database("data.json")
	db.data(key="user_count", value=241)
	data = {
		"user_id": 234565,
		"user_name": "AwesomeUserName",
		"is_moderator": True,
	}
	db.data(dictionary=data)
	print db.data()

if __name__ == '__main__':
	main()
