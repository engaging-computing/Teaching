field_data_total_bases = [];

function GET(){

    URL = 'http://rsense-dev.cs.uml.edu/api/v1/data_sets/1190?recur=true.json';
    response = $.ajax({ type: "GET",
                        url: URL,
                        async: false,
                        dataType: "JSON"
                    }).responseText;

    arg = JSON.parse(response);

    for (var i=0;i<30;i++) {
        field_data_total_bases.push(arg.data[i][647]) ;
    }

    console.log(field_data_total_bases);
}