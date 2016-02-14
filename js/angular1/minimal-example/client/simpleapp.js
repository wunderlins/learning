/* 
 * License: GPL2
 * Author: Simon Wunderlin
 * Copyright, 2015, simon Wunderlin
 */
var SimpleApp = angular.module("SimpleApp", ['ui.bootstrap'])
.factory("appFactory", function() {
	var factory = {};
	var items = [
		{name: "name 1", location: "location 1"},
		{name: "name 3", location: "location 3"},
		{name: "name 2", location: "location 2"}
	];
	
	factory.getItems = function() {
		return items;
	};
	
	return factory;
})
.controller("appController", function ($scope, appFactory) {
	$scope.items = appFactory.getItems();
	
	$scope.addItem = function() {
		$scope.items.push({
			name: $scope.newItem.name,
			location: $scope.newItem.location
		});
		$scope.newItem.name = "";
		$scope.newItem.location = "";
	};
});
