/* 
 * License: GPL2
 * Author: Simon Wunderlin
 * Copyright, 2015, simon Wunderlin
 */
var SimpleApp = angular.module("SimpleApp", ['ui.bootstrap', 'ngRoute']);

SimpleApp.config(['$routeProvider',
  function($routeProvider) {
    $routeProvider.
      when('/', {
        templateUrl: 'partials/list.html',
        controller: 'appController'
      }).
			/*
      when('/phones/:phoneId', {
        templateUrl: 'partials/phone-detail.html',
        controller: 'PhoneDetailCtrl'
      }).
			*/
      when('/add', {
        templateUrl: 'partials/add.html',
        controller: 'appController'
      }).
      otherwise({
        redirectTo: '/'
      });
  }]);

SimpleApp.factory("appFactory", function() {
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
});

SimpleApp.controller("appController", function ($scope, $location, appFactory) {
	$scope.items = appFactory.getItems();
	
	$scope.addItem = function() {
		$scope.items.push({
			name: $scope.newItem.name,
			location: $scope.newItem.location
		});
		$scope.newItem.name = "";
		$scope.newItem.location = "";
		$location.path('/');
	};
});
