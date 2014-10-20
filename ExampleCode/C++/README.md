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


Currently Working:
----------------------------

1. GET with libcurl
2. POST with libcurl
3. DiceApp in C++