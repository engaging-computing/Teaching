#include <iostream>
#include <string>                  // std::string, std::to_string;
#include <curl/curl.h>           // cURL to make HTTP requests
#include "../../../../json/json.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::stringstream;        // for concating an int onto a string.

/*
    At some point this will hold all the upload related stuff for iSENSE uploading in C++
    Probably functions like:

    - Upload with Contributor key
    - Upload with username / password - don't worry about ATM
    - GET JSON of a project given project ID
    - GET Project Fields given project ID
    - POST JSON dataset.
    - POST JSON appending to a dataset
*/


class iSENSE_Upload
{
    public:
        iSENSE_Upload();                             // Default constructor

        // This function should be called by the user, and should set up all the fields and what not.
        void set_project_ID(int proj_ID);

        // The user should also set the project title
        void set_project_title(string proj_title);

        // This one is optional, by default the label will be "cURL".
        void _set_project_label(string label);

        // As well as the contributor key they will be using
        void set_contributor_key(strng contr_key);

        void GET_PROJ_INFO();                    // this will grab info from the project page and display it, ie "api/v1/projects/PROJECT_ID"
        void GET_PROJ_FIELDS();                 // Given a URL has been set, the fields will be pulled and put into the fields vector.
        void Format_Upload_String();          // This formats the upload string
        int POST_JSON_KEY();                      // Post using contributor key (will not worry about Username/Password)

        void set_URL(string s_URL);             // Set the URL for this object

        devURL = "http://rsense-dev.cs.uml.edu/api/v1";

    private:
        vector<vector<string>> fields;      // this will contain all the field IDs
        vector<vector<string>> data;       // this will contain all the data, in the form of a strings
                                                                // each entry should be separate by a comma (",")

        string URL;                                    // URL to upload the JSON to
        string upload;                                // the upload string, in JSON
        string contributor_label;                // Label for the contributor key. by default this is "cURL"
        string contributor_key;                  // contributor key for the project
        string title;                                     // title for the dataset
        int project_ID;                                // project ID of the project
};


iSENSE_Upload::iSENSE_Upload()
{
    // Set these to default values for future references
    URL = "URL";
    upload = "upload";
    contributor_key = "KEY";
    title = "TITLE";
    project_ID = 0;
}


int POST_JSON_KEY()
{
    // Set up the POST URL
    post_URL = devURL + "/projects/" + project_ID + "/jsonDataUpload";

    // Format the DATA to be uploaded. Call another function to format this.


    // CURL object and response code.
    CURL *curl;
    CURLcode res;

    // In windows, this will init the winsock stuff
    res = curl_global_init(CURL_GLOBAL_DEFAULT);

    // Set the headers to JSON
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");

    // get a curl handle
    curl = curl_easy_init();
    if(curl)
    {
        // Set the URL that we will be using for our POST.
        curl_easy_setopt(curl, CURLOPT_URL, post_URL.c_str());

        // POST data. Upload will be the string with all the data.
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, upload.c_str());

        // JSON Headers
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Verbose debug output - turn this on if you are having problems. It will spit out a ton of information.
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        cout << "rSENSE says: \n";

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // For cURL return codes, see the following page:
        // http://curl.haxx.se/libcurl/c/libcurl-errors.html
        cout << "\n\ncURL return code was: " << res << endl;

        // Check for errors
        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);                // always cleanup
    }

    curl_global_cleanup();
}