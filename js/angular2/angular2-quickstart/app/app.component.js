(function(app) {
  app.AppComponent =
    ng.core.Component({
      selector: 'my-app',
      template: '<h2>My First Angular 2 App</h2>'
    })
    .Class({
      constructor: function() {}
    });
})(window.app || (window.app = {}));
