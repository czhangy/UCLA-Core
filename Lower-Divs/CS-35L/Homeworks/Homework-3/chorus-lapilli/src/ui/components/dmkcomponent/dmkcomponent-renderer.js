define(
    'ui/components/dmkcomponent/dmkcomponent-renderer',
    function(require) {
        var templating = require('raptor/templating');

        return {
            render: function(input, context) {
                templating.render('ui/components/dmkcomponent', {
                    name: input.name,
                    count: input.count
                }, context);
            }
        };
    });