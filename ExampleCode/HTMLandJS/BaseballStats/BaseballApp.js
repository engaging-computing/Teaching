var fieldDataTotalBases = [];
var fieldDataWalks = [];
var calculatedRuns = [];
var actualRuns = [];

function getDataSet() {

    if (fieldDataTotalBases[0] != null) { 
        alert("Please clear before pulling new datasets")
    } else {


        URL = 'http://rsense-dev.cs.uml.edu/api/v1/data_sets/1190?recur=true.json';
        response = $.ajax({ type: "GET",
                            url: URL,
                            async: false,
                            dataType: "JSON"
                        }).responseText;

        parsedResponse = JSON.parse(response);

        for (var i=0;i<30;i++) {
            fieldDataTotalBases.push(parsedResponse.data[i][647]) ;
            fieldDataWalks.push(parsedResponse.data[i][644]) ;
            actualRuns.push(parsedResponse.data[i][638]) ;
        }

        $("#totalBases").text("Total Bases: " + fieldDataTotalBases.join());
        $("#walks").text("Walks: " + fieldDataWalks.join());
        $("#actualRuns").text("Actual Runs: " + actualRuns.join());
    }
}

function calculateRuns() {

    if (calculatedRuns[0] != null) {
        alert("Please clear before recalculating")
    } else {

        if (fieldDataWalks[0] == null) {
            alert("Please pull datasets before calculating");
        } else {

            for (var i=0;i<30;i++) {
                calculatedRuns.push((Number(fieldDataWalks[i]) + Number(fieldDataTotalBases[i])) /4.0);
            }

            $("#calculatedRuns").text("Calculated Runs: " + calculatedRuns.join());
        }
    }
}

function post() {
    
    var currentTime = new Date();
    var timestamp = JSON.stringify(currentTime);
    var API_URL = 'http://rsense-dev.cs.uml.edu/api/v1/projects/106/jsonDataUpload';
    var upload = {
        'title': 'Test' + timestamp,
        'contribution_key': 'Key',
        'contributor_name': 'Tyler',
        'data':
        {
            '4279': calculatedRuns,
            '638': actualRuns
        }
    }

    if (calculatedRuns[0] == null) {
        alert("There are no calculated runs. Please press Calculate Runs before posting");
    } else {

        $.post(API_URL, upload);

        clearData();

        alert("Runs have been Posted");
    }
}

function clearData() {

    calculatedRuns = [];
    fieldDataTotalBases = [];
    fieldDataWalks = [];
    actualRuns = [];

    $("#totalBases").text("Total Bases: " + fieldDataTotalBases);
    $("#walks").text("Walks: " + fieldDataWalks);
    $("#actualRuns").text("Actual Runs: " + actualRuns);
    $("#calculatedRuns").text("Calculated Runs: " + calculatedRuns);
}
