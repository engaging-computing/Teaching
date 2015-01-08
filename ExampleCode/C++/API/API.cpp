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
	// Set these to default values for future reference
	upload_URL = "URL";
	get_URL = "URL";
	get_UserURL = "URL";
	title = "title";
	project_ID = "empty";
	contributor_key = "key";
	contributor_label = "label";
	email = "email";
	password = "password";
}


// Constructor with parameters
iSENSE::iSENSE(string proj_ID, string proj_title, string label, string contr_key)
{
	set_project_ID(proj_ID);
	set_project_title(proj_title);
	set_project_label(label);
	set_contributor_key(contr_key);
}


// Similar to the constructor with parameters, but can be called at anytime to set up the upload object.
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
void iSENSE::set_project_label(string proj_label)
{
	contributor_label = proj_label;
}


// As well as the contributor key they will be using
void iSENSE::set_contributor_key(string proj_key)
{
	contributor_key = proj_key;
}


// Sets the email address to be used to upload data
void iSENSE::set_email(string proj_email)
{
	email = proj_email;
}


// Sets the password to be used
void iSENSE::set_password(string proj_password)
{
	password = proj_password;
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


// Searches for projects with the search term.
// Returns a vector with projects that show up.
vector<string> iSENSE::get_projects_search(string search_term)
{
	string get_search = devURL + "/projects?utf8=true&search=" + search_term + "&sort=updated_at&order=DESC";

	// Vector of project titles.
	vector<string> project_titles;

	// This project will try using CURL to make a basic GET request to rSENSE
	CURL *curl = curl_easy_init();;			// cURL object
	CURLcode curl_code;									// cURL status code
	long http_code;											// HTTP status code
	MEMFILE* json_file = memfopen();    // Writing JSON to this file.
	char error[256];                    // Errors get written here

	if(curl)
	{
		// Set the GET URL, in this case the one be created above using the user's
		// email & password.
		curl_easy_setopt(curl, CURLOPT_URL, get_search.c_str());
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, &error);    	// Write errors to the char array "error"

		// From the picojson example, "github-issues.cc". Used  for writing the JSON to a file.
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, memfwrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, json_file);

		// Perform the request
		curl_easy_perform(curl);

		// We can actually get the HTTP response code from cURL, so let's do that to check for errors.
		http_code = 0;

		// This will put the HTTP response code into the "http_code" variable.
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

		/*
		The iSENSE API gives us one response code to check against:
		Success: 200 OK
		If we do not get a code 200 from iSENSE, something went wrong.
		*/

		// If we do not get a code 200, or cURL quits for some reason, we didn't successfully
		// get the project's fields.
		if(http_code != 200)
		{
			cout << "\nProject search failed.\n";

			// Clean up cURL and close the memfile
			curl_easy_cleanup(curl);
			curl_global_cleanup();
			memfclose(json_file);

			return project_titles;
		}

		// We got a code 200, so try and parse the JSON into a PICOJSON object.
		// Error checking for the parsing occurs below.
		string errors;
		value projects_json;

		// This will parse the JSON file.
		parse(projects_json, json_file->data, json_file->data + json_file->size, &errors);

		// If we have errors, print them out and quit.
		if(errors.empty() != true)
		{
			cout << "\nError parsing JSON file!\n";
			cout << "Error was: " << errors;

			// Clean up cURL and close the memfile
			curl_easy_cleanup(curl);
			curl_global_cleanup();
			memfclose(json_file);

			return project_titles;
		}

		// Convert the JSON array (projects_json) into a vector of strings (strings would be project titles);
		array projects_array = projects_json.get<array>();;
		array::iterator it, the_begin, the_end;

		the_begin = projects_array.begin();
		the_end = projects_array.end();

		// Check and see if the projects_title JSON array is empty
		if(the_begin == the_end)
		{
			// Print an error and quit, we can't make a vector of project titles to return
			// if the JSON array ended up empty. Probably wasn't any projects with that search term.
			cout << "\nProject title array is empty.\n";

			// Clean up cURL and close the memfile
			curl_easy_cleanup(curl);
			curl_global_cleanup();
			memfclose(json_file);

			return project_titles;	// this is an empty vector
		}

		// If we make here, we can make a vector of project titles and return that to the user.
		for(it = projects_array.begin(); it != projects_array.end(); it++)
		{
			// Get the current object
			object obj = it->get<object>();

			// Grab the field name
			string name = obj["name"].get<string>();

			// Push the name back into the vector.
			project_titles.push_back(name);
		}

		// Clean up cURL and close the memfile
		curl_easy_cleanup(curl);
		curl_global_cleanup();
		memfclose(json_file);

		return project_titles;
	}
}


