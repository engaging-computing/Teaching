#include <iostream>             // std::cout, std::cin
#include <string>                  // std::string, std::to_string;
#include <curl/curl.h>           // cURL to make HTTP requests
#include <time.h>                 // for time stamps
#include "isenseupload.h"      // using isenseupload.h
#include "../../../../picojson.h"    // May need to change the path for this if not in git repo


using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::stringstream;        // for concating an int onto a string.


// Main, calls upload function. Uses ***something*** for JSON serialization / parsing.
int main ()
{
    // Testing picojson to see how it works.

    string json;

    // Example of using the class iSENSE_Upload
    iSENSE_Upload test;

    // Add project info / dataset info to the object
    test.set_project_ID(555);
    test.set_project_title("TEST");
    test.set_project_label("label goes here");
    test.set_contributor_key("key goes here");

    // At some point make it possible to add data / fields

    // DEBUG testing
    test.DEBUG();


    // string title;           // Four variables for user input
    // string letters;
    // time_t timestamp;
    // int num = 0;

    // /*
    //     URL for the project. Change "929" for a different project.
    //     NOTE: if you change the URL you will need to change the field IDs
    //     (should probably try to auto detect them if possible.)
    // */
    // string url = "http://rsense-dev.cs.uml.edu/api/v1/projects/929/jsonDataUpload";

    // // Get user input.
    // cout << "Please enter a title for the dataset: ";       // Gets the title
    // getline(cin, title);

    // cout << "Please enter a bunch of letters: ";            // Gets a bunch of letters
    // getline(cin, letters);

    // cout << "Please enter a number: ";                      // Gets a number to upload to iSENSE
    // cin >> num;

    // // Get timestamp (unix)
    // timestamp = time(NULL);

    // // Let the user know we're uploading. (Maybe add an option to confirm here in the future.)
    // cout << "\nUploading " << " to rSENSE.\n\n";
    // cout << "The title you entered: " << title << endl;
    // cout << "Letters you entered: " << letters << endl;
    // cout << "Number you entered: " << num << endl;
    // cout << "Timestamp: " << timestamp << endl;



    // In the future we should tell the user if this upload function was a success. Or if it failed - if it failed then why.
    return 0;
}