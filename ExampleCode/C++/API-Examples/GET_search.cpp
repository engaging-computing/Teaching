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

  string search_term;

  // This class just does a GET for a search term.
  cout << "Please enter a search term: ";
  getline(cin, search_term);

  // The get_projects_search function returns a vector of strings of project titles
  // Whatever search term you put in is searched on iSENSE and then the top 10 results are saved
  // to the vector.
  vector<string> project_titles = test.get_projects_search(search_term);

  // Print out all the titles in the vector.
  for(vector<string>::iterator it = project_titles.begin(); it != project_titles.end(); it++)
  {
    cout << "Name: " << *it << endl;
  }

  return 0;
}
