<<<<<<< HEAD:ExampleCode/HTML5/SimpleGet/Get.js
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
>>>>>>> 6c7f8e691b43d72c3773d99c18f8907b91e2c5e4:ExampleCode/HTMLandJS/SimpleGet/Get.js

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