// Checks to see if the email / password is valid
bool iSENSE::get_check_user()
{
	// First check to see if the email and password have been set.
	if(email == "email" || password == "password")
	{
		cout << "Please set an email & password for this project.\n";
	}
	else if(email.empty() == true || password.empty() == true)
	{
		cout << "Please set an email & password for this project.\n";
	}

	// If we get here, an email and password have been set, so do a GET using
	// the email & password.

	get_UserURL = devURL + "/users/myInfo?email=" + email + "&password=" + password;

	// This project will try using CURL to make a basic GET request to rSENSE
	CURL *curl = curl_easy_init();;			// cURL object
	CURLcode curl_code;									// cURL status code
	long http_code;											// HTTP status code

	if(curl)
	{
		// Set the GET URL, in this case the one be created above using the user's
		// email & password.
		curl_easy_setopt(curl, CURLOPT_URL, get_UserURL.c_str());

		// Disable libcURL's desire to output to the screen by giving it a
		// write function which basically does nothing but returns the size of what
		// would have been outputted.
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, suppress_output);

		// Perform the request
		curl_easy_perform(curl);

		// We can actually get the HTTP response code from cURL, so let's do that to check for errors.
		http_code = 0;

		// This will put the HTTP response code into the "http_code" variable.
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

		/*
				The iSENSE API gives us two response codes to check against:
				Success: 200 OK
				Failure: 401 Unauthorized
		*/

		if(http_code == 200)
		{
			// Clean up cURL
			curl_easy_cleanup(curl);
			curl_global_cleanup();

			// Return success.
			return true;
		}
		else {
				cout << "\nThe email and/or password you entered was **not** valid.\n";
				cout << "Please try entering the email / password again.\n";

				// Clean up cURL
				curl_easy_cleanup(curl);
				curl_global_cleanup();

				// Return failure.
				return false;
		}
	}
}


// This is pretty much straight from the GET_curl.cpp file.
bool iSENSE::get_project_fields()
{
	// Detect errors. We need a valid project ID before we try and perform a GET request.
	if(project_ID == "empty" || project_ID.empty() == true)
	{
		cout << "Error - project ID not set!\n";
		return false;
	}

	// This project will try using CURL to make a basic GET request to rSENSE
	// It will then save the JSON it recieves into a picojson object.
	CURL *curl = curl_easy_init();;			// cURL object
	CURLcode curl_code;									// cURL status code
	long http_code;											// HTTP status code
	MEMFILE* json_file = memfopen();    // Writing JSON to this file.
	char error[256];                    // Errors get written here

	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, get_URL.c_str());
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, &error);    // Write errors to the char array "error"

		// From the picojson example, "github-issues.cc". Used  for writing the JSON to a file.
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, memfwrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, json_file);

		// Perform the request, res will get the return code
		curl_code = curl_easy_perform(curl);

		// We can actually get the HTTP response code from cURL, so let's do that to check for errors.
		http_code = 0;

		// This will put the HTTP response code into the "http_code" variable.
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

		/*
				The iSENSE API gives us one response code to check against:
				Success: 200 OK
				If we do not get a code 200 from iSENSE, something went wrong.
		*/

		// If we do not get a code 200, or cURL quits for some reason, we didn't successfully
		// get the project's fields.
		if(http_code != 200)
		{
			cout << "\nGET project fields failed.\n";
			cout << "Is the project ID you entered valid?\n";

			// Clean up cURL and close the memfile
			curl_easy_cleanup(curl);
			curl_global_cleanup();
			memfclose(json_file);

			return false;
		}

		// We got a code 200, so try and parse the JSON into a PICOJSON object.
		// Error checking for the parsing occurs below.
		string errors;

		// This will parse the JSON file.
		parse(get_data, json_file->data, json_file->data + json_file->size, &errors);

		// If we have errors, print them out and quit.
		if(errors.empty() != true)
		{
			cout << "\nError parsing JSON file!\n";
			cout << "Error was: " << errors;
			return false;
		}

		// Save the fields to the field array
		fields = get_data.get("fields");
		fields_array = fields.get<array>();
	}

	// Clean up cURL and close the memfile
	curl_easy_cleanup(curl);
	curl_global_cleanup();
	memfclose(json_file);

	// Return true as we were able to successfully get the project's fields.
	return true;
}


