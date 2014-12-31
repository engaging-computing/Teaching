C++ Example Code.
=================

Some of these examples use libcURL through the libcurl library for C/C++.

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
 #include <curl/curl.h>             // cURL to make HTTP requests
```

To compile in Windows, you will need to use Visual Studios Express 2013 (Professional version will work as well).
See the "Windows" directory for more information. An example project will be created in the future.

See this site for help:
[curl website](http://curl.haxx.se/docs/httpscripting.html)


NOTES:
-------------

When compiling with curl, be sure to include "-lcurl" at the end of the gcc/g++ command.

Example:

```
g++ GET_basic_curl.cpp -lcurl
```


For some of these programs, I use a JSON library called picojson to serialize and parce JSON. 
You can grab the code for that off the following github repo: https://github.com/kazuho/picojson

The one header file you need can be found at: https://raw.githubusercontent.com/kazuho/picojson/master/picojson.h

You can also just git clone the repo using the following command:

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