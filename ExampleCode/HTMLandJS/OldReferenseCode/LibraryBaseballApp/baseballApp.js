var fieldDataTotalBases = [];
var fieldDataWalks = [];
var calculatedRuns = [];
var actualRuns = [];

function getDataSet() {

    if (fieldDataTotalBases[0] != null) { 

        alert("Please clear before pulling new datasets");
        return;
    }

    fieldDataWalks = isense.getDatasetFieldData(106,'MLB Team Statistics 2013','Walks');
    fieldDataTotalBases = isense.getDatasetFieldData(106,'MLB Team Statistics 2013','Total Bases');
    actualRuns = isense.getDatasetFieldData(106,'MLB Team Statistics 2013','Runs');

    $("#totalBases").text("Total Bases: " + fieldDataTotalBases.join());
    $("#walks").text("Walks: " + fieldDataWalks.join());
    $("#actualRuns").text("Actual Runs: " + actualRuns.join());   
}

function calculateRuns() {

    if (calculatedRuns[0] != null) {

        alert("Please clear before recalculating");
        return;
    }

    if (fieldDataWalks[0] == null) {

        alert("Please pull datasets before calculating");
        return;
    }

    for (var i=0; i<30; i++) {

        calculatedRuns.push((Number(fieldDataWalks[i]) + Number(fieldDataTotalBases[i])) /4.0);
    }

    $("#calculatedRuns").text("Calculated Runs: " + calculatedRuns.join());    
}

function post() {

    if (calculatedRuns[0] == null) {
        
        alert("There are no calculated runs. Please press Calculate Runs before posting");
        return;
    }

    isense.postDataset(106,'Key','Calculated Runs','Calculated Runs','Tyler',calculatedRuns)
    
    clearData();
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