// Call this function to POST data to rSENSE
bool iSENSE::post_json_key()
{
	/*
			These first couple of if statements perform some basic error checking, such as
			whether or not all the required fields have been set up.
	*/

	// Check that the project ID is set properly.
	// When the ID is set, the fields are also pulled down as well.
	if(project_ID == "empty" || project_ID.empty() == true)
	{
		cout << "\nError - please set a project ID!\n";
		return false;
	}

	// Check that a title and contributor key has been set.
	if(title == "title" || title.empty() == true)
	{
		cout << "\nError - please set a project title!\n";
		return false;
	}

	if(contributor_key == "key" || contributor_key.empty() == true)
	{
		cout << "\nErrror - please set a contributor key!\n";
		return false;
	}

	// If a label wasn't set, automatically set it to "cURL"
	if(contributor_label == "label" || contributor_label.empty() == true)
	{
		contributor_label = "cURL";
	}

	// Make sure the map actually has stuff pushed to it.
	if(map_data.empty() == true)
	{
		cout << "\nMap of keys/data is empty. You should push some data back to this object.\n";
		return false;
	}

	// Should make sure each vector is not empty as well, since I had issues uploading
	// if any ONE vector was empty. rSENSE complained about the nil class.

	// Format the data to be uploaded. Call another function to format this.
	format_upload_string(true);

	/*  Once we get the data formatted, we can try to POST to rSENSE
	The below code uses cURL. It
	1. Sets the headers, so iSENSE knows we are sending it JSON
	2. Does some curl init stuff that makes the magic happen.
	3. cURL sends off the request, we can grab the return code to see if cURL failed.
		 Also check the curl verbose debug to see why something failed.
	4. We also get the HTTP status code so we know if iSENSE handled the request or not. */

	// CURL object and response code.
	CURL *curl = curl_easy_init();;			// cURL object
	CURLcode curl_code;									// cURL status code
	long http_code;											// HTTP status code

	// In windows, this will init the winsock stuff
	curl_code = curl_global_init(CURL_GLOBAL_DEFAULT);

	// Set the headers to JSON, make sure to use UTF-8
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
		curl_code = curl_easy_perform(curl);

		// This will put the HTTP response code into the "http_code" variable.
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

		/*
				The iSENSE API gives us two response codes to check against:
				Success: 200 OK (iSENSE handled the request fine)
				Failure: 401 Unauthorized (email / password or contributor key was not valid)
				Failure: 422 Unprocessable Entity (email or contributor key was fine, but there was an issue with
				the request's formatting. Something in the formatting caused iSENSE to fail.)
		*/

		if(http_code == 200)
		{
			cout << "\n\nPOST request successfully sent off to iSENSE!\n";
			cout << "The URL to your project is: " << dev_baseURL << "/projects/" << project_ID << endl;
			return true;
		}
		else if(http_code == 401)
		{
			cout << "\n\nPOST request **failed**\n";
			cout << "Try checking to make sure your contributor key is valid\n";
			cout << "for the project you are trying to contribute to.\n";
			return false;
		}
		else if(http_code == 422)
		{
			cout << "\n\nPOST request **failed**\n";
			cout << "Something went wrong with iSENSE.\n";
			cout << "Try formatting your data differently,\n";
			cout << "using an email & password instead of a contributor key,\n";
			cout << "or asking for help from others. You can also try running the\n";
			cout << "the program with the \"debug\" method enabled, by typing: \n";
			cout << "object_name.debug()\n";
			cout << "This will output a ton of data to the console and may help you in\n";
			cout << "debugging your program.\n";
			return false;
		}
		else {
			cout << "\n\nPOST request failed for some unknown reason.\n";
			return false;
		}

		// For cURL return codes, see the following page:
		// http://curl.haxx.se/libcurl/c/libcurl-errors.html
		cout << "\ncURL return code was: " << curl_code << endl;

		// Check for errors
		if(curl_code != CURLE_OK)
		{
			fprintf(stderr, "\ncurl_easy_perform() failed: %s\n",
			curl_easy_strerror(curl_code));
		}
	}
	curl_easy_cleanup(curl);                // always cleanup
	curl_global_cleanup();
}


