exports.addRoutes = function(app, env) {
    app.get("/dmkpage", require("./src/ui/pages/dmkpage").controller);    
    app.get('/hello', require('./src/ui/pages/hello').controller);
    app.get('/keywords/:keywords', require('./src/ui/pages/search-results').controller);
    app.get('/ui-components', require('./src/ui/pages/ui-components').controller);
    app.get("/config", require("./src/ui/pages/config").controller);
    app.get("/async-fragments", require("./src/ui/pages/async-fragments").controller);
    app.get('/', require('./src/ui/pages/index').controller);
};
