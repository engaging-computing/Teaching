#include <iostream>                  // std::cout, std::cin
#include <string>                    // std::string, std::to_string;
#include "include/API.h"             // API class

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;

// For picojson
using namespace picojson;

/*
 * This file requires Boost. Please make sure to run the following command before compiling:
 * sudo apt-get install libboost-test-dev
 * The above command installs Boost into your development environment.
 *
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>


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


// Ensure the CheckUser() method works.
BOOST_AUTO_TEST_CASE(Get_CheckUser)
{
  iSENSE test;

  // Add test project
  test.set_project_ID("929");
  test.set_project_title("Boost " + test.generate_timestamp());

  // This is a valid email / password - so it should return true.
  BOOST_REQUIRE(test.set_email_password("j@j.j", "j") == true);
}


// Test POSTing with Contributor keys
BOOST_AUTO_TEST_CASE(Post_JSON_withKey)
{
  iSENSE test("929", "test ", "BOOST Test", "123");

  // Make the title unique
  test.set_project_title("Boost " + test.generate_timestamp());

  // Push some data back
  test.push_back("Timestamp", test.generate_timestamp());
  test.push_back("Number", "123");
  test.push_back("Text", "ABC");

  BOOST_REQUIRE(test.post_json_key() == true);
}


// Test POSTing with Email/Password
BOOST_AUTO_TEST_CASE(Post_JSON_withEmail)
{
  iSENSE test("929", "test ", "BOOST Test", "123");

  // Make the title unique + set email/password
  test.set_project_title("Boost " + test.generate_timestamp());
  test.set_email_password("j@j.j", "j");

  // Push some data back
  test.push_back("Timestamp", test.generate_timestamp());
  test.push_back("Number", "123");
  test.push_back("Text", "ABC");

  BOOST_REQUIRE(test.post_json_email() == true);
}


// Test Appending with Dataset IDs
// (Email / Password)
BOOST_AUTO_TEST_CASE(Append_withDatasetID_byEmail)
{
  // Example of using the iSENSE class
  iSENSE test;
  string title, ID, dataset_ID, email, password, letters, num, timestamp;

  // This will be a test of the append method.
  ID = "929";
  title = "valid";
  email = "j@j.j";
  password = "j";
  dataset_ID = "7659";

  // Add project info / dataset info to the object
  test.set_project_ID(ID);
  test.set_dataset_ID(dataset_ID);
  test.set_project_title(title);
  test.set_email_password(email, password);

  test.push_back("Number", "123456789");
  test.push_back("Text", "THIS");
  test.push_back("Timestamp", test.generate_timestamp());

  BOOST_REQUIRE(test.append_email_byID(dataset_ID) == true);
}


// Test Appending with Dataset names
// (Email / Password)
BOOST_AUTO_TEST_CASE(Append_withDatasetName_byEmail)
{
  /*  This is taken from the POST_email_append_byName   */
  // Example of using the iSENSE class
  iSENSE test;
  string title, ID, dataset_name, email, password, letters, num, timestamp;

  // This will be a test of the append method.
  ID = "929";
  title = "valid";
  email = "j@j.j";
  password = "j";
  dataset_name = "testing";

  // Add project info / dataset info to the object
  test.set_project_ID(ID);
  test.set_project_title(title);
  test.set_email_password(email, password);

  // Push data back to the object.
  test.push_back("Number", "123456789");
  test.push_back("Text", "THIS");
  test.push_back("Timestamp", test.generate_timestamp());

  BOOST_REQUIRE(test.append_email_byName(dataset_name) == true);
}


// Test Appending with Dataset IDs
// (Contributor keys)
BOOST_AUTO_TEST_CASE(Append_withDatasetID_byKey)
{
  // Example of using the iSENSE class
  iSENSE test;
  string title, ID, dataset_ID, key, letters, num, timestamp;

  // This will be a test of the append method.
  title = "this works?";
  ID = "1029";
  key = "key";
  dataset_ID = "7795";

  // Add project info / dataset info to the object
  test.set_project_ID(ID);
  test.set_dataset_ID(dataset_ID);
  test.set_project_title(title);
  test.set_contributor_key(key);

  timestamp = test.generate_timestamp();

  test.push_back("Number", "99");

  BOOST_REQUIRE(test.append_key_byID(dataset_ID) == true);
}


// Test Appending with Dataset names
// (Contributor keys)
BOOST_AUTO_TEST_CASE(Append_withDatasetName_byKey)
{
  /*  This is taken from the POST_email_append_byName   */
  // Example of using the iSENSE class
  iSENSE test;
  string title, ID, dataset_name, label, key;

  // This will be a test of the append method.
  ID = "1029";
  title = "test";
  label = "BOOST Test";
  key = "key";
  dataset_name = "this works?";

  // Add project info / dataset info to the object
  test.set_project_ID(ID);
  test.set_project_title(title);
  test.set_project_label(label);
  test.set_contributor_key(key);

  // Push data back to the object.
  test.push_back("Number", "123456789");
  test.push_back("Text", "THIS");
  test.push_back("Timestamp", test.generate_timestamp());

  BOOST_REQUIRE(test.append_key_byName(dataset_name) == true);
}

