#include <iostream>
#include <string>                    // std::string, std::to_string;
#include "include/API.h"

// To avoid poluting the namespace, and also to avoid typing std:: everywhere.
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::to_string;
using std::vector;


// Default constructor
iSENSE::iSENSE()
{
	// Set these to default values for future references
	upload_URL = "URL";
	get_URL = "URL";
	title = "title";
	project_ID = "empty";
	contributor_key = "key";
	contributor_label = "label";
}


// Constructor with parameters
iSENSE::iSENSE(string proj_ID, string proj_title, string label, string contr_key)
{
	set_project_ID(proj_ID);
	set_project_title(proj_title);
	set_project_label(label);
	set_contributor_key(contr_key);
}


// Similar to the constructor with parameters, but can be called at anytime to
// set up the upload object.
void iSENSE::set_project_all(string proj_ID, string proj_title, string label, string contr_key)
{
	set_project_ID(proj_ID);
	set_project_title(proj_title);
	set_project_label(label);
	set_contributor_key(contr_key);
}


// This function should be called by the user, and should set up all the fields.
void iSENSE::set_project_ID(string proj_ID)
{
	// Set the Project ID, and the upload/get URLs as well.
	project_ID = proj_ID;
	upload_URL = devURL + "/projects/" + project_ID + "/jsonDataUpload";
	get_URL = devURL + "/projects/" + project_ID ;
	get_project_fields();
}


// The user should also set the project title
void iSENSE::set_project_title(string proj_title)
{
	title = proj_title;
}


// This one is optional, by default the label will be "cURL".
void iSENSE::set_project_label(string label)
{
	contributor_label = label;
}


// As well as the contributor key they will be using
void iSENSE::set_contributor_key(string contr_key)
{
	contributor_key = contr_key;
}


// Extra function that the user can call to just generate a timestamp
// IT DOES NOT push back to the map of vectors! It merely returns a string,
// that users may grab and then send off to the push_back function.
string iSENSE::generate_timestamp(void)
{
	// Generates a ISO 8601 timestamp
	time_t time_stamp;
	time(&time_stamp);
	char buffer[sizeof "2011-10-08T07:07:09Z"];

	// This originally did not compile in Visual Studios. 
	// Note that "%F" and "%T" are not supported by Microsoft.
	strftime(buffer, sizeof buffer, "%Y-%m-%dT%H:%M:%SZ", gmtime(&time_stamp));

	string cplusplus_timestamp(buffer);

	// This function only returns the timestamp, it doesn't add it to the vector!
	return cplusplus_timestamp;
}


// Add data to the map, which keeps track of the data to be uploaded.
void iSENSE::push_back(string field_name, string data)
{
	// Add the piece of data to the back of the vector with the given field name.
	map_data[field_name].push_back(data);
}


// This is pretty much straight from the GET_curl.cpp file.
void iSENSE::get_project_fields()
{
	// Detect errors. We need a valid project ID before we try and perform a GET request.
	if(project_ID == "empty")
	{
		cout << "Error - project ID not set!\n";
		return;
	}

	// This project will try using CURL to make a basic GET request to rSENSE
	// It will then save the JSON it recieves into a picojson object.
	CURL *curl = curl_easy_init();;
	CURLcode res;
	MEMFILE* json_file = memfopen();           // Writing JSON to this file.
	char error[256];                                        // Errors get written here

	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, get_URL.c_str());
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
			return;
		}
		// Good to try and parse the JSON into a PICOJSON object if we get here
		string errors;

		// This will parse the JSON file.
		parse(get_data, json_file->data, json_file->data + json_file->size, &errors);

		// If we have errors, print them out and quit.
		if(errors.empty() != true)
		{
			cout << "Error parsing JSON file!\n";
			cout << "Error was: " << errors;
			return;
		}

		// Save the fields to the field array
		fields = get_data.get("fields");
		fields_array = fields.get<array>();
	}

	// Clean up cURL and close the memfile
	curl_easy_cleanup(curl);
	curl_easy_init();
}


