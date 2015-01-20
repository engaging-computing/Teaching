C++ Example Code
================

It is recommended that you compile any projects using the iSENSE C++ code in a Unix like system,
either Linux or Mac OS.

The code does work in Visual Studios but it is not trivial to set up.

Setup
------
Some of these examples use cURL through the libcURL library for C.

Linux
-----
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

When compiling with curl, be sure to include "-lcurl" at the end of the gcc/g++ command.

Example:

```
g++ GET_basic_curl.cpp -lcurl
```

Windows
-------
To compile in Windows, you will need to use Visual Studios Express 2013 (Professional / Community versions should also work).
See the "Windows" directory for more information. An example project is provided - however, you will need to change
the paths of the curl directory and the lib directory.

To download Visual Studios 2013, [go to the following website.](http://www.visualstudio.com/)

MacOS
-----
MacOS users should have curl / libcurl installed by default.
You will however need to add "-lcurl" to the Other Linker Flags.
This can be found by going to build settings within an Xcode project, and then clicking on "All"
and scrolling down until you see an option for Other Linker Flags. Here you can type "-lcurl" and
add the API files (api.cpp as well as the "include" directory) to the Xcode project.

For more help with Xcode, [see the following site.](http://docs.millennialmedia.com/iOS-SDK/iOSAddingLinkerFlag.html)

You can also check out the example project in the "Mac" directory in the Github repo.

You should also be able to use the provided Makefile for Linux.

Confirmed working in Windows 7, 8.1 (x64), Mac OS X 10.10.1 Yosemite and Ubuntu 14.04LTS (x64)


NOTES:
------
For some of these programs, I use a JSON library called picojson to serialize and parse JSON.
[You can grab the code for that off the following github repo.](https://github.com/kazuho/picojson)

I have also included it in this GitHub Repository, inside the Projects directory in a
zip called "include.zip". Unzip that zip and you will have picojson,
as well as memfile.h and API.h.

You will likely want to check this repo for updates to API.h / API.cpp, as those files contain
the iSENSE class that provides API wrappers for using iSENSE APIs in C++.

[The one header file you need can be found here.](https://raw.githubusercontent.com/kazuho/picojson/master/picojson.h)

You can also just git clone the repository using the following command:

```
git clone https://github.com/kazuho/picojson.git
```

Note that picojson is just one file, a .h that you will need to include when compiling.