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

//   // Debug info
//   cout << "This should be **empty** \n\n";
//   test.debug();
//
//   // These should all fail.
//   test.get_check_user();
//   test.get_project_fields();
//   test.post_json_email();
//   test.post_json_key();
//
//   // Debug info
//   cout << "This should still be **empty** \n\n";
//   test.debug();
//
//   // Add non-valid data to the object.
//   test.set_project_all("9999", "not-valid", "label", "999");
//
//   // Try uploading. This will fail.
//   test.post_json_key();
//
//   // Debug info
//   cout << "This obviously failed. \n\n";
//   test.debug();
//
//   // Now add valid data.
//   test.set_project_all("929", "valid", "Jason", "123");
//   test.push_back("Text", "this is some text");
//
//   // Try uploading. This will work.
//   test.post_json_key();
//
//   // Debug info
//   cout << "This should have worked. If not, see why. \n\n";
//   test.debug();

  // Should also test pushing back a vector.
  test.set_project_all("929", "valid", "Jason", "123");

  vector<string> vect_test;

  vect_test.push_back("string");
  vect_test.push_back("another string.");
  vect_test.push_back("one more string.");

  test.push_vector("text", vect_test);

  // Try uploading. This will work.
  test.post_json_key();

  // Debug info
  cout << "\n\nThis should have worked. If not, see why. \n\n";
  test.debug();

  // Let's try resetting the object.
  test.clear_data();

  // Debug
  cout << "\n\nData should be reset. Testing. \n\n";
  test.debug();

  return 0;
}