// Call this function to POST data to rSENSE
void iSENSE::post_json_key()
{
	// Check that the project ID is set properly.
	// When the ID is set, the fields are also pulled down as well.
	if(project_ID == "empty")
	{
		cout << "\nError - please set a project ID!\n";
		return;
	}

	// Check that a title and contributor key has been set.
	if(title == "title")
	{
		cout << "\nError - please set a project title!\n";
		return;
	}

	if(contributor_key == "key")
	{
		cout << "\nErrror - please set a contributor key!\n";
		return;
	}

	// If a label wasn't set, automatically set it to "cURL"
	if(contributor_label == "label")
	{
		contributor_label = "cURL";
	}

	// Make sure the map actually has stuff pushed to it.
	if(map_data.empty() == true)
	{
		cout << "Map of keys/data is empty. You should push some data back to this object.\n";
		return;
	}

	// Should make sure each vector is not empty as well, since I had issues uploading
	// if any ONE vector was empty. rSENSE complained about the nil class.

	// Format the data to be uploaded. Call another function to format this.
	format_upload_string();

	/*  Once we get the data formatted, we can try to POST to rSENSE
	The below code uses cURL. It
	1. sets the headers, so iSENSE knows we are sending it JSON
	2. does some curl init stuff that makes the magic happen.
	3. cURL sends off the request, we can grab the return code to see if cURL failed.
	also check the curl verbose debug to see why something failed.       */

	// CURL object and response code.
	CURL *curl;
	CURLcode res;

	// In windows, this will init the winsock stuff
	res = curl_global_init(CURL_GLOBAL_DEFAULT);

	// Set the headers to JSON, makesure to use UTF-8
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Accept-Charset: utf-8");
	headers = curl_slist_append(headers, "charsets: utf-8");
	headers = curl_slist_append(headers, "Content-Type: application/json");

	// get a curl handle
	curl = curl_easy_init();

	if(curl)
	{
		// Set the URL that we will be using for our POST.
		curl_easy_setopt(curl, CURLOPT_URL, upload_URL.c_str());

		// This is necessary! As I had issues with only 1 byte being sent off to iSENSE
		// unless I made sure to make a string out of the upload_data picojson object,
		// then with that string you can call c_str() on it below.
		string upload_real = (value(upload_data).serialize());

		// POST data. Upload will be the string with all the data.
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, upload_real.c_str());

		// JSON Headers
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		// Verbose debug output - turn this on if you are having problems. It will spit out a ton of information,
		// such as bytes sent off, headers/access/etc. Useful to see if you formatted the data right.
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		cout << "\nrSENSE response: \n";

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


// This function is called by the JSON uplosad function
// It formats the upload string
void iSENSE::format_upload_string()
{
	// Add the title + the correct formatting
	upload_data["title"] = value(title);
	upload_data["contribution_key"] = value(contributor_key);
	upload_data["contributor_name"] = value(contributor_label);

	// Add each field, with its field ID and an array of all the data in its vector.

	// Grab all the fields using an iterator. Similar to printing them all out below in the debug function.
	array::iterator it;

	// Pointer to one of the vectors in the map
	vector<string> *vect;

	// Check and see if the fields object is empty
	if(fields.is<picojson::null>() == true)
	{
		// Print an error and quit, we can't do anything if the field array wasn't set up correctly.
		cout << "Error - field array wasn't set up. Have you pulled the fields off iSENSE?\n";
		return;
	}

	// We made an iterator above, that will let us run through the fields
	for(it = fields_array.begin(); it != fields_array.end(); it++)
	{
		// Get the current object
		object obj = it->get<object>();

		// Grab the field ID and save it in a string/
		string field_ID = obj["id"].to_str();

		// Grab the field name
		string name = obj["name"].get<string>();

		// Now add all the data in that field's vector (inside the map) to the fields_array object.
		vect = &map_data[name];
		format_data(vect, it, field_ID);
	}

	// Once we've made the field_data object, we can
	// add the field_data object to the upload_data object
	upload_data["data"] = value(fields_data);
}


// This makes the switch above shorter, since I reuse this code for all 5 types of data.
void iSENSE::format_data(vector<string> *vect, array::iterator it, string field_ID)
{
	vector<string>::iterator x;    // For going through the vector
	value::array data;             // Using a picojson::value::array, basically a vector but represents a json array.

	// First we push all the vector data into a json array.
	for(x = vect -> begin(); x < vect -> end(); x++)
	{
		data.push_back(value(*x));
	}

	// Now we push the json array to the upload_data object.
	fields_data[field_ID] = value(data);
}


// Call this function to dump all the data in the given object.
void iSENSE::debug()
{
	cout << "Project Title: \t\t" << title << endl;
	cout << "Project ID: \t\t" << project_ID << endl;
	cout << "Contributor  Key: \t" << contributor_key << endl;
	cout << "Contributor Label: \t" << contributor_label << endl;
	cout << "Upload URL: \t\t" << upload_URL << "\n";
	cout << "GET URL: \t\t" << get_URL << "\n\n";
	cout << "Upload string: \n" << value(upload_data).serialize() << "\n\n";
	cout << "GET Data: \n" << get_data.serialize() << "\n\n";
	cout << "GET Field Data: \n" << fields.serialize() << "\n\n";
}


// These are needed for picojson. Declared in memfile.h
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
