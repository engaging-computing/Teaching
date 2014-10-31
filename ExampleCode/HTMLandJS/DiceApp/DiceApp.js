var dice_roll_array = [];
 
function rollDi(){

    dice_roll_array.push(Math.floor(Math.random() * 6) + 1);
    $("#Printout").text("Dice Rolls: " + dice_roll_array.join());
}

function postDiArray(){

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

    if(dice_roll_array[0] == null){
        alert("There are no dice rolls. Please roll di before posting");
    }else {

        $.post(API_URL, upload);

        dice_roll_array = [];
        $("#Printout").text("Dice Rolls: " + dice_roll_array.join());
        alert("Rolls have been Posted");
    }
}

function post1000DiRolls(){
    
    alert("hi");
    var currentTime = new Date();
    var timestamp = JSON.stringify(currentTime);


    dice_roll_array = [];

    for(var i = 0; i<1000; i++){
        rollDi();
    }

    postDiArray();
}

function clearDiceRolls(){

    dice_roll_array = [];
    $("#Printout").text("Dice Rolls: " + dice_roll_array.join());
}
