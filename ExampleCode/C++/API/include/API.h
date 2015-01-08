#ifndef API_h
#define API_h

// Windows likes the curl header this way.
#ifdef WIN32
#include <curl.h>                 // cURL to make HTTP requests

// Linux / other systems. (Test MacOS and see if it likes it this way or the Windows way)
#else
#include <curl/curl.h>            // cURL to make HTTP requests
#endif

#include <ctime>                  // Timestamps
#include <iostream>
#include <map>
#include <string>                 // std::string, std::to_string;
#include <vector>
#include "picojson.h"             // picojson for using JSON easily.
#include "memfile.h"              // picojson/curl uses this for temp files.
                                  // Note: declared in memfile.h, but defined in api.cpp
/*
    To do list:
    1. Make a dice roll app
    2. Try other GET/POST API functions, such as amending/editing datasets.
    3. Try media objects.
    4. Create a zip file for people to download for Linux / Mac / Windows.

    Currently working in Linux & Windows 8.1 (x64)
    Test in x86 if possible (VM?) and Windows 7. Also Mac OS.
*/

// To avoid poluting the namespace, and also to avoid typing std:: everywhere.
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::to_string;
using std::vector;

// For picojson
using namespace picojson;

// Constants for the rest of the class
const string dev_baseURL = "http://rsense-dev.cs.uml.edu";
const string live_baseURL = "http://isenseproject.org";
const string devURL = "http://rsense-dev.cs.uml.edu/api/v1";
const string liveURL = "http://isenseproject.org/api/v1";

class iSENSE
{
  public:
    iSENSE();                                          // Default constructor
    iSENSE(string proj_ID, string proj_title,          // Contructor with parameters
           string label, string contr_key);

    // Similar to the constructor with parameters, but called after the object is created.
    // This way you can change/update the title/project ID/etc.
    void set_project_all(string proj_ID, string proj_title,
                         string label, string contr_key);

    void set_project_ID(string proj_ID);                // This function should set up all the fields
    void set_project_title(string proj_title);          // The user should also set the project title
    void set_project_label(string proj_label);          // This one is optional, by default the label will be "cURL"
    void set_contributor_key(string proj_key);          // User needs to set the contributor key they will be using
    void set_email(string proj_email);                  // Sets the email address to be used to upload data
    void set_password(string proj_password);            // Sets the password to be used

    /*  This function will push data back to the map.
        User must give the pushback function the following:
        1. Field name (as seen on iSENSE)
        2. Some data (in string format). For numbers, use to_string.         */
    void push_back(string field_name, string data);

    // I also created a timestamp function to make it easier for users to use timestamps in their project.
    string generate_timestamp(void);

    // This formats the upload string
    void format_upload_string(bool key);

    // This formats one FIELD ID : DATA pair
    void format_data(vector<string> *vect, array::iterator it, string field_ID);

    /*  iSENSE API functions
        Note: methods which return bool return true for success and false for failure.
        They also output the reasons for failure to the screen.   */
    bool get_check_user();                          // Checks to see if a username / password is valid
    bool get_project_fields();                      // Pulls the fields and puts them into the fields object & array
    vector<string> get_projects_search(string search_term);    // Search for projects with the search term
    bool post_json_email();                         // Post using a email / password
    bool post_json_key();                           // Post using contributor key

    /*  Future functions to be implemented at a later date.
    void post_append_key();                         // Amend a dataset with a contributor key
    void post_append_email();                       // Amend a dataset with a email / password
    void post_edit_key();                           // Edit a dataset with a dataset ID & contributor key
    void post_edit_user();                          // Edit a dataset with a dataset ID & email / password
    void post_fields_email();                       // Post fields  by email / password
    void post_projects_email();                     // Post a project by email / password

    void get_projects_by_id(string project_ID);     // Get information about a project by project ID
    void get_fields_by_id();                        // Get information about a field by field ID
    void get_search_projects(string search_term);   // Search for projects by search term

    // Possibly try posting media objects by email/password or contributor key.
    void post_media_objects_email();
    void post_media_objects_key();
    */

    // For debugging, dumps all the data.
    void debug();

  private:
    /*  These two 'objects' are picojson objects that will be used to upload to iSENSE. The upload_data object
    contains the entire upload string, in JSON format. Picojson will let us output this to a string and then pass
    that string to libcurl. The fields data object is the object that the 'data' part contains in the upload_data
    object. Basically it is a bunch of key:values, with the key being the field ID and the value being an array
    of data, whether it be numbers/text/etc.    */
    object upload_data, fields_data;

    /*  These three objects are the data that is pulled off iSENSE for the given project. The get_data object
    contains all the data we can pull off of iSENSE (like what you find on /api/v1/projects/DATASET_ID_HERE).
    The fields object then contains just the field information, and the fields_array has that same data in an array form
    for iterating through it.  */
    value get_data, fields;
    array fields_array;

    /* Data to be uploaded to iSENSE.
    The string is the field name, the vector of strings contains all the data for that field name. */
    map<string, vector<string>> map_data;

    // Data needed for processing the upload request
    //bool usingDev;                  // Whether the user wants iSENSE or rSENSE
                                      // (currently not implemented, future idea)
    string upload_URL;                // URL to upload the JSON to
    string get_URL;                   // URL to grab JSON from
    string get_UserURL;               // URL to test credentials
    string title;                     // title for the dataset
    string project_ID;                // project ID of the project
    string contributor_label;         // Label for the contributor key. by default this is "cURL"
    string contributor_key;           // contributor key for the project
    string email;                     // Email to be used to upload the data
    string password;                  // Password to be used with the above email address
};

#endif
