#include <iostream>                  // std::cout, std::cin
#include <string>                    // std::string, std::to_string;
#include "include/API.h"             // API class

/* This file requires Boost. Please make sure to run the following command before compiling:
 * sudo apt-get install libboost-test-dev
 * The above command installs Boost into your development environment.
 */
#define BOOST_TEST_MODULE API test
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

  Every function in the future should return something to make testing easier. Either a bool or
  an int would work.

*/

// using std::cin;
// using std::cout;
// using std::endl;
// using std::string;
// using std::to_string;
//
// // For picojson
// using namespace picojson;



// EOF