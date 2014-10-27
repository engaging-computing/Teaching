#include <iostream>       // cout/cin
#include <stdio.h>           // Printf/scanf
#include <curl/curl.h>     // cURL to make HTTP requests
#include <string.h>         // strings
#include <cstring>          // strings
#include <stdlib.h>         // srand, rand
#include <time.h>           // time

using namespace std;

/*
    This will be a DiceApp written in C++.

    All it will do is create two random numbers (probably using srand?) and
    then upload those two numbers to rSENSE.

    What also might be cool is to get this to run a loop, and save say 100 red dice and 100 white dice.
    Then upload those two arrays to rSENSE.
*/

void upload_to_rsense(char title[], int red_die, int white_die)
{
    // URL for the project. Change "821" for a different project.
    char url[] = "http://rsense-dev.cs.uml.edu/api/v1/projects/911/jsonDataUpload";

    // DATA for the project. This will be the entire uploaded string.
    char upload[150] = "\0";                // Make sure to initialize this to NULL.

    // Part of the stuff needed to upload. "3550" is the field ID for a number on rSENSE, so make sure to change that if you change the project ID in the URL.
    char data[] = "\",\"contribution_key\":\"123\",\"contributor_name\":\"cURL\",\"data\":{\"4160\":[";

    // Holds the value of the int entered above.
    char value[21];

    // This part combines everything entered above into one string that can be uploaded to rSENSE.
    strcat(upload, "{\"title\":\"");
    strcat(upload, title);                        // Add the title.
    strcat(upload, data);                       // Add the contributor stuff and the field ID.

    sprintf(value, "%d", red_die);          // Convert the first die into a string
    strcat(upload, value);                      // Add the variable entered to the upload data.

    strcat(upload, "], \"4161\":[");          // Add the second field ID

    sprintf(value, "%d", white_die);        // Convert the second die into a string
    strcat(upload, value);

    strcat(upload, "]}}");                      // Add the last few brackets.

    // Debugging. Uncomment if you have issues uploading to rSENSE.
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

        // Verbose debug output -  uncomment this on if you are having problems. It will spit out a ton of information.
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

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


int main()
{
    char title[41];
    int red_die = 0, white_die = 0;

    // Get user input.
    cout<<"Please enter a title for the dataset: ";
    cin.getline(title, 41, '\n');

    // Dice roll simulation.
    cout<<"Generating two die rolls. Numbers 1 through 6. \n";

    srand(time(NULL));                      // Seed the random function

       red_die = rand()%6 + 1;          // Generate random numbers between 1 and 6.
    white_die = rand()%6 + 1;

    // Let the user know we're uploading. (Maybe add an option to confirm here in the future.)
    cout<<"\nUploading red_die "<<red_die<<" and white_die "<<white_die<<" to rSENSE.\n\n";

    // Right here I call a function to upload to rSENSE-dev.
    // I just pass it the title of the dataset and the number that the user entered.
    upload_to_rsense(title, red_die, white_die);

    return 0;
}