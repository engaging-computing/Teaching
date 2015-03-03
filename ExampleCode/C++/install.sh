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

# See if a directory with the name "isense" exists.
DIRECTORY="isense"

cd ~/

if [ ! -d "$DIRECTORY" ]; then
  mkdir ~/isense
fi

cd ~/isense

# See if git is installed. If not, install it.
# if [ which git >/dev/dull; ]; then
#   echo "Git is installed."
# else
#   echo "Installing Git..."
#   sudo apt-get install git
# fi

# Clone the following repos:
# iSENSE API
# iSENSE Teaching
# Picojson
git clone https://github.com/isenseDev/iSENSE-API.git
git clone https://github.com/JasonD94/Teaching.git

mvdir /iSENSE-API/API ~/isense
rmdir iSENSE-API

wget https://raw.githubusercontent.com/kazuho/picojson/master/picojson.h
