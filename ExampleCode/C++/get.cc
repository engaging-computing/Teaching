// POCO requests these headers. For HTTP requests.
// #include <Poco/Net/HTTPClientSession.h>
// #include <Poco/Net/HTTPRequest.h>
// #include <Poco/Net/HTTPResponse.h>
// #include <Poco/StreamCopier.h>
// #include <Poco/Path.h>
// #include <Poco/URI.h>
// #include <Poco/Exception.h>

// curlpp uses these libraries below.
// #include <curlpp/cURLpp.hpp>
// #include <curlpp/Easy.hpp>
// #include <curlpp/Options.hpp>

// This is for librcurl
#include <curl/curl.h>

#include <iostream>
#include <string>


/*

Tried Poco, didn't seem to work.

Going to try curlpp.

Requires going to:
https://code.google.com/p/curlpp/

Need to download it and install the following
package from the Ubuntu repos:
libcurl4-openssl-dev

I'm pretty sure I needed this too:
sudo apt-get install libboost-all-dev

For curpp, just download the tar, unpack it
using archive manager and then type:
./configure
make
sudo make install

Poco also requires the same steps to install.

*/


// using namespace Poco::Net;
// using namespace Poco;
using namespace std;

int main()
{
	string email, password, title, URL;

	cout<<"iSENSE GET Request Test \n";

	URL = "http://rsense-dev.cs.uml.edu/api/v1/projects/821";

	
	

	// Wikipedia test

	// // RAII cleanup
	// curlpp::Cleanup myCleanup;

	// // standard request object.
	// curlpp::Easy myRequest;

	// // Set the URL.
	// myRequest.setOpt(new curlpp::options::Url(std::string("http://www.wikipedia.com")));

	// // Send request and get a result.
	// // By default the result goes to standard output.
	// // Here I use a shortcut to get it in a string stream ...
	// ostringstream os;
	// os << myRequest.perform();

	// string asAskedInQuestion = os.str();

// 	Below this point uses "Poco", but it kept returning an exit status of 1.

	// // Preparing the session.
	// URI uri(URL);
	// HTTPClientSession session(uri.getHost(), uri.getPort());

	// // Prepare the path.
 //    string path(uri.getPathAndQuery());
 //    if (path.empty()) path = "/";

 //    // Send Request
 //    HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
 //    session.sendRequest(req);

 //    // Get Response
 //    HTTPResponse res;
 //    cout<<res.getStatus()<<" "<<res.getReason()<<endl;

 //    // Print Response
 //    istream &is = session.receiveResponse(res);
 //    StreamCopier::copyStream(is, cout);

	return 0;
}