// Post using a email / password
bool iSENSE::post_json_email()
{
	/*
		These first couple of if statements perform some basic error checking, such as
		whether or not all the required fields have been set up.
	*/

	// Check that the project ID is set properly.
	// When the ID is set, the fields are also pulled down as well.
	if(project_ID == "empty" || project_ID.empty() == true)
	{
		cout << "\nError - please set a project ID!\n";
		return false;
	}

	// Check that a title and contributor key has been set.
	if(title == "title" || title.empty() == true)
	{
		cout << "\nError - please set a project title!\n";
		return false;
	}

	if(email == "email" || email.empty() == true)
	{
		cout << "\nErrror - please set an email address!\n";
		return false;
	}

	if(password == "password" || password.empty() == true)
	{
		cout << "\nErrror - please set a password!\n";
		return false;
	}

	// If a label wasn't set, automatically set it to "cURL"
	if(contributor_label == "label" || contributor_label.empty() == true)
	{
		contributor_label = "cURL";
	}

	// Make sure the map actually has stuff pushed to it.
	if(map_data.empty() == true)
	{
		cout << "\nMap of keys/data is empty. You should push some data back to this object.\n";
		return false;
	}

	// Should make sure each vector is not empty as well, since I had issues uploading
	// if any ONE vector was empty. rSENSE complained about the nil class.

	// Format the data to be uploaded. Call another function to format this.
	format_upload_string(false);

	/*  Once we get the data formatted, we can try to POST to rSENSE
	The below code uses cURL. It
	1. sets the headers, so iSENSE knows we are sending it JSON
	2. does some curl init stuff that makes the magic happen.
	3. cURL sends off the request, we can grab the return code to see if cURL failed.
	also check the curl verbose debug to see why something failed.       */

	// CURL object and response code.
	CURL *curl = curl_easy_init();;			// cURL object
	CURLcode curl_code;									// cURL status code
	long http_code;											// HTTP status code

	// In windows, this will init the winsock stuff
	curl_code = curl_global_init(CURL_GLOBAL_DEFAULT);

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

		// Perform the request, curl_code will get the return code
		curl_code = curl_easy_perform(curl);

		// This will put the HTTP response code into the "http_code" variable.
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

		/*
				The iSENSE API gives us two response codes to check against:
				Success: 200 OK (iSENSE handled the request fine)
				Failure: 401 Unauthorized (email / password or contributor key was not valid)
				Failure: 422 Unprocessable Entity (email or contributor key was fine, but there was an issue with
				the request's formatting. Something in the formatting caused iSENSE to fail.)
		*/

		if(http_code == 200)
		{
			cout << "\n\nPOST request successfully sent off to iSENSE!\n";
			cout << "The URL to your project is: " << dev_baseURL << "/projects/" << project_ID << endl;
			return true;
		}
		else if(http_code == 401)
		{
			cout << "\nPOST request **failed**\n";
			cout << "Try checking to make sure your contributor key is valid\n";
			cout << "for the project you are trying to contribute to.\n";
			return false;
		}
		else if(http_code == 422)
		{
			cout << "\n\nPOST request **failed**\n";
			cout << "Something went wrong with iSENSE.\n";
			cout << "Try formatting your data differently,\n";
			cout << "using a contributor key instead of an email/password,\n";
			cout << "or asking for help from others. You can also try running the\n";
			cout << "the program with the \"debug\" method enabled, by typing: \n";
			cout << "object_name.debug()\n";
			cout << "This will output a ton of data to the console and may help you in\n";
			cout << "debugging your program.\n";
			return false;
		}
		else {
			cout << "\n\nPOST request failed for some unknown reason. :/\n";
			return false;
		}

		// For cURL return codes, see the following page:
		// http://curl.haxx.se/libcurl/c/libcurl-errors.html
		cout << "\ncURL return code was: " << curl_code << endl;

		// Check for errors
		if(curl_code != CURLE_OK)
		{
			fprintf(stderr, "\ncurl_easy_perform() failed: %s\n",
			curl_easy_strerror(curl_code));
		}
	}
	curl_easy_cleanup(curl);                // always cleanup
	curl_global_cleanup();
}


