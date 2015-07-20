When the window is clicked on, a random name will appear along with the corresponding gender and popularity rank. If the name is female, then the background color will change to pink, if the name is male, then the background color will change to blue.
Also, an added feature was added to the API.js library so that if a contributor key is not needed for an iSENSE project, then one can still get data from it.

noKey : function(projectID, contributorName){

        this.projectID = projectID;
        this.contributorName = contributorName;
    },
