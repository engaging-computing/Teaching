#!/bin/bash
#*****************************************************************************
#  iSENSE C++ Class Install Script
#*****************************************************************************

printf "iSENSE C++ Class Install Script\n\n"
printf "This script pulls all required dependencies of the iSENSE C++ Class\n"
printf "The script will do the following:\n"
printf "  Creates a directory in your home folder (~/) called \"isense\"\n"
printf "  Installs git, curl, libcurl (if not already installed)\n"
printf "  Pulls down iSENSE class / includes\n"
printf "  Pulls down iSENSE examples / example apps\n"
printf "  Pulls down picojson - 3rd party JSON library that the class depends on\n\n"
printf "This script should only be run once, as when this script is finished, look for\n"
printf "a directory named \"isense\" in your home directory (~/isense)\n"
printf "You may, however, run it again to update the API code should any changes\n"
printf "be made to the C++ API\n\n"

# See if a directory with the name "isense" exists.
DIRECTORY="isense"
cd ~/

if [ ! -d "$DIRECTORY" ]; then
  printf "Creating a directory in your home directory called \"isense\"\n"
  printf "Please look at ~/isense/ for the API files + Example Code.\n\n"
  mkdir ~/isense
fi

# Don't do the following if the user is running Mac OS
# Users should be using Debian based systems with apt-get working
# Plus they need sudo access - a VM or personal computer.
if [[ "$OSTYPE" != "darwin"* ]]; then
  printf "This script requires git, and the iSENSE API requires curl & libcurl\n"
  printf "Please install these packages:\n"
  printf "git curl libcurl4-gnutls-dev\n"
  printf "Enter your password at the prompt to install them.\n\n"

  # If these are already installed, nothing happens. Just "already newest version" comments.
  sudo apt-get install git curl libcurl4-gnutls-dev
fi

# Detect Mac OS users - tell them to use the XCode Command Line Tools,
# and don't try apt-get install git
# Also Mac users have curl + libcurl installed already from Apple.
if [[ "$OSTYPE" == "darwin"* ]]; then
  printf "It looks like you are using some version of OS X.\n"
  printf "Please install git using the XCode Command Line Tools.\n"
  printf "See the following website for an example: \n"
  printf "http://burnedpixel.com/blog/setting-up-git-and-github-on-your-mac/"
fi

# Clone the following repos:
# iSENSE API
# iSENSE Teaching
# Picojson
printf "\n"
git clone https://github.com/isenseDev/iSENSE-API.git ~/isense/iSENSE-API
printf "\n"
git clone https://github.com/JasonD94/Teaching.git ~/isense/Teaching
printf "\n"
git clone https://github.com/kazuho/picojson.git ~/isense/picojson

# Move the C++ code / Picojson header file to the right directory
mv ~/isense/iSENSE-API/C++/API/ ~/isense/
mv ~/isense/picojson/picojson.h ~/isense/API/include

# Move the Example code / Example apps to a higher directory
mv ~/isense/Teaching/ExampleCode/C++/API-Examples/ ~/isense/
mv ~/isense/Teaching/ExampleCode/C++/Apps/ ~/isense/

# Remove the extra directories that are no longer needed.
rm -rf ~/isense/iSENSE-API
rm -rf ~/isense/picojson
rm -rf ~/isense/Teaching

# Let the user know we're done.
printf "\niSENSE C++ Install Script is finished.\n"
printf "Please look for the C++ API in ~/isense/\n"
printf "The API files are in ~/isense/API, examples of using the API are in API-Examples and \n"
printf "two example apps are in the Apps folder.\n"
printf "See the READMEs at https://github.com/isenseDev/Teaching for help.\n"
