#!/usr/bin/env nodejs
/**
 * read/write/delete access via webservie to a json file
 * 
 * this service exposes an json file via http. it offers read/write and 
 * delete capabilities. it is possible to access a part of the json file 
 * by using url paths to traverse into the data structure.
 * 
 * Example data file:
 * {"a": 1, b: {"b1": 1, "b2": 2}}
 * 
 * accessing GET / will return the whole file as seen above.
 * accessing GET /b will return {"b1": 1, "b2": 2}
 * accessing an node end like GET/b/b1 will return {"value": 1}
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
 * Responses may send the following status codes
 * - 200, element found, action successful
 * - 404, element not found
 * - 500, failed to apply change or general server error
 *
 * 2016, simon wunderlin
 */
(function () {
'use strict';
var DEBUGGING = false;

// configuration
var port           = 8081; // port for the webserver
var db_file        = "storage.json"; // this is the file with the primary storage
var db_file_backup = "storage_backup.json"; // this shadow copy is for read access
var db_encoding    = "utf8"; // content and transfer encoding

// Globals
var colors = require('colors/safe');
var express = require('express');
var app = express();
var fs = require("fs");
var bodyParser = require('body-parser')

// set up http body parser
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

// on startup we check if the required data files are there, if not create 
// empty json files.
try {
	fs.lstatSync(db_file);
} catch (e) {
	console.log(e)
	fs.writeFile(db_file, "{}", function(err) {
		if(err) {
			console.log("Failed to create Datafile.");
			return console.log(err);
		}
	}); 
	fs.createReadStream(db_file).pipe(fs.createWriteStream(db_file_backup));
	console.log("Created data store: " + db_file);
}

/** 
 * Open json as database
 */
function get_db() {
	// https://www.npmjs.com/package/node-json-db
	var JsonDB = require('node-json-db');
	// The second argument is used to tell the DB to save after each push 
	// If you put false, you'll have to call the save() method. 
	// The third argument is to ask JsonDB to save the database in an human readable 
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
	
	// remove trailing slashes
	//console.log(data.url.substr(1, data.url.length-2))
	if (data.url.length > 1)
		if (data.url.substr(data.url.length-1) == "/")
			data.url = data.url.substr(0, data.url.length-1);
	
	//console.log(data.url)
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
			//console.log("fetching")
			data = db.getData(parameter.url);
		} catch(error) {
			// if not found, send 404
			//console.log("Error");
			res.status(404).send('<h1>404 File not found.</h1>');
			return false;			
		}
		// if found send json
		//console.log(data)
		var ret = JSON.stringify(data);
		if (ret.substr(0, 1) != '{')
			ret = '{"value":'+ret+'}'
		res.end(ret);
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

try {
	var server = app.listen(port, function () {
		var host = server.address().address
		var port = server.address().port
		console.log(colors.blue("Backend") + colors.green(" running on: ") + 
			          colors.red.bold("%s:%s"), host, port);
	});
} catch(error) {
	console.error("Failed to start server, is there arelady something else listeing on port " + port + "?");
	console.error(error.stack);
}

})();
