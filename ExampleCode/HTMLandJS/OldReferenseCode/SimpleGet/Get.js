"use strict";
var totalBases = [];

function get(){

    var url = 'http://rsense-dev.cs.uml.edu/api/v1/data_sets/1190';
    var response = $.ajax({ type: "GET",
                        url: url,
                        async: false,
                        dataType: "JSON"
    }).responseText;

    var parsedResponse = JSON.parse(response);

    for (var i=0;i<30;i++) {
        totalBases.push(parsedResponse.data[i][647]) ;
    }

    console.log(parsedResponse);
}
