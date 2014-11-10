#include <iostream>               // Using C++, but also a C JSON library + libcURL, a C networking/HTTP library
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>             // cURL to make HTTP requests
#include <string.h>                 // libcurl likes c strings, also parson can format JSON into c strings
#include <cstring>
#include <time.h>                   // for time stamps

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::stringstream;    // for concating an int onto a string.


// This function will use the parson JSON library for parsing / serializing
void upload_to_rsense_json_test(char title[], int num, char letters[], int timestamp)
{
    // Let's see if we can take a title, number and some letters, along with making a timestamp
    // and send this off to rSENSE using
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;

    // Data will be its own string, that we will add to the upload object.
    JSON_Value *data_value = json_value_init_object();
    JSON_Object *data_object = json_value_get_object(data_value);
    char *data_string = NULL;

    char buffer[10];

    // Example field IDs
    int field_IDs[3] = {4274, 4275, 4276};

    sprintf(buffer, "%d", field_IDs[0]);                        // Convert a field ID to a string.
    json_object_set_number(data_object, buffer, num);           // add that field ID and the entered number to data_object
    memset(buffer, '\0', 21);                                   // Clear the value char array.

    sprintf(buffer, "%d", field_IDs[1]);                        // Convert a field ID to a string.
    json_object_set_string(data_object, buffer, letters);       // add the random string.

    memset(buffer, '\0', 21);                                   // Clear the value char array.
    sprintf(buffer, "%d", field_IDs[2]);                        // Convert a field ID to a string.
    json_object_set_string(data_object, buffer, title);

    data_string = json_serialize_to_string(data_value);         // Convert data JSON object to string.
    puts(data_string);                                          // Print it out.


    /*
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


    // The following is required.
    json_object_set_string(root_object, "title", title);
    json_object_set_string(root_object, "contribution_key", "123");
    json_object_set_string(root_object, "contributor_name", "cURL parson");


    /*

        Need to figure out how to get data with field IDs working here.
        Must be a way to do it easily. Hopefuilly.

    */

    // This part adds the variables given to the function.
    json_object_dotset_string(root_object, "data", data_string);

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

    time_t current_time;
    current_time = time(NULL);
    printf(ctime(&current_time));

    // This part combines everything entered above into one string that can be uploaded to rSENSE.
    strcat(upload, "{\"title\":\"");
    strcat(upload, title);                      // Add the title.
    strcat(upload, data);                       // Add the contributor stuff and the field ID.

    // Add the numbers.
    sprintf(value, "%d", num);                  // Convert the variable to a string
    strcat(upload, value);                      // Add the variable entered to the upload data.
    strcat(upload, "],");                       // Add the last few brackets.

    // Add the letters that were entered
    strcat(upload, "\"4275\":[\"");             // Add the next field ID to the upload string.
    strcat(upload, letters);                    // Add the misc letters that were entered.
    strcat(upload, "\"],");                     // Add the last few brackets.

    // Add the timestamp field
    memset(value, '\0', 21);                                // Clear the value char array.
    strcat(upload, "\"4276\":[\"");                         // Add the timestamp field.
    sprintf(value, "%lu", (unsigned long) time(NULL));      // This should put a timestamp into the upload string.
    strcat(upload, value);                                  // Add the misc letters that were entered.
    strcat(upload, "\"]}}");                                // Add the last few brackets.

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


// Main, calls upload function. Uses ***something*** for JSON serialization / parsing.
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

    cout << "Please enter a number: ";                         // Gets a number to upload to iSENSE
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