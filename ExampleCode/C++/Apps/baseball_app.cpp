#include <iostream>                  // std::cout, std::cin
#include <string>                    // std::string, std::to_string;
#include "include/API.h"             // API class

// Main, calls upload function. Uses picojson for JSON serialization / parsing.
int main ()
{
  // Example of using the iSENSE class
  iSENSE test;

  // Set the project ID
  test.set_project_ID("106");

  // Get all the datasets and media objects.
  test.get_datasets_and_mediaobjects();

  // Now let's try getting the a row of data to mess with.
  vector<string> baseball_hits = test.get_dataset("MLB Team Statistics 2013", "Runs");

  // Let's try printing out all the runs we found:
  vector<string>::iterator tmp;

  cout << "Runs for MLB 2013:\n";
  for(tmp = baseball_hits.begin(); tmp != baseball_hits.end(); tmp++)
  {
    cout << *tmp << endl;
  }

  // We could now do fun stuff with that data, like find the average runs, or w/e
  // and then push this average to another iSENSE object and submit this to
  // a project.
  // Or we could add more runs we have stored locally, and push this vector to
  // another iSENSE object.
  // etc.

  return 0;
}
