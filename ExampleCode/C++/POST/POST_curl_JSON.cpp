#include <iostream>             // std::cout, std::cin
#include <string>               // std::string, std::to_string;
#include <curl/curl.h>          // cURL to make HTTP requests
#include <time.h>               // for time stamps

// Check if these are needed. Might be needed for cURL
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::stringstream;        // for concating an int onto a string.


// This function will use the a JSON library for parsing / serializing
string JSON_Stringify(string title, int num, string letters, time_t timestamp)
{
    string upload = "wow much json \n";
    return upload;
}

// This function will actually upload the JSON string to iSENSE using cURL
void upload_to_rsense(string url, string upload)
{
    CURL *curl;
    CURLcode res;

    /* In windows, this will init the winsock stuff */
    res = curl_global_init(CURL_GLOBAL_DEFAULT);

    // Set the headers to JSON
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");

    /* get a curl handle */
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

        cout<<"rSENSE says: \n";

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // For cURL return codes, see the following page:
        // http://curl.haxx.se/libcurl/c/libcurl-errors.html
        cout<<"\n\ncURL return code was: "<<res<<endl;

        /* Check for errors */
        if(res != CURLE_OK)
          fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}


// Main, calls upload function. Uses ***something*** for JSON serialization / parsing.
int main ()
{
    string title;           // Four variables for user input
    string letters;
    time_t timestamp;
    int num = 0;
    string upload;          // This will hold the final upload string, in JSON

    /*  
        URL for the project. Change "929" for a different project.
        NOTE: if you change the URL you will need to change the field IDs
        (should probably try to auto detect them if possible.)
    */
    string url = "http://rsense-dev.cs.uml.edu/api/v1/projects/929/jsonDataUpload";

    // Get user input.
    cout << "Please enter a title for the dataset: ";       // Gets the title
    getline(cin, title);

    cout << "Please enter a bunch of letters: ";            // Gets a bunch of letters
    getline(cin, letters);

    cout << "Please enter a number: ";                      // Gets a number to upload to iSENSE
    cin >> num;

    // Get timestamp (unix)
    timestamp = time(NULL);

    // Let the user know we're uploading. (Maybe add an option to confirm here in the future.)
    cout << "\nUploading " << " to rSENSE.\n\n";
    cout << "The title you entered: " << title << endl;
    cout << "Letters you entered: " << letters << endl;
    cout << "Number you entered: " << num << endl;
    cout << "Timestamp: " << timestamp << endl;

    // JSON_Stringify will turn the user input into workable JSON
    upload = JSON_Stringify(title, num, letters, timestamp);

    cout << upload;

    // Otherwise upload to iSENSE
    //upload_to_rsense(url, upload);

    return 0;
}