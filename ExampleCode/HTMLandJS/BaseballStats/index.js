var field_data_total_bases = [];
var field_data_walks = [];
var calculated_runs = [];
var actual_runs = [];
var i;

function Get_Data_Set(){

	URL = 'http://rsense-dev.cs.uml.edu/api/v1/data_sets/1190?recur=true.json';
	response = $.ajax({ type: "GET",
					url: URL,
					async: false,
					dataType: "JSON"
					}).responseText;


	arg = JSON.parse(response);
	for(i=0;i<30;i++){
		field_data_total_bases.push(arg.data[i][647]) ;
	}

	alert(field_data_total_bases);

	URL = 'http://rsense-dev.cs.uml.edu/api/v1/data_sets/1190?recur=true.json';
	response = $.ajax({ type: "GET",
					url: URL,
					async: false,
					dataType: "JSON"
					}).responseText;


	arg = JSON.parse(response);
	for(i=0;i<30;i++){
		actual_runs.push(arg.data[i][638]) ;
	}

	alert(actual_runs);


	URL = 'http://rsense-dev.cs.uml.edu/api/v1/data_sets/1190?recur=true.json';
	response = $.ajax({ type: "GET",
					url: URL,
					async: false,
					dataType: "JSON"
					}).responseText;


	arg = JSON.parse(response);
	for(i=0;i<30;i++){
		field_data_walks.push(arg.data[i][644]) ;
	}

	alert(field_data_walks);
}

function Calculate_Runs(){

	for(i=0;i<30;i++){
		calculated_runs.push((Number(field_data_walks[i]) + Number(field_data_total_bases[i])) /4.0);
	}

	alert(calculated_runs);
}

function Post(){
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

    if(calculated_runs[0] == null){
        alert("There are no dice rolls. Please roll di before posting");
    }
    else{

        $.post(API_URL, upload);

        calculated_runs = [];

        alert("Runs have been Posted");
    }
}