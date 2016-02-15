#!/usr/bin/env nodejs
/**
 * node-json-db test
 *
 * see https://github.com/louischatriot/nedb
 *
 * 2015, simon wunderlin
 */

console.log('Opening database');

var JsonDB = require('node-json-db');
//The second argument is used to tell the DB to save after each push 
//If you put false, you'll have to call the save() method. 
//The third argument is to ask JsonDB to save the database in an human readable 
// format. (default false) 
var db = new JsonDB("data/storage", true, true);

//Pushing the data into the database 
//With the wanted DataPath 
//By default the push will override the old value 
db.push("/test1","super test");
 
//It also create automatically the hierarchy when pushing new data for a DataPath that doesn't exists 
db.push("/test2/my/test",5);
 
//You can also push directly objects 
db.push("/test3", {test:"test", json: {test:["test"]}});
 
//If you don't want to override the data but to merge them 
//The merge is recursive and work with Object and Array. 
db.push("/3", {new:"cool", json: {important : 6}}, false);


