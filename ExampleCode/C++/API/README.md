API Source
==========
API source code for iSENSE related projects in C++.

You will need to make a project in either Visual Studios / Xcode or some other IDE,
or use Linux and the included makefile as well as a text editor.

Required to use the API in a program:

1. API.cpp -> This file contains the class function definitions. Look through it and read the
comments to understand what they do and how they can be used.

2. a main file -> You can check out some of the example mains (GET_search.cpp, POST_email.cpp, etc)
so that you can make your own program that uses the API.

3. an include directory -> This should contain API.h, memfile.h and picojson.h. memfile.h and
picojson.h are used along with libcurl to make HTTP requests GETing / POSTing JSON to iSENSE's
RESTFUL API. I only suggest looking through API.h for the iSENSE class declaration.

Also see the notes in the C++ directory's README and look through the Projects directory
for example projects in Visual Studios and Xcode.