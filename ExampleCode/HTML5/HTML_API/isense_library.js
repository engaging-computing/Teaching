/*
    Collection of JavaScript functions for connecting with the iSENSE website.

    These are all taken from the HTML5 directory on GitHub, comments shortened
    and/or removed and made for easily copy/pasting this code into your own
    HTML5 project.

    As a result, if anything is confusing or not explained well, please look on
    GitHub for a more information. See the below link:

     Source code: https://github.com/isenseDev/HTML-Apps
    Example Apps: http://jasond94.github.io/HTML-Apps/index.html
*/
function POST_jsonDataUpload_Email()
{
    var API_URL;        // EX: 'http://isenseproject.org/api/v1/projects/556/jsonDataUpload';
    var USER_URL;       // EX: 'http://isenseproject.org/projects/556';
    var USER_URL_TEXT;  // EX: 'Click here to go to your project!';

    var currentTime = new Date();
    var timestamp = JSON.stringify(currentTime);

    var email;  // EX: a@a.a
    var password;   // EX: a
    var title;  // EX: Table A's Awesome Lab Data

    var upload = {
        'email': email,
        'password': password,
        'title': title,
        'data':
        {
            //  Fill in the fields for your project here.
            //  use the following URL to find this:
            //  http://isenseproject.org/api/v1/projects/PROJECT_ID/
        }
    }

    // POST the data to iSENSE
    if(confirm("Do you want to upload this data to iSENSE?")) {
        $.post(API_URL, upload);

        // Add a link in the HTML file to the project they contributed to.
        The_URL.innerHTML = '<p><a href="'+ USER_URL +'">' + USER_URL_TEXT + '</a></p>';
    }
    else {
        // Change the HTML to show that the user canceled the upload request.
        The_URL.innerHTML = "<br/>Canceled!<br/><br/>";
    }
}

function POST_jsonDataUpload_ContributorKey()
{
    var API_URL;                  // EX: 'http://isenseproject.org/api/v1/projects/555/jsonDataUpload';
    var USER_URL;               // EX: 'http://isenseproject.org/projects/555';
    var USER_URL_TEXT;     // EX: 'Click here to go to your project!';

    var currentTime = new Date();
    var timestamp = JSON.stringify(currentTime);

    var   key;          // EX: '12345';
    var  name;          // EX: 'WebApp';
    var title;          // EX: 'My awesome WebApp!'

    /*
        You probably want to use some JavaScript functions here, such as
        document.getElementById("PUT ID HERE").value;
        This way you can get user input and then submit that data to iSENSE.
    */

    var upload = {
        'title': title,
        'contribution_key': key,
        'contributor_name': name,
        'data':
        {
            //  Fill in the fields for your project here.
            //  Use the following URL to find this:
            //  http://isenseproject.org/api/v1/projects/PROJECT_ID/
        }
    }

    // POST the data to iSENSE
    if(confirm("Do you want to upload this data to iSENSE?")) {
        var result = $.post(API_URL, upload);

        /*  This is quick check to see if the above POST command worked. */
        if(result.done) {
            rev.innerHTML = "<p>Successfully posted to iSENSE!</p>";
        }
        else if(result.fail) {
            rev.innerHTML = "<p>Failed to post to iSENSE!</p>";
        }

        // Add a link in the HTML file to the project they contributed to.
        The_URL.innerHTML = '<p><a href="'+ USER_URL +'">' + USER_URL_TEXT + '</a></p>';
    }
    else {
        // Change the HTML to show that the user canceled the upload request.
        The_URL.innerHTML = "<p>Canceled!</p>";
    }
}

function GET_Projects_ByProjectID()
{
    var ID = document.getElementById("dataset_name").value;
    var URL = "http://isenseproject.org/api/v1/projects/"+ID;
    var USER_URL_TEXT = "Click here to view project #" + ID + "!";

    /*  type:   Must be either "POST" or "GET" for iSENSE - in this case it MUST be
                a "GET" request because we aren't posting anything to iSENSE.
        url: use the URL variable at the top. You could also hardcode this in.
        async: false, because we want to make a cross domain request.
        dataType: "JSON" because we are requesting the data in JSON format.     */
    var response = $.ajax({ type: "GET",
                url: URL,
                async: false,
                dataType: "JSON"
            }).responseText;

    /*  If the response text ends up being undefined, we weren't able to find
        anything about the project.         */
    if(response === undefined)
    {
        rev.innerHTML = "That project ID could not be found!";
    }
    else{

        /*  Now we should have some information about the project. This should
            let us parse the request and then store the information about the
            project.            */
        var arg = JSON.parse(response);
        var array = [];
        array[0] = arg['name'];
        array[1] = arg['createdAt'];
        array[2] = arg['ownerName'];
        array[3] = arg['url'];

        /*  Here I display some of the information about the project.

            Note:   Use the output of the console.log(response) command to find
                    out more information about a given project. There are other
                    properties you can display to the user.     */
        rev.innerHTML = "Information about this project: <br/>Name: "+ array[0]
        + "<br/>Created at: "+ array[1] + "<br/> Owner: "+ array[2]
        + '<br/>URL: <a href="' + array[3] + '">' + USER_URL_TEXT + '</a>';

    }
}

function GET_Fields_ByFieldID()
{
    var ID = document.getElementById("dataset_name").value;
    var URL = "http://isenseproject.org/api/v1/fields/"+ID;

    /*  type:   Must be either "POST" or "GET" for iSENSE - in this case it MUST be
                a "GET" request because we aren't posting anything to iSENSE.
        url: use the URL variable at the top. You could also hardcode this in.
        async: false, because we want to make a cross domain request.
        dataType: "JSON" because we are requesting the data in JSON format.     */
    var response = $.ajax(
    {   type: "GET",
        url: URL,
        async: false,
        dataType: "JSON"
    }).responseText;            // Getting response text from this ajax request.

    //console.log(response);    // Debugging

    /*  If the response text ends up being undefined, we weren't able to find
        anything about the field. IE it doesn't exist.          */
    if(response === undefined)
    {
        rev.innerHTML = "That field ID could not be found!";
    }
    else{

        /*  Now we should have some information about the field. This should let
            us parse the request and then store the information about the field. */
        var arg = JSON.parse(response);
        var array = [];
        array[0] = arg['name'];
        array[1] = arg['type'];
        array[2] = arg['unit'];
        array[3] = arg['restrictions'];

        /*  Here I display some of the information about the field.
            Note: there really isn't anymore information about fields other
            than what I have listed below. You can however use these fields to
            upload data to iSENSE.      */
        rev.innerHTML = "Information about this field: "    +
                    "<br/>Name: "           + array[0]  +
                    "<br/>Type: "           + array[1]  +
                    "<br/>Unit: "           + array[2]  +
                    "<br/>Restrictions: "       + array[3];

        //console.log(arg); // Debugging
    }
}
