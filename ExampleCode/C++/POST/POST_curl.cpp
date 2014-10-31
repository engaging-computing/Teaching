#include <iostream>         // std::cout, std::cin
#include <string>               // std::string, std::to_string;
#include <curl/curl.h>      // cURL to make HTTP requests
#include <time.h>           // Timestamps

// Check if these are needed.
#include <stdio.h>
#include <string.h>
#include <cstring>

using std::cout;
using std::cin;
using std::string;
using std::to_string;
using std::endl;

/*
    Below is an example of using cURL on the command line to POST to iSENSE.
    curl -X POST -H "Content-Type: application/json; charset=UTF-8" \
    -d '{"title":"Curl Test","contribution_key":"key","contributor_name":"cURL","data":{"3550":[22]}}' \
    http://rsense-dev.cs.uml.edu/api/v1/projects/821/jsonDataUpload
*/

/*
    NOTES about using C++ with iSENSE.

    This example uses cURL, through libcurl.

    Its a bit of a pain, but I found a good example at this site:
    http://curl.haxx.se/libcurl/c/http-post.html

    Major issue in the beginnig - make sure to include headers specifying JSON as the content-type.

    Works under Linux, going to test Windows next.
*/


// Basic upload a char test.
void upload_to_rsense(string title, int num, string letters, time_t timestamp)
{
    string upload;     // DATA for the project. This will be the entire uploaded string.

    // URL for the project. Change "929" for a different project.
    string url = "http://rsense-dev.cs.uml.edu/api/v1/projects/929/jsonDataUpload";

    // Part of the stuff needed to upload. "3550" is the field ID for a number on rSENSE, so make sure to change that if you change the project ID in the URL.
    string data = "\",\"contribution_key\":\"123\",\"contributor_name\":\"cURL\",\"data\":{\"4274\":[";

    // This part combines everything entered above into one string that can be uploaded to rSENSE.
    upload = string("{\"title\":\"") + title + data;                   // JSON/Title/Data string

    // Add the number and the bracket/comma to the upload string.
    sprintf(upload.c_str(), "%d", num);

    upload = string("],");

    // Add the letters that were entered (+ the field ID / JSON stuff)
    upload = string("\"4275\":[\"") + letters + string("\"],");

    // Add the timestamp field ID, timestamp, and JSON stuff.
    upload = string( "\"4276\":[\"");
    sprintf(upload, "%d", timestamp);
    upload =  string( "\"]}}");

    // Debugging:
    cout << "The string is: " << upload << endl;

    // TESTING
/*
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
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // POST data. Upload will be the char array with all the data.
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, upload);

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
*/
}


int main ()
{
    string title;
    string letters;
    time_t timestamp;
    int num = 0;

    // Get user input.
    cout << "Please enter a title for the dataset: ";
    cin >> title;

    cout << "Please enter a number: ";
    cin >> num;

    cout << "Please enter a bunch of letters: ";
    cin >> letters;

    // Get timestamp (unix)
    timestamp = time(NULL);

    // Let the user know we're uploading. (Maybe add an option to confirm here in the future.)
    cout << "\nUploading " << " to rSENSE.\n\n";
    cout << title << endl;
    cout << letters << endl;
    cout << num << endl;
    cout << timestamp << endl;

    // Right here I call a function to upload to rSENSE-dev.
    // I just pass it the title of the dataset and the number that the user entered.
    upload_to_rsense(title, num, letters, timestamp);

    // In the future we should tell the user if this upload function was a success. Or if it failed - if it failed then why.

    return 0;
}