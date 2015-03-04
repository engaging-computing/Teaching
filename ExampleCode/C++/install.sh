#!/bin/bash
#*****************************************************************************
#  iSENSE C++ Class Install Script
#*****************************************************************************

echo "iSENSE C++ Class Install Script"
echo "This script pulls all required dependencies of the iSENSE C++ Class"
echo "Included are:"
echo  "- Pulls down iSENSE class / includes"
echo  "- Pulls down iSENSE examples / example apps"
echo  "- Pulls down picojson - 3rd party JSON library that the class depends on"
echo  "- Installs curl, libcurl"
echo "Please only run this script once. When this script is finished, look for"
echo "a directory named \"isense\" in your home directory (~/isense)"
printf "\n"

# See if a directory with the name "isense" exists.
DIRECTORY="isense"

cd ~/

if [ ! -d "$DIRECTORY" ]; then
  printf "Creating a directory in your home directory called \"isense\"\n"
  printf "Please look at ~/isense/ for the API files + Example Code.\n\n"
  mkdir ~/isense
fi

cd ~/isense

# Install git, curl, libcurl.
# If these are already installed, nothing happens. The following should print out to the user:
# 0 upgraded, 0 newly installed, 0 to remove and 0 not upgraded.
printf "This script requires git, and the iSENSE API requires curl & libcurl\n"
printf "Please install these packages:\n"
printf "git curl libcurl4-gnutls-dev\n"
printf "Enter your password at the prompt to install them.\n\n"
sudo apt-get install git curl libcurl4-gnutls-dev
# sudo apt-get update

# Clone the following repos:
# iSENSE API
# iSENSE Teaching
# Picojson
printf "\n"
git clone https://github.com/isenseDev/iSENSE-API.git
printf "\n"
git clone https://github.com/JasonD94/Teaching.git
printf "\n"
git clone https://github.com/kazuho/picojson.git

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
