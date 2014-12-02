var totalBases = [];

function getDataset(projectID,fieldName){

    var urlProject = 'http://rsense-dev.cs.uml.edu/api/v1/projects/' + projectID;
    var responseProject = $.ajax({ type: "GET",
                        url: urlProject,
                        async: false,
                        dataType: "JSON"
                    }).responseText;

    var parsedResponseProject = JSON.parse(responseProject);

    for(var i = 0; i < parsedResponseProject.fieldCount; i++) {


        if(parsedResponseProject.fields[i].name == fieldName) {

            alert("HEYY")
            fieldID = parsedResponseProject.fields[i].id;

            var urlDataset = 'http://rsense-dev.cs.uml.edu/api/v1/data_sets/1190/?recur=true.json'; // NEED A WAY TO GET THIS ID 1190 FROM PROJECT ID
            var responseDataset = $.ajax({ type: "GET",
                                url: urlDataset,
                                async: false,
                                dataType: "JSON"
                            }).responseText;




            var parsedResponseDataset = JSON.parse(responseDataset);


            alert(parsedResponseDataset)

            var datasetArray = [];

            for (var i=0;i<30;i++) {

                //alert(parsedResponseDataset.data[i][fieldID]);

                datasetArray.push(parsedResponseDataset.data[i][fieldID]);
            }


            return datasetArray;
        }
    }

}