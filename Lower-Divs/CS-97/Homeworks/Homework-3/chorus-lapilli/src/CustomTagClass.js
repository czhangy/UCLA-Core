define(
    'CustomTagClass',
    function(require) {
        
        return {
            render: function(input, context) {
                context.write('Hello ' + input.name + '!');
            }
        };
    });