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

// Main, calls upload function. Uses picojson for JSON serialization / parsing.
int main ()
{
  // Example of using the iSENSE class
  iSENSE test;

  // Test the output
  test.debug();

  test.set_project_ID("929");

  // Get all the datasets and media objects.
  test.get_datasets_and_mediaobjects();

  // More debugging - see if the above project exists and if datasets are
  // all saved inside the iSENSE object.
  test.debug();

  // Try clearing out the object.
  test.clear_data();
  test.debug();

  return 0;
}
