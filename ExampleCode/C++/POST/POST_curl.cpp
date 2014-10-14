#include <iostream>
#include <curl/curl.h>      // cURL to make HTTP requests
#include <stdio.h>
#include <string.h>
#include <cstring>

using namespace std;

    // Below is an example of using cURL on the command line to POST to iSENSE.
    //curl -X POST -H "Content-Type: application/json; charset=UTF-8" -d '{"title":"Curl Test","contribution_key":"key","contributor_name":"cURL","data":{"3550":[22]}}' http://rsense-dev.cs.uml.edu/api/v1/projects/821/jsonDataUpload

/*
    NOTES about using C++ with iSENSE.

    This example uses cURL, through libcurl.

    Its a bit of a pain, but I found a good example at this site:
    http://curl.haxx.se/libcurl/c/http-post.html

    Major issue in the beginnig - make sure to include headers specifying JSON as the content-type.

    Also, had

    Works under Linux, going to test Windows next.
    Also works using different titles and numbers, which is awesome.

*/

/*
    EXPANDED

    {
        "title":"Curl Test", 
        "contribution_key":"key", 
        "contributor_name":"cURL", 
        "data":
            {
                "3550":[99]
            }
    } 
*/

/*
    FROM THE PYTHON APP

{
    'title': title,                     
    'contribution_key': contributor,
    'contributor_name': "python",
    'data':
    {
        '3398': [data]
    }
}

*/

int main(void)
{
    char title[41];
    int x;

    cout<<"Please enter a title for the dataset: ";
    cin.getline(title, 41, '\n');

    //cout<<"You entered the title: "<<title<< "\n\n";

    cout<<"Please enter a number: ";
    cin>>x;

    //cout<<"You entered the number: "<<x;
    cout<<"\n\nUploading "<<x<<" to rSENSE.\n\n";


//  *** Below this point is the POST stuff. ***
    
    // URL for the project. Change "821" for a different project.
    char url[] = "http://rsense-dev.cs.uml.edu/api/v1/projects/821/jsonDataUpload";

    // DATA for the project. This will be the entire uploaded string.
    char upload[150] = "\0";    // Make sure to initialize this to NULL.
    
    // Part of the stuff needed to upload. "3550" is the field ID for a number on rSENSE, so make sure to change that if you change the project ID in the URL.
    char data[] = "\",\"contribution_key\":\"key\",\"contributor_name\":\"cURL\",\"data\":{\"3550\":[";

    // Holds the value of the int entered above.
    char value[21];

    // This part combines everything entered above into one string that can be uploaded to rSENSE.
    strcat(upload, "{\"title\":\"");
    strcat(upload, title);
    strcat(upload, data);

    sprintf(value, "%d", x);    // Add the variable entered to the upload data.
    strcat(upload, value);      // ^^^ 

    strcat(upload, "]}}");

    // Debugging: 
    //cout<<"The string is: "<<upload<<endl;

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
        curl_easy_setopt(curl, CURLOPT_URL, url);
     
        // POST data. Upload will be the char array with all the data.
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, upload);

        // JSON Headers
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
     
        // Verbose debug output
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        /* Check for errors */ 
        if(res != CURLE_OK)
          fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));

        /* always cleanup */ 
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    cout<<"\n\n";   // extra new lines in the terminal.

    return 0;
}