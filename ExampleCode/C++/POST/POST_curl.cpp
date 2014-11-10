#include <iostream>           // std::cout, std::cin
#include <string>                // std::string, std::to_string;
#include <curl/curl.h>         // cURL to make HTTP requests
#include <time.h>               // Timestamps
#include <sstream>            // stringstreams, converting ints to numbers

// Check if these are needed. Might be needed for cURL
#include <stdio.h>
#include <string.h>
#include <cstring>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::stringstream;    // for concating an int onto a string.


// Basic upload a test. Uploads a number, a string and a timestamp
void upload_to_rsense(string title, int num, string letters, time_t timestamp)
{
    string upload;     // DATA for the project. This will be the entire uploaded string.

    //  URL for the project. Change "929" for a different project.
    string url = "http://rsense-dev.cs.uml.edu/api/v1/projects/929/jsonDataUpload";

    /*
        Part of the stuff needed to upload. "3550" is the field ID for a number on rSENSE, so make
        sure to change that if you change the project ID in the URL.
        You may also need to change the following to your own project:
        contribution_key = the key to your iSENSE project
        contributor_name = you can leave this or change it to something relevant to your project
        for the data part, the field ID comes first and should be changed for your project's fields
    */
    string data = "\",\"contribution_key\":\"123\",\"contributor_name\":\"cURL\",\"data\":{\"4274\":[";

    // This part combines everything entered above into one string that can be uploaded to rSENSE.
    upload += string("{\"title\":\"") + title + data;                   // JSON/Title/Data string

    // Add the number and the bracket/comma to the upload string.
    stringstream num_to_string;                                // First part converts a number (int in this case) to a string
    num_to_string << num;
    upload += num_to_string.str() + string("],");      // This part adds both the number and the closing bracket to upload string

    // Add the letters that were entered (+ the field ID / JSON stuff)
    upload += string("\"4275\":[\"") + letters + string("\"],");

    // Add the timestamp field ID, timestamp, and JSON stuff.
    num_to_string.clear();                         // Clear the stringstream object, and add the timestamp to the upload string
    num_to_string << timestamp;
    upload += string( "\"4276\":[\"") + num_to_string.str() + string( "\"]}}");

    // Debugging:
    cout << "The string is: " << upload << endl;

    // TESTING - hopefully this part works!

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
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // POST data. Upload will be the char array with all the data.
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


int main ()
{
    string title;
    string letters;
    time_t timestamp;
    int num = 0;

    // Get user input.
    cout << "Please enter a title for the dataset: ";       // Gets the title
    getline(cin, title);

    cout << "Please enter a bunch of letters: ";            // Gets a bunch of letters
    getline(cin, letters);

    cout << "Please enter a number: ";                        // Gets a number to upload to iSENSE
    cin >> num;

    // Get timestamp (unix)
    timestamp = time(NULL);

    // Let the user know we're uploading. (Maybe add an option to confirm here in the future.)
    cout << "\nUploading " << " to rSENSE.\n\n";
    cout << "The title you entered: " << title << endl;
    cout << "Letters you entered: " << letters << endl;
    cout << "Number you entered: " << num << endl;
    cout << "Timestamp: " << timestamp << endl;

    // Right here I call a function to upload to rSENSE-dev.
    // I just pass it the title of the dataset and the number that the user entered.
    upload_to_rsense(title, num, letters, timestamp);

    // In the future we should tell the user if this upload function was a success. Or if it failed - if it failed then why.

    return 0;
}