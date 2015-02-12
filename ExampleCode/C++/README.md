C++ Example Code.
=================

Some of these examples use cURL through the libcURL library for C.

You can get libcurl on Linux (Ubuntu/Debian) by running the following commands:

```
sudo apt-get install curl
sudo apt-get install libcurl4-gnutls-dev
sudo apt-get update
```

If those prerequisites are not installed, you may see the following error:

```
g++ -O0 -g -Wall -Wextra -pedantic-errors  -w -std=c++11 POST_simple.cpp -o simple.out -lcurl
POST_simple.cpp:1:65: fatal error: curl/curl.h: No such file or directory
#include <curl/curl.h>            
```

To compile in Windows, you will need to use Visual Studios Express 2013 (Professional / Community versions should also work).
See the "Windows" directory for more information. An example project is provided - however, you will need to change
the paths of the curl directory and the lib directory.

To download Visual Studios 2013, go to the following website: http://www.visualstudio.com/

MacOS users should have curl / libcurl installed by default.
You may however need to add "-lcurl" to the Other Linker Flags (OTHER_LDFLAGS) according to one stackoverflow post.
In the future MacOS will be tested and any other issues will be noted.


Confirmed working in Windows 7, 8.1 (x64) and Ubuntu 14.04LTS (x64)

Unconfirmed: MacOS X

NOTES:
-------------

When compiling with curl, be sure to include "-lcurl" at the end of the gcc/g++ command.

Example:

```
g++ GET_basic_curl.cpp -lcurl
```


For some of these programs, I use a JSON library called picojson to serialize and parse JSON. 
You can grab the code for that off the following github repo: https://github.com/kazuho/picojson
I have also included it in this GitHub Repository. 

The one header file you need can be found at: https://raw.githubusercontent.com/kazuho/picojson/master/picojson.h

You can also just git clone the repository using the following command:

```
git clone https://github.com/kazuho/picojson.git
```

Note that picojson is just one file, a .h that you will need to include when compiling.


Currently Working:
----------------------------

1. GET with libcurl
2. POST with libcurl


Needs to be redone using API:
DiceApp in C++ (2 dice rolls and 200 dice rolls)