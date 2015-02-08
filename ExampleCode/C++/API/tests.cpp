#include <iostream>                  // std::cout, std::cin
#include <string>                    // std::string, std::to_string;
#include "include/API.h"             // API class

/*
  This file will run a series of tests on the C++ API
  The following methods should be tested:

  iSENSE()
  iSENSE(string proj_ID, string proj_title, string label, string contr_key)
  set_project_all(string proj_ID, string proj_title, string label, string contr_key)
  push_back(string)
  push_back(vector<string>)
  clear_data()
  format_data_upload()
  get_check_user()
  post_json_key()
  post_json_email()

  Every function in the future should return something to make testing easier. Either a bool or
  an int would work.

*/

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;

// For picojson
using namespace picojson;

// Main, calls upload function. Uses picojson for JSON serialization / parsing.
int main ()
{
  // First test: uploading a blank dataset.
  iSENSE test;

  // These should all fail.
  if(!test.get_check_user() && !test.get_project_fields() \
    && !test.post_json_email() && !test.post_json_key())
  {
    cout << "Test 1: All failures for empty object - PASSED\n";
  }
  else{
    cout << "Test 1: All failures for empty object - FAILED\n";
  }

  // Add non-valid data to the object.
  test.set_project_all("9999", "not-valid", "label", "999");

  // Try uploading. This will fail.
  if(!test.post_json_key())
  {
    cout << "Test 2: non-valid data fails - PASSED\n";
  }
  else{
    cout << "Test 2: non-valid data fails - FAILED\n";
  }

  // Make sure the title is unique.
  string timestamp = test.generate_timestamp();
  string title = "valid" + timestamp;

  // Now add valid data.
  test.set_project_all("929", title, "Jason", "123");
  test.push_back("Text", "this is some text");

  // Try uploading. This will work.
  if(test.post_json_key())
  {
    cout << "Test 3 - valid JSON data uploaded by key - PASSED\n";
  }
  else{
    cout << "Test 3 - valid JSON data uploaded by key - FAILED\n";
  }

  // Should also test pushing back a vector.
  test.set_project_all("929", "valid", "Jason", "123");

  vector<string> vect_test;

  vect_test.push_back("string.");
  vect_test.push_back("another string.");
  vect_test.push_back("one more string.");

  test.push_vector("Text", vect_test);

  // Try pushing back another string.
  test.push_back("Text", "final string.");

  // Push back to two other fields as well.
  test.push_back("Number", "12345");
  test.push_back("Timestamp","2011-10-08T07:07:09Z");

  // Try uploading. This will work.
  if(test.post_json_key())
  {
    cout << "Test 4 - valid vector of JSON data uploaded by key - PASSED\n";
  }
  else{
    cout << "Test 4 - valid vector of JSON data uploaded by key - FAILED\n";
  }

  // Let's try resetting the object.
  test.clear_data();

  // Here we should test the edit / append function.

  return 0;
}
