#!/usr/bin/env nodejs
/**
 * expose json file
 *
 * see http://www.tutorialspoint.com/nodejs/nodejs_restful_api.htm
 * 
 * Rest Api
 * +----+----------+--------+-------------+-----------------------------+
 * | ID | URI      | Method | POST body   | Result                      |
 * +----+----------+--------+-------------+-----------------------------+
 * |  1 | /        | GET    | empty       | Show item.                  |
 * |  2 | /        | POST   | JSON String | Add/Update item.            |
 * |  3 | /?delete | GET    | empty       | Delete an existing item.    |
 * +----+----------+--------+-------------+-----------------------------+
 * 
 * 2015, simon wunderlin
 */
'use strict';

var DEBUGGING = true;

var db_file = "storage.json";
var db_file_backup = "storage_backup.json";
var db_encoding = "utf8";

var colors = require('colors/safe');
var express = require('express');
var app = express();
var fs = require("fs");
var bodyParser = require('body-parser')

// set up http body parser
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

/** 
 * Open json as database
 */
function get_db() {
	// https://www.npmjs.com/package/node-json-db
	var JsonDB = require('node-json-db');
	//The second argument is used to tell the DB to save after each push 
	//If you put false, you'll have to call the save() method. 
	//The third argument is to ask JsonDB to save the database in an human readable 
	// format. (default false) 
	return new JsonDB(db_file.split('.')[0], false, DEBUGGING);
}

function store_db(db, path, data) {
	// store data
	db.push(path, data);
	db.save()
	// create shadow copy
	fs.createReadStream(db_file).pipe(fs.createWriteStream(db_file_backup));
	return true;
}

function handle_request(req, res) {
	var data = {
		//baseUrl: req.baseUrl,
		url: req.originalUrl,
		route: req.route,
		query: req.query,
		//url: req.url,
		method: req.method
	};
	
	// remove query string from path
	var p = data.url.indexOf('?');
	if (p > 0) {
		data.url = data.url.substr(0, p);
	}
	data.url = decodeURIComponent(data.url);
	return data;
}

// our special form for testing
if (DEBUGGING) {
	app.get('/test', function (req, res) {
		fs.readFile( __dirname + "/test.html", db_encoding, function (err, data) {
			res.end(data);
		});
		return true;
	});
}

// global url handling
app.use(function(req, res, next) {
	//res.status(404).send('Sorry cant find that!');
	var parameter = handle_request(req, res);
	//res.send(parameter);
	//console.log(parameter)
	
	// if "/" was requested and method is GET, just send out the shadow copy 
	// of the file and quit. we do this to prevent locking problems
	// we expect GET / to be the most common request
	if ((parameter.url == "" || parameter.url == "/") && 
	     parameter.method == "GET") {
		fs.readFile( __dirname + "/" + db_file_backup, db_encoding, function (err, data) {
			res.end(data);
		});
		return true;
	}
	
	// open json file
	var db = get_db();
	
	// handle GET requests to partial data
	if (parameter.method == "GET") {
		// delete object ?
		if ("delete" in parameter.query) {
			console.log("Deleting " + parameter.url);
			try {
				db.delete(parameter.url);
				db.save();
				fs.createReadStream(db_file).pipe(fs.createWriteStream(db_file_backup));
				res.end("");
				return true;
			} catch(error) {
				res.status(500).send('<h1>500 Failed to delete Object.</h1>');
				return false;			
			}
		}
		
		var data = {};
		try {
			console.log("fetching")
			data = db.getData(parameter.url);
		} catch(error) {
			// if not found, send 404
			console.log("Error");
			res.status(404).send('<h1>404 File not found.</h1>');
			return false;			
		}
		// if found send json
		//console.log(data)
		res.end(JSON.stringify(data));
		return true;
	}
				
	// POST
	if (parameter.method == "POST") {
		// store element, send empty response on success
		try {
			store_db(db, parameter.url, req.body)
			res.end("");
		} catch(error) {
			console.error(err.stack);
			res.status(500).send('Something broke!');
		}
		return true;
	}
	
});

// handle server errors
app.use(function(err, req, res, next) {
  console.error(err.stack);
  res.status(500).send('Something broke!');
});

var server = app.listen(8081, function () {

  var host = server.address().address
  var port = server.address().port
  console.log(colors.blue("Backend") + colors.green(" running on: ") + 
              colors.red.bold("%s:%s"), host, port)

});
