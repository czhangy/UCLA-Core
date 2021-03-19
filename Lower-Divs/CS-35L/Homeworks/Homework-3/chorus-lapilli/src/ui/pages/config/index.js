var expressRaptor = require('express-raptor');
var promises = require('raptor/promises');
var ConfigurationBuilder = require("context-config").ConfigurationBuilder;


exports.controller = expressRaptor.handler(function(context, req, res, next) {
        
    res.setHeader('Content-Type', 'text/html');

    new ConfigurationBuilder().build(context, {
            project:"searchm",
            config:"SRPKeywordRedirectTags",
            version:"1.0.0"
        })
        .then(function(config){
            context.renderTemplate(
                '/ui/pages/config/config.rhtml',
                {
                    configData: JSON.stringify(config.get("DRESS"))
                });
        })
        .done();
});