// This function is called by the JSON uplosad function
// It formats the upload string
void iSENSE::format_upload_string(bool key)
{
	// Add the title + the correct formatting
	upload_data["title"] = value(title);

	if(key == true)
	{
		upload_data["contribution_key"] = value(contributor_key);
		upload_data["contributor_name"] = value(contributor_label);
	}
	else{
		upload_data["email"] = value(email);
		upload_data["password"] = value(password);
	}

	// Add each field, with its field ID and an array of all the data in its vector.

	// Grab all the fields using an iterator. Similar to printing them all out below in the debug function.
	array::iterator it;

	// Pointer to one of the vectors in the map
	vector<string> *vect;

	// Check and see if the fields object is empty
	if(fields.is<picojson::null>() == true)
	{
		// Print an error and quit, we can't do anything if the field array wasn't set up correctly.
		cout << "\nError - field array wasn't set up. Have you pulled the fields off iSENSE?\n";
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
	cout << "\nProject Title: " << title << endl;
	cout << "Project ID: " << project_ID << endl;
	cout << "Contributor  Key: " << contributor_key << endl;
	cout << "Contributor Label: " << contributor_label << endl;
	cout << "Email Address: " << email << endl;
	cout << "Password: " << password << endl;
	cout << "Upload URL: " << upload_URL << endl;
	cout << "GET URL: " << get_URL << endl;
	cout << "GET User URL: " << get_UserURL << "\n\n";
	cout << "Upload string: \n" << value(upload_data).serialize() << "\n\n";
	cout << "GET Data: \n" << get_data.serialize() << "\n\n";
	cout << "GET Field Data: \n" << fields.serialize() << "\n\n";
	cout << "Map data: \n";

	// These for loops will dump all the data in the map.
	// Good for debugging.
	for(map<string, vector<string>>::iterator it = map_data.begin(); it != map_data.end(); it++)
	{
		cout << it->first << " ";

		for(vector<string>::iterator vect = (it->second).begin(); vect != (it->second).end(); vect++)
		{
			cout << *vect << " ";
		}

		cout << "\n";
	}
}


//**********************************************************************************
// These are needed for picojson & libcURL. Declared in memfile.h but defined below.
//**********************************************************************************
MEMFILE*  memfopen()
{
	MEMFILE* mf = (MEMFILE*) malloc(sizeof(MEMFILE));
	mf->data = NULL;
	mf->size = 0;
	return mf;
}

void memfclose(MEMFILE* mf)
{
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


// Simple function only used by the get_check_user function to suppress curl's output to the screen.
size_t suppress_output(char* ptr, size_t size, size_t nmemb, void* stream)
{
	return size * nmemb;
}


size_t memfwrite(char* ptr, size_t size, size_t nmemb, void* stream)
{
	MEMFILE* mf = (MEMFILE*) stream;
	int block = size * nmemb;

	if (!mf->data)
	{
		mf->data = (char*) malloc(block);
	}
	else {
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
