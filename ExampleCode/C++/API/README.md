API Source
==========
API source code for iSENSE related projects in C++.

You will need to make a project in either Visual Studios / Xcode or some other IDE,
or use Linux and the included makefile as well as a text editor.

Required to use the API in a program:

1. API.cpp -> This file contains the class function definitions. Look through it and read the
comments to understand what they do and how they can be used.

2. A main file -> You can check out some of the example mains (GET_search.cpp, POST_email.cpp, etc)
so that you can make your own program that uses the API.

3. An include directory -> This should contain API.h, memfile.h and ** picojson.h. ** memfile.h and
picojson.h are used along with libcurl to make HTTP requests GETing / POSTing JSON to iSENSE's
RESTFUL API. I only suggest looking through API.h for the iSENSE class declaration.

Note: picojson.h is not in this github repo. You should either 
[download the include.zip here](https://github.com/JasonD94/Teaching/blob/jd_data_sets/ExampleCode/C%2B%2B/Projects/include.zip)
here by clicking on Raw, then unzip it and copy the picojson.h file into your code directory,
or 
[go to the following link](https://raw.githubusercontent.com/kazuho/picojson/master/picojson.h)
to find a recent copy of picojson. Right click and save the file as a header file inside your
code directory.

4. A makefile - one is provided for testing. Simply add on to it to compile your program.

Also see the notes in the C++ directory's README and look through the Projects directory
for example projects in Visual Studios and Xcode.