This folder will contain the C++ Example Code.

Some of these examples use cURL through the libcurl library for c/c++.

You can get libcurl on Linux (Ubuntu/Debian) by running the following commands:

sudo apt-get install curl

sudo apt-get install libcurl4-gnutls-dev

sudo apt-get update

(I will include Windows instructions after I try compiling with Visual Studios Express.)


See this site for help:

http://curl.haxx.se/docs/httpscripting.html


NOTE:

When compiling with curl, be sure to include "-lcurl" at the end of the gcc/g++ command.

Example:

g++ GET_basic_curl.cpp -lcurl


Other  C++ libraries to try:

boost/asio

win socks / Microsoft's REST SDK for C++


Currently Working:

GET with libcurl

POST with libcurl

Future: DiceApp for C++.