// POCO requests these headers. For HTTP requests.
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>

#include <iostream>
#include <string>

using namespace Poco::Net;
using namespace Poco;
using namespace std;

int main()
{
	string email, password, title, URL;

	cout<<"iSENSE GET Request Test \n";

	URL = "http://rsense-dev.cs.uml.edu/api/v1/projects/821";

	// Preparing the session.
	URI uri(URL);
	HTTPClientSession session(uri.getHost(), uri.getPort());

	// Prepare the path.
    string path(uri.getPathAndQuery());
    if (path.empty()) path = "/";

    // Send Request
    HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
    session.sendRequest(req);

    // Get Response
    HTTPResponse res;
    cout<<res.getStatus()<<" "<<res.getReason()<<endl;

    // Print Response
    istream &is = session.receiveResponse(res);
    StreamCopier::copyStream(is, cout);

	return 0;
}