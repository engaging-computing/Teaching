URL = 'http://rsense-dev.cs.uml.edu/api/v1/projects/683';
response = $.ajax({ type: "GET",
                url: URL,
                async: false,
                dataType: "JSON"
                }).responseText;
arg = JSON.parse(response);
=======
totalBases = [];

function get(){
    URL = 'http://rsense-dev.cs.uml.edu/api/v1/data_sets/1190?recur=true.json';
    response = $.ajax({ type: "GET",
                        url: URL,
                        async: false,
                        dataType: "JSON"
                    }).responseText;

    arg = JSON.parse(response);

    for (var i=0;i<30;i++) {
        totalBases.push(arg.data[i][647]) ;
    }

    console.log(totalBases);
}
