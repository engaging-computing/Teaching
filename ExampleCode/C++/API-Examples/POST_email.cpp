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

  // Get user input
  string title, ID, email, password, letters, num, timestamp;

  // Get user input.
  cout << "Please set the project ID for this dataset: ";
  getline(cin, ID);         // Get the project ID

  cout << "Please enter a title for the dataset: ";
  getline(cin, title);      // Get the title

  cout << "Please set an email address for this dataset: ";
  getline(cin, email);      // Get the email address

  cout << "Please enter a password for this dataset: ";
  getline(cin, password);   // Get the password

  /*  Add a timestamp to the title to avoid duplicates
   *        and to make it clear when the dataset was uploaded.   */
  timestamp = test.generate_timestamp();
  title = title + " "  + timestamp;

  // Add project info / dataset info to the object
  test.set_project_ID(ID);
  test.set_project_title(title);
  test.set_project_label("C++");

  while(!test.set_email_password(email, password))
  {
    cout << "Please set an email address for this dataset: ";
    getline(cin, email);      // Get the email address

    cout << "Please enter a password for this dataset: ";
    getline(cin, password);   // Get the password
  }

  // Do a quick test on the email / password to see if they are valid.
  test.get_check_user();

  // Let's also push some stuff back to the other vectors.
  /*
   *        Olsen hall
   *        42.654761, -71.326674
   */
  test.push_back("Number", "123456789");
  test.push_back("Text", "THIS");
  test.push_back("Latitude", "42.654761");
  test.push_back("Longitude", "-71.326674");

  // Let's add a timestamp using the provided generate_timestamp() method provided by the iSENSE class.
  test.generate_timestamp();
  test.push_back("Timestamp", timestamp);

  // Example of pushing numbers back into the object.
  for(int i = 0; i < 10; i++)
  {
    // Make sure to use "to_string" to convert an int/double/float/etc to a string.
    test.push_back("Number", to_string(i));
  }

  // Try grabbing fields. Error checking occurs below.
  test.get_project_fields();

  // Try formatting the upload data string without uploading yet.
  test.format_upload_string(3);

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

  cout << "\nUploading to rSENSE.\n";
  test.post_json_email();

  return 0;
}
