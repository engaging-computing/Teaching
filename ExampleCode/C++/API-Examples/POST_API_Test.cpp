#include <iostream>                  // std::cout, std::cin
#include <string>                    // std::string, std::to_string;
#include "include/API.h"             // API class

/*  Quick test of the API / C++ class
 *  Hard coded to project 993.          */

// To avoid poluting the namespace, and also to avoid typing std:: everywhere.
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

  // Get user input
  string title, ID, key, letters, num, timestamp;

  // Quick test of the API, hard coding some of this.
  ID = "993";
  key = "123";
  title = "Hello, World";

  /*  Add a timestamp to the title to avoid duplicates
   *    and to make it clear when the dataset was uploaded.   */
  timestamp = test.generate_timestamp();
  title = title + " "  + timestamp;

  // Add project info / dataset info to the object
  test.set_project_ID(ID);
  test.set_project_title(title);
  test.set_project_label("cURL");
  test.set_contributor_key(key);

  test.push_back("One Number", "1");

  // Example of pushing numbers back into the object.
  for(int i = 1; i < 101; i++)
  {
    // Make sure to use "to_string" to convert an int/double/float/etc to a string.
    test.push_back("100 Numbers", to_string(i));
  }

  // Try grabbing fields. Error checking occurs below.
  test.get_project_fields();

  // Try formatting the upload data string without uploading yet.
  test.format_upload_string(true);

  // Check the fields for errors (manually compare against iSENSE)
  test.debug();

  char ans;

  do{
    cout << "Does the data look alright to you? (enter y/n) -> ";
    cin >> ans;
  }while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');

  if(ans == 'n' || ans == 'N')
  {
    cout << "\nUser chose not to upload. Quitting instead.\n";
    return 0;
  }

  cout << "Uploading to rSENSE.\n";
  test.post_json_key();

  // In the future we should tell the user if this upload function was a success. Or if it failed then why.
  return 0;
}
