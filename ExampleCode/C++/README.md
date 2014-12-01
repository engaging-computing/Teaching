C++ Example Code.
=================

Some of these examples use cURL through the libcurl library for C/C++.

You can get libcurl on Linux (Ubuntu/Debian) by running the following commands:

```
sudo apt-get install curl
sudo apt-get install libcurl4-gnutls-dev
sudo apt-get update
```

(I will include Windows instructions after I try compiling with Visual Studios Express.)

See this site for help:
[curl website](http://curl.haxx.se/docs/httpscripting.html)


NOTES:
-------------

When compiling with curl, be sure to include "-lcurl" at the end of the gcc/g++ command.

Example:
```
g++ GET_basic_curl.cpp -lcurl
```

Other  C++ libraries to try:

1. boost/asio
2. win socks / Microsoft's REST SDK for C++


For some of these programs, I use a JSON library called parson to serialize and parce JSON. 
You can grab the code for that off the following github repo: https://github.com/kgabis/parson

You can also just git clone the repo using the following command:

```
git clone https://github.com/kgabis/parson.git
```

Note that parson is just two files, a .c and a .h that you will need to include when compiling.


Currently Working:
----------------------------

1. GET with libcurl
2. POST with libcurl
3. DiceApp in C++ (2 dice rolls and 200 dice rolls)