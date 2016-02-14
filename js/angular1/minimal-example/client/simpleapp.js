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
		{name: "Simone", location: "Basel"},
		{name: "Andreas", location: "Lupsingen"},
		{name: "Sämi", location: "Basel"}
	];
	
	factory.getItems = function() {
		return items;
	};
	
	return factory;
});

SimpleApp.controller("appController", function ($scope, $location, $filter, appFactory) {
	$scope.items = appFactory.getItems();
	$scope.reverse = false;
	
	$scope.addItem = function() {
		$scope.items.push({
			name: $scope.newItem.name,
			location: $scope.newItem.location
		});
		$scope.newItem.name = "";
		$scope.newItem.location = "";
		$location.path('/');
	};
	
	var orderBy = $filter('orderBy');
	//$scope.reverse = true;
	$scope.order = function(predicate) {
		//alert(predicate)
		$scope.predicate = predicate;
		$scope.reverse = ($scope.predicate === predicate) ? !$scope.reverse : false;
		$scope.items = orderBy($scope.items, predicate, $scope.reverse);
	};
	//console.log($scope)
	//$scope.order('name', true);
});
