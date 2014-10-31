var field_data_total_bases = [];
var field_data_walks = [];
var calculated_runs = [];
var actual_runs = [];

function getDataSet() {

    if (field_data_total_bases[0] != null) { 
        alert("Please clear before pulling new datasets")
    } else {
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
        $("#total_bases").text("Total Bases: " + field_data_total_bases.join());

        URL = 'http://rsense-dev.cs.uml.edu/api/v1/data_sets/1190?recur=true.json';
        response = $.ajax({ type: "GET",
                            url: URL,
                            async: false,
                            dataType: "JSON"
                        }).responseText;


        arg = JSON.parse(response);
        for (i=0;i<30;i++) {
            field_data_walks.push(arg.data[i][644]) ;
        }

        $("#walks").text("Walks: " + field_data_walks.join());

        URL = 'http://rsense-dev.cs.uml.edu/api/v1/data_sets/1190?recur=true.json';
        response = $.ajax({ type: "GET",
                            url: URL,
                            async: false,
                            dataType: "JSON"
                        }).responseText;


        arg = JSON.parse(response);
        for (i=0;i<30;i++) {
            actual_runs.push(arg.data[i][638]) ;
        }

        $("#actual_runs").text("Actual Runs: " + actual_runs.join());
    }
}

function calculateRuns() {

    if (calculated_runs[0] != null) {
        alert("Please clear before recalculating")
    } else {

        if (field_data_walks[0] == null) {

            alert("Please pull datasets before calculating");
        } else {

            for (var i=0;i<30;i++) {
                calculated_runs.push((Number(field_data_walks[i]) + Number(field_data_total_bases[i])) /4.0);
            }

            $("#calculated_runs").text("Calculated Runs: " + calculated_runs.join());
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
            '4279': calculated_runs,
            '638': actual_runs
        }
    }

    if (calculated_runs[0] == null) {
        alert("There are no calculated runs. Please press Calculate Runs before posting");
    } else {

        $.post(API_URL, upload);

        calculated_runs = [];
        field_data_total_bases = [];
        field_data_walks = [];
        actual_runs = [];

        $("#total_bases").text("Total Bases: " + field_data_total_bases.join());
        $("#walks").text("Walks: " + field_data_walks.join());
        $("#actual_runs").text("Actual Runs: " + actual_runs.join());
        $("#calculated_runs").text("Calculated Runs: " + calculated_runs.join());

        alert("Runs have been Posted");
    }
}

function clearData() {

    calculated_runs = [];
    field_data_total_bases = [];
    field_data_walks = [];
    actual_runs = [];

    $("#total_bases").text("Total Bases: " + field_data_total_bases.join());
    $("#walks").text("Walks: " + field_data_walks.join());
    $("#actual_runs").text("Actual Runs: " + actual_runs.join());
    $("#calculated_runs").text("Calculated Runs: " + calculated_runs.join());

}

