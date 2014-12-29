diceRollArray = [];

function rollDie() {

    diceRollArray.push(Math.floor(Math.random() * 6) + 1);
    $("#Printout").text("Dice Rolls: " + diceRollArray.join());
}

function postDieArray() {

    isense.postDataset(927,'Key','Dice Roll','TESTTESTTEST','Tyler',diceRollArray);

    diceRollArray = [];
    $("#Printout").text("Dice Rolls: " + diceRollArray.join()); 
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
