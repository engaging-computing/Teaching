#include <iostream>                   // std::cout, std::cin
#include <string>                     // std::string, std::to_string;
#include <random>                     // random number generators
#include "include/API.h"              // API class

// Main, calls upload function. Uses picojson for JSON serialization / parsing.
int main ()
{
  // Example of using the iSENSE class
  iSENSE Dice;

  // Get user input
  std::string title, ID, key, letters, num, timestamp;

  std::cout << "Dice Roll App\n";

  // Get user input.
  std::cout << "Please set the project ID for this dataset: ";     // Sets project ID
  getline(std::cin, ID);

  std::cout << "Please set a contributor key for this project: ";  // Set contributor key
  getline(std::cin, key);

  cout << "Please enter a title for the dataset: ";           // Gets the title
  getline(std::cin, title);

  /*  Add a timestamp to the title to avoid duplicates
   *        and to make it clear when the dataset was uploaded.   */
  timestamp = Dice.generate_timestamp();
  title = title + " "  + timestamp;

  // Add project info / dataset info to the object
  Dice.set_project_ID(ID);
  Dice.set_project_title(title);
  Dice.set_project_label("DiceApp");
  Dice.set_contributor_key(key);

  // Note: can also call set_project_all(ID, title, label, key) like this:
  Dice.set_project_all(ID, title, "DiceApp", key);

  // Create & Seed the random generator
  std::default_random_engine random_generator((unsigned int)time(0));
  std::uniform_int_distribution<int> dice_rolls(1, 6);

  int roll;     // int for the dice rolls

  // Example of pushing numbers back into the object.
  for(int i = 0; i < 200; i++)
  {
    // Generate a random number using rand()
    roll = dice_rolls(random_generator);

    // Make sure to use "to_string" to convert an int/double/float/etc to a string.
    Dice.push_back("Red Die", to_string(roll));

    // Now do the blue die as well
    roll = dice_rolls(random_generator);
    Dice.push_back("White Die", to_string(roll));
  }

  // Try grabbing fields. Error checking occurs below.
  Dice.get_project_fields();

  // Try formatting the upload data string without uploading yet.
  Dice.format_upload_string(true);

  // Check the fields for errors (manually compare against iSENSE)
  Dice.debug();

  char ans;

  do{
    std::cout << "Does the data look alright to you? (enter y/n) -> ";
    std::cin >> ans;
  }while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');

  if(ans == 'n' || ans == 'N')
  {
    std::cout << "\nUser chose not to upload. Quitting instead.\n";
    return 0;
  }

  cout << "\nUploading to rSENSE.\n";
  Dice.post_json_key();

  // In the future we should tell the user if this upload function was a success. Or if it failed then why.
  return 0;
}
