/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
var SimpleApp = angular.module("SimpleApp", ['ui.bootstrap']);

function appController($scope) {
  $scope.items = [
    {name: "name 1", location: "location 1"},
    {name: "name 3", location: "location 3"},
    {name: "name 2", location: "location 2"}
  ];
};

SimpleApp.controller("appController", appController);


