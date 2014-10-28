#include <iostream>             // Using C++, but also a C JSON library + libcURL, a C networking/HTTP library
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>          // cURL to make HTTP requests
#include <string.h>             // libcurl likes c strings, also parson can format JSON into c strings
#include <cstring>
#include <time.h>               // for time stamps

#include "parson.h"             // Used for creating/parsing JSON strings.

using namespace std;

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

    Major issue in the beginning - make sure to include headers specifying JSON as the content-type.

    Works under Linux, going to test Windows next.

    Also currently using parson for JSON parsing / serialization.
*/


// This function will use the parson JSON library for parsing / serializing
void upload_to_rsense_json_test(char title[], int num, char letters[], int timestamp)
{
    // Let's see if we can take a title, number and some letters, along with making a timestamp
    // and send this off to rSENSE using
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;

    //char test[20] = "test";
    int field_id = 5555;

    // The following is required.
    json_object_set_string(root_object, "title", title);
    json_object_set_string(root_object, "contribution_key", "123");
    json_object_set_string(root_object, "contributor_name", "cURL parson");

    // This part adds the variables given to the function.
    json_object_dotset_string(root_object, "data.field_id", letters);

    // Convert the JSON object to a string.
    serialized_string = json_serialize_to_string(root_value);
    puts(serialized_string);
    json_free_serialized_string(serialized_string);
    json_value_free(root_value);
}


// This function will use the parson JSON library for parsing / serializing
void upload_to_rsense_json_test(void)
{
    // Test to see if this library works.

    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;
    json_object_set_string(root_object, "name", "John Smith");
    json_object_set_number(root_object, "age", 25);
    json_object_dotset_string(root_object, "address.city", "Cupertino");
    json_object_dotset_value(root_object, "contact.emails", json_parse_string("[\"email@example.com\",\"email2@example.com\"]"));
    serialized_string = json_serialize_to_string(root_value);
    puts(serialized_string);
    json_free_serialized_string(serialized_string);
    json_value_free(root_value);
}



// Basic upload a string, number, timestamp test.
// Works, but very ugly.
void upload_to_rsense(char title[], int num, char letters[], int timestamp)
{
    // URL for the project. Change "821" for a different project.
    char url[] = "http://rsense-dev.cs.uml.edu/api/v1/projects/929/jsonDataUpload";

    // DATA for the project. This will be the entire uploaded string.
    char upload[500] = "\0";    // Make sure to initialize this to NULL.

    // Part of the stuff needed to upload. "3550" is the field ID for a number on rSENSE, so make sure to change that if you change the project ID in the URL.
    char data[] = "\",\"contribution_key\":\"123\",\"contributor_name\":\"cURL\",\"data\":{\"4274\":[";

    // Holds the value of the int entered above.
    char value[21];

    /*
            '2685': [5],
            '2640': [4],
            '2641': [4],
    */

/*
        {
            "title": "round 2",
            "contribution_key": "key",
            "contributor_name": "cURL",
            "data":
            {
                "4274": [21345],
                "4275":'jdjdhjdew',
                "4276": [1414509593]
            }
        }


        {
            "title": "will this work?",
            "contribution_key":"key",
            "contributor_name":"cURL",
            "data":
            {
                "4274": [12345],
                "4275": 'shjwhjjasw',
                '4276": "1414510108'
            }
        }
*/
    time_t current_time;
    current_time = time(NULL);
    printf(ctime(&current_time));

    // This part combines everything entered above into one string that can be uploaded to rSENSE.
    strcat(upload, "{\"title\":\"");
    strcat(upload, title);                // Add the title.
    strcat(upload, data);               // Add the contributor stuff and the field ID.

    // Add the numbers.
    sprintf(value, "%d", num);      // Convert the variable to a string
    strcat(upload, value);             // Add the variable entered to the upload data.
    strcat(upload, "],");             // Add the last few brackets.

    // Add the letters that were entered
    strcat(upload, "\"4275\":[\"");   // Add the next field ID to the upload string.
    strcat(upload, letters);            // Add the misc letters that were entered.
    strcat(upload, "\"],");              // Add the last few brackets.

    // Add the timestamp field
    memset(value, '\0', 21);                    // Clear the value char array.
    strcat(upload, "\"4276\":[\"");              // Add the timestamp field.
    sprintf(value, "%lu", (unsigned long) time(NULL));       // This should put a timestamp into the upload string.
    strcat(upload, value);                        // Add the misc letters that were entered.
    strcat(upload, "\"]}}");                        // Add the last few brackets.

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

// Main, calls upload function. Uses parson for JSON serialization / parsing.
int main(void)
{
    char title[41];
    char letters[41];
    int timestamp;
    int num = 0;


    // Get user input.
    cout<<"Please enter a title for the dataset: ";
    cin.getline(title, 41, '\n');

    // Flush cin buffer
    //cin.ignore();

    cout<<"Please enter a bunch of letters (max 40 chars): ";
    cin.getline(letters, 41, '\n');



    upload_to_rsense_json_test();       // Basic serialization works, so that's good.
    upload_to_rsense_json_test(title, num, letters, timestamp);


/*
    // THIS IS AN OLD TEST USING MANUAL JSON ENCODING.
    // JUST FOR AN EXAMPLE.

    char title[41];
    char letters[41];
    int timestamp;
    int num = 0;

    // Get user input.
    cout<<"Please enter a title for the dataset: ";
    cin.getline(title, 41, '\n');

    cout<<"Please enter a number: ";
    cin>>num;

    // Flush cin buffer
    cin.ignore();

    cout<<"Please enter a bunch of letters (max 40 chars): ";
    cin.getline(letters, 41, '\n');

    // Get timestamp (unix)
    timestamp = (int)time(NULL);

    // Let the user know we're uploading. (Maybe add an option to confirm here in the future.)
    cout<<"\nUploading "<<num<<" to rSENSE.\n\n";

    // Right here I call a function to upload to rSENSE-dev.
    // I just pass it the title of the dataset and the number that the user entered.
    upload_to_rsense(title, num, letters, timestamp);

    // In the future we should tell the user if this upload function was a success. Or if it failed - if it failed then why.
*/
    return 0;
}