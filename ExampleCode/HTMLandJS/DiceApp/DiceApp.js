var dice_roll_array = [];
 
function Roll_Di(){

	dice_roll_array.push(Math.floor(Math.random() * 6) + 1);

}

function Show_Di_Array(){

	alert(dice_roll_array);
}

function Post_Di_Array(){
	var currentTime = new Date();
	var timestamp = JSON.stringify(currentTime);
    var API_URL = 'http://rsense-dev.cs.uml.edu/api/v1/projects/927/jsonDataUpload';
    var upload = {
        'title': 'Test' + timestamp,
        'contribution_key': 'Key',
        'contributor_name': 'Tyler',
        'data':
        {
        	'4251': dice_roll_array
        }
    }
    $.post(API_URL, upload);

    alert("Rolls have been Posted");
    dice_roll_array = [];
}

function Post_1000_Di_Rolls(){
	var currentTime = new Date();
	var timestamp = JSON.stringify(currentTime);
	var i;
	dice_roll_array = [];
    for(i = 0; i<1000; i++){
    	Roll_Di();
    }

    var API_URL = 'http://rsense-dev.cs.uml.edu/api/v1/projects/927/jsonDataUpload';
    var upload = {
        'title': 'TEST'+timestamp,
        'contribution_key': 'Key',
        'contributor_name': 'Tyler',
        'data':
        {
        	'4251': dice_roll_array
        }
    }
    $.post(API_URL, upload);
    alert("Rolls have been Posted");
    dice_roll_array = [];

}
function Clear_Dice_Rolls(){

	dice_roll_array = [];
}