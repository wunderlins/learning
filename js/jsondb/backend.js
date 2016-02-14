#!/usr/bin/env node
/**
 * expose json file
 *
 * see http://www.tutorialspoint.com/nodejs/nodejs_restful_api.htm
 *
 * 2015, simon wunderlin
 */

var db_file = "data/storage.json";
var db_encoding = "utf8";

var colors = require('colors/safe');
var express = require('express');
var app = express();
var fs = require("fs");

/*
 * Rest Api
 * 
 * +----+-----+--------+-------------+-----------------------------+
 * | ID | URI | Method | POST body   | Result                      |
 * +----+-----+--------+-------------+-----------------------------+
 * |  1 | /   | GET    | empty       | Show item.                  |
 * |  2 | /   | POST   | JSON String | Add/Update item.            |
 * |  3 | /   | DELETE | empty       | Delete an existing item.    |
 * +----+-----+--------+-------------+-----------------------------+
*/

var api = function() {
	return [
		{method: "get",     post: false, comment: "Show Item."},
		{method: "post",    post: true,  comment: "Add/Update item."},
		{method: "delete",  post: false, comment: "Delete an existing item."},
	];
}

app.get('/', function (req, res) {
	/*
	//console.log(req);
	console.log(req.query);
	console.log(req.originalUrl);
	console.log(req.route);
	//console.log(res);
	*/
	fs.readFile( __dirname + "/" + db_file, db_encoding, function (err, data) {
		//console.log( data );
		res.end(data);
	});
});

/*
var user = {
   "user4" : {
      "name" : "mohit",
      "password" : "password4",
      "profession" : "teacher",
      "id": 4
   }
};

app.get('/addUser', function (req, res) {
   // First read existing users.
   fs.readFile( __dirname + "/" + db_file, db_encoding, function (err, data) {
       data = JSON.parse( data );
       data["user4"] = user["user4"];
       console.log( data );
       res.end( JSON.stringify(data));
   });
});
*/

var server = app.listen(8081, function () {

  var host = server.address().address
  var port = server.address().port
  console.log(colors.blue("Backend") + colors.green(" running on: ") + 
              colors.red.bold("%s:%s"), host, port)

});
