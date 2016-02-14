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
 * +-------+------------+--------+-------------+-----------------------------+
 * | S. N. | URI        | Method | POST body   | Result                      |
 * +-------+------------+--------+-------------+-----------------------------+
 * |     1 | get        | GET    | empty       | Show list of all the items. |
 * |     2 | post       | POST   | JSON String | Add/Update  item.           |
 * |     3 | delete     | DELETE | JSON String | Delete an existing item.    |
 * |     4 | :path      | GET    | empty       | Show details of an item.    |
 * +-------+------------+--------+-------------+-----------------------------+
*/

app.get('/get', function (req, res) {
   fs.readFile( __dirname + "/" + db_file, db_encoding, function (err, data) {
       //console.log( data );
       res.end( data );
   });
});

app.get('/get', function (req, res) {
   fs.readFile( __dirname + "/" + db_file, db_encoding, function (err, data) {
       //console.log( data );
       res.end( data );
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
