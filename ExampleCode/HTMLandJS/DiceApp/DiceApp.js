var diceRollArray = [];
 
function rollDie() {

    diceRollArray.push(Math.floor(Math.random() * 6) + 1);
    $("#Printout").text("Dice Rolls: " + diceRollArray.join());
}

function postDieArray() {

    var currentTime = new Date();
    var timestamp = JSON.stringify(currentTime);
    var apiUrl = 'http://rsense-dev.cs.uml.edu/api/v1/projects/927/jsonDataUpload';
    var upload = {
        'title': 'Test' + timestamp,
        'contribution_key': 'Key',
        'contributor_name': 'Tyler',
        'data':
        {
            '4251': diceRollArray
        }
    }

    if (diceRollArray[0] == null) {
        alert("There are no dice rolls. Please roll di before posting");
    } else {

        $.post(apiUrl, upload);

        diceRollArray = [];
        $("#Printout").text("Dice Rolls: " + diceRollArray);
        alert("Rolls have been Posted");
    }
}

function post1000DieRolls() {
    
    diceRollArray = [];

    for (var i = 0; i<1000; i++) {
        rollDie();
    }

    postDieArray();
}

function clearDiceRolls() {

    diceRollArray = [];
    $("#Printout").text("Dice Rolls: " + diceRollArray);
}
