#ifndef API_h
#define API_h

// Windows likes the curl header this way.
#ifdef WIN32
#include <curl.h>                 // cURL to make HTTP requests

// Linux / other systems. (Test MacOS and see if it likes it this way or the Windows way)
#else
#include <curl/curl.h>            // cURL to make HTTP requests
#endif

#include <ctime>                  // Timestamps
#include <iostream>
#include <map>
#include <string>                 // std::string, std::to_string;
#include <vector>
#include "picojson.h"             // picojson for using JSON easily.
#include "memfile.h"              // picojson/curl uses this for temp files.

/*
 *    To do list:
 *
 *    1. Appending / editing datasets
 *      - Appending now works and can also pull down all the datasets in a project.
 *      - Try the edit API call and see if its useful.
 *
 *    2. Pulling data off of iSENSE, then appending to that via push_back.
 *      - This can now be done since pulling datasets works.
 *      - Need to add a way to return data in the form of some sort of map though.
 *        That way users can pull down datasets, get a map to play with and then
 *        reupload data through push_back(string) and push_back(vector)
 *
 *    3. Media objects
 *      - Since datasets are pulled down, media objects also get pulled down.
 *        Could add the same ability as datasets - return a map of media objects
 *      - Also work on allowing media objects to be pushed to iSENSE through the
 *        media objects API call
 *
 *    4. Test file that should also work as an example of all the various API methods
 *      - Boost tests now written.
 *      - Only 7 which test basic JSON uploading and appending.
 *      - Should test more areas of the API
 *
 *    5. Dice roll app to serve as another example.
 *      - Possible to rewrite it using the API now.
 *      - Should be very simple. Add it to the Makefile once completed.
 *
 *    6. Baseball app to serve as an example of pulling data and uploading it.
 *      - Requires above mentioned map of datasets.
 *      - Can use the push_back(vector) method to push data back to iSENSE.
 *
 *    7. Create a zip file for people to download for Linux / Mac.
 *      - Install script could be useful.
 *        Just need to write a bash script that install curl, git clones the repo,
 *        curls picojson.h off of the picojson repo and then runs the Makefile
 *        to test stuff.
 *
 *    Currently working on:
 *    Linux (64 bit) -> Uses a Makefile
 *    Mac OS 10.10 (64 bit) -> should work the same as Linux
 *    Windows 7 / 8.1 (64 bit) -> Requires Visual Studios
 */

/*
 * NOTE:
 * Most of the API calls expect that you have already set an email & password OR a contributor
 * key, as well as a project ID and a project title. You can set these by either calling the
 * default constructor with parameters, or by calling one of the set methods.
 *
 */

// To avoid poluting the namespace, and also to avoid typing std:: everywhere.
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::to_string;
using std::vector;

// For picojson
using namespace picojson;

// Constants for the rest of the class
const string dev_baseURL = "http://rsense-dev.cs.uml.edu";
const string live_baseURL = "http://isenseproject.org";
const string devURL = "http://rsense-dev.cs.uml.edu/api/v1";
const string liveURL = "http://isenseproject.org/api/v1";

const int CURL_ERROR = -1;
const string GET_ERROR = "ERROR";

class iSENSE
{
public:
  iSENSE();                                          // Default constructor
  iSENSE(string proj_ID, string proj_title,          // Contructor with parameters
         string label, string contr_key);


  // Similar to the constructor with parameters, but called after the object is created.
  // This way you can change/update the title/project ID/etc.
  void set_project_all(string proj_ID, string proj_title,
                       string label, string contr_key);

  void set_project_ID(string proj_ID);          // This function should set up all the fields
  void set_project_title(string proj_title);    // The user should also set the project title
  void set_project_label(string proj_label);    // Optional, by default the label will be "cURL"
  void set_contributor_key(string proj_key);    // User needs to set the contributor key

  // This function should be used for setting the email / password for a project.
  // It will return true if the email / password are valid, or false if they are not.
  bool set_email_password(string proj_email, string proj_password);

  /*  This function will push data back to the map.
   *  User must give the pushback function the following:
   *    1. Field name (as seen on iSENSE)
   *    2. Some data (in string format). For numbers, use to_string.
   *
   *  Note: this function merely pushes a single piece of data to the map.
   *  If you would like to add more than one string of data, you should used
   *  either a loop or create a vector of strings and push that back to the object.
   */
  void push_back(string field_name, string data);

  /* Add a field name / vector of strings (data) to the map.
   * See above notes. Behaves similar to the push_back function.
   * Also - if you push a vector back, it makes a copy of the vector and saves it
   * in the map. You will need to use the push_back function to add more data.
   */
  void push_vector(string field_name, vector<string> data);

  // Resets the object and clears the map.
  void clear_data();

  // Timestamp function to make it easier for users to use timestamps in their project.
  // Only returns the timestamp, does not add it to the map.
  string generate_timestamp(void);

