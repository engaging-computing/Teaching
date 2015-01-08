#include <iostream>
#include <stdio.h>
#include <curl/curl.h>                  //CURL to make HTTP requests
#include "../../../../picojson.h"        // May need to change the path for this if not in git repo

// Don't cloud up the namespace
using std::cout;
using std::cin;
using std::string;
using std::endl;

// For picojson
using namespace picojson;

// Change this for iSENSE, or leave it for rSENSE
const string devURL = "http://rsense-dev.cs.uml.edu/api/v1/projects/";

/*
    This program allows you to grab data from any rSENSE project.
    It could also work on iSENSE if you change the URL.

    It currently prints out the following information:
    1. All the data that is attached to the project in JSON format.
    2. Just the field object
    3. The field IDs, followed by their type (i.e. number/text/etc)
*/

// This is from the picojson example page
// I use it to save the JSON from iSENSE to memory (temporary)
typedef struct {
    char* data;       // response data from server
    size_t size;        // response size of data
} MEMFILE;

MEMFILE*  memfopen() {
    MEMFILE* mf = (MEMFILE*) malloc(sizeof(MEMFILE));
    mf->data = NULL;
    mf->size = 0;
    return mf;
}

void memfclose(MEMFILE* mf) {
    // Double check to make sure that mf exists.
    if(mf == NULL)
    {
        return;
    }

    // OK to free the char array
    if (mf != NULL && mf->data)
    {
        free(mf->data);
    }

    // And OK to free the structure
    free(mf);
}

size_t memfwrite(char* ptr, size_t size, size_t nmemb, void* stream) {
    MEMFILE* mf = (MEMFILE*) stream;
    int block = size * nmemb;

    if (!mf->data)
    {
        mf->data = (char*) malloc(block);
    }
    else
    {
        mf->data = (char*) realloc(mf->data, mf->size + block);
    }

    if (mf->data)
    {
        memcpy(mf->data + mf->size, ptr, block);
        mf->size += block;
    }

    return block;
}

char* memfstrdup(MEMFILE* mf)
{
    char* buf = (char*)malloc(mf->size + 1);
    memcpy(buf, mf->data, mf->size);
    buf[mf->size] = 0;

    return buf;
}


int main()
{
    // This project will try using CURL to make a basic GET request to rSENSE
    // It will then save the JSON it recieves into a picojson object.
    CURL *curl = curl_easy_init();
    CURLcode res;
    MEMFILE* json_file = memfopen();            // Writing JSON to this file.
    char error[256];                                       // Errors get written here
    string project_ID;

    // User enters a project ID
    cout << "Enter a project ID to find: ";
    cin >> project_ID;

    // Setting the GET URL here.
    string upload_URL = devURL+ project_ID;

    if(curl)
    {
        // Set the URL / error array
        curl_easy_setopt(curl, CURLOPT_URL, upload_URL.c_str());
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, &error);    // Write errors to the char array "error"

        // From the picojson example, "github-issues.cc". Used  for writing the JSON to a file.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, memfwrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, json_file);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors before trying to use the JSON
        if(res != CURLE_OK)
        {
            // Print out the error
            cout << "Error occured! Error is: ";
            cout << error << endl;

            // Quit so we don't go to the next part.
            exit(1);
        }

        // Good to try and parse the JSON into a PICOJSON object if we get here
        value json_data;             // parsed JSON will end up in here.
        string errors;                  // parsing errors will be written here.

        // This will parse the JSON file.
        parse(json_data, json_file->data, json_file->data + json_file->size, &errors);

        // If we have errors, print them out and quit.
        if(errors.empty() != true)
        {
            cout << "Error parsing JSON file!\n";
            cout << "Error was: " << errors;
            exit(2);
        }

        // Check to make sure json_data is a JSON object
        if(!field.is<piojson::object>())
        {
            cout << "Error, we do not have a JSON object.";
            exit(3);
        }

        // Output the entire string for fun.
        cout << "\nOutputting all the JSON: \n";
        string output_test = json_data.serialize();
        cout  << output_test << endl;

        // Try getting individual values, again for testing. We'll want to be able to grab fields after all!
        value field;
        field = json_data.get("fields");
        cout << "\nTesting fields: \n" << field.serialize() << "\n\n";

        // Check to make sure we have an array.
        if(!field.is<piojson::array>())
        {
            cout << "Error, we do not have a JSON array.";
            exit(4);
        }

        // So that worked! We were able to just grab the field object. Now we can iterate through the fields!
        array arr = field.get<array>();
        array::iterator it;

        cout << "Printing out all the fields here: \n";

        // We made an iterator above, that will let us run through the 3 fields (or how ever many we find) and print them out.
        for(it =arr.begin(); it != arr.end(); it++)
        {
            // Output all the fields
            object obj = it->get<object>();
            cout << "id: " << obj["id"].to_str();

            /*
                This part will be important for POSTing. We will want to save the fields and know what type they are.
                If we have a timestamp, number, text, latitude or longitude.
                We can detect this by looking at the "type" value.
            */

            // Grab the  type in number form.
            int type = obj["type"].get<double>();

            // Now we can build a switch statement around this!
            switch(type)
            {
                case 1:
                    cout << "\tWe got a timestamp field here!\n";
                    break;
                case 2:
                    cout << "\tFound a number here!\n";
                    break;
                case 3:
                    cout << "\tThere's some text over here!\n";
                    break;
                case 4:
                    cout << "\tLatitude here!\n";
                    break;
                case 5:
                    cout << "\tLongitude here!\n";
                    break;
                default:
                    cout << "Error, why'd we get here?\n";
                    break;
            }

        }

    }

    // Clean up cURL and close the memfile
    curl_easy_cleanup(curl);
    curl_easy_init();

    return 0;
}