  // This formats the upload string
  void format_upload_string(int key);

  // This formats one FIELD ID : DATA pair
  void format_data(vector<string> *vect, array::iterator it, string field_ID);

  // This function makes a POST request via libcurl
  int post_data_function(int type);

  /*  iSENSE API functions
   *        Note: methods which return bool return true for success and false for failure.
   *        They also output the reasons for failure to the screen.   */
  bool get_check_user();          // Checks to see if a username / password is valid
  bool get_project_fields();      // Pulls the fields and puts them into the fields object & array

  // This function grabs fields, datasets, media objects and owner information
  // Saves these arrays into picojson arrays.
  bool get_datasets_and_mediaobjects();

  // Search for projects with the search term
  vector<string> get_projects_search(string search_term);

  // Return a vector of data given a field name
  vector<string> get_dataset(string dataset_name, string field_name);

  // Future: return a map of media objects
  // map<string, vector<string> > get_media_objects();

  bool post_json_email();          // Post using a email / password
  bool post_json_key();            // Post using contributor key

  /*    Notes about the append & edit functions
   *
   *    Appending & editing by key is tricky.
   *    In general, you should only be able to append or edit a dataset that you uploaded with
   *    your contributor key. You cannot append to just any project with email & password. It
   *    DOES not work like uploading a dataset - you will only be able to append to datasets you
   *    own - i.e. projects you've created while logged in.
   *
   *    To sum up:
   *    A Contributor key can append to datasets that YOUR KEY uploaded.
   *    Email & password can append to datasets YOU uploaded OR any datasets in projects YOU created.
   *
   *    NOTE: You do not need call
   *    bool get_datasets_and_mediaobjects();
   *    before using any of the editing and appending methods.
   *    All append methods automatically call this function.
   *
   *    Note - the edit functions are not yet complete.
   *
   */

  // Appends to a dataset using a dataset name and either a key or email/password
  bool append_key_byName(string dataset_name);
  bool append_email_byName(string dataset_name);

  // Helper methods
  std::string get_Dataset_ID(string dataset_name);
  std::string get_Field_ID(string field_name);

  /*  Future functions to be implemented at a later date.
      //  Editing API calls (not yet implemented)
      bool get_edit_key();      // Edit a dataset with a dataset ID & contributor key
      bool get_edit_user();     // Edit a dataset with a dataset ID & email / password

      //  Post media objects - this is less of a priority but still could be interesting to do.
      bool post_media_objects_email();
      bool post_media_objects_key();

      void get_fields_by_id();       // Get information about a field by field ID
      void post_fields_email();      // Post fields  by email / password
      void post_projects_email();    // Post a project by email / password
   */

  // For debugging, this method dumps all the data.
  void debug();


protected:

  /*  Users do not need to worry about dataset IDs. They only need to pass the
   *  append function a valid dataset name - that is, the name as it appears on iSENSE.
   *  This method is marked as protected to prevent users from accessing it.
   */
  void set_dataset_ID(string proj_dataset_ID);  // Need to set the dataset ID for appending.
  bool append_key_byID(string dataset_ID);       // Appends a dataset with a contributor key
  bool append_email_byID(string dataset_ID);        // Amend a dataset with a email / password

private:

  /*  These two 'objects' are picojson objects that will be used to upload to iSENSE.
   *  The upload_data object contains the entire upload string, in JSON format.
   *  Picojson will let us output this to a string and then pass that string to libcurl.
   *  The fields data object is the object that the 'data' part contains in the upload_data object.
   *  Basically it is a bunch of key:values, with the key being the field ID and the value being an
   *  array of data, whether it be numbers/text/etc.    */
  object upload_data, fields_data, owner_info;

  /*  These three objects are the data that is pulled off iSENSE for the given project.
   *  The get_data object contains all the data we can pull off of iSENSE (like what you find
   *  on /api/v1/projects/DATASET_ID_HERE). The fields object then contains just the field
   *  information, and the fields_array has that same data in an array form for iterating
   *  through it.  */
  value get_data, fields;
  array fields_array, data_sets, media_objects;

  /*  Data to be uploaded to iSENSE. The string is the field name, the vector of strings
   *  contains all the data for that field name.  */
  map<string, vector<string> > map_data;

  // Data needed for processing the upload request
  //bool usingDev;                  // Whether the user wants iSENSE or rSENSE
                                    // (currently not implemented, future idea)

  string upload_URL;                // URL to upload the JSON to
  string get_URL;                   // URL to grab JSON from
  string get_UserURL;               // URL to test credentials
  string title;                     // title for the dataset
  string project_ID;                // project ID of the project
  string dataset_ID;                // dataset ID for the dataset you want to append to.
  string contributor_label;         // Label for the contributor key. by default this is "cURL"
  string contributor_key;           // contributor key for the project
  string email;                     // Email to be used to upload the data
  string password;                  // Password to be used with the above email address
};

#endif
