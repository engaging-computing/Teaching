#include <iostream>
// Using the following two
#include <cpprest/http_client.h>
#include <cpprest/json.h>                       // JSON library -> will want this.
#include <cpprest/filestream.h>

// These one's are apparently useful
#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/uri.h>                        // URI library
#include <cpprest/containerstream.h>            // Async streams backed by STL containers
#include <cpprest/interopstream.h>              // Bridges for integrating Async streams with STL and WinRT streams
#include <cpprest/rawptrstream.h>               // Async streams backed by raw pointer to memory
#include <cpprest/producerconsumerstream.h>     // Async streams for producer consumer scenarios


/*
	This one will use the C++ REST SDK
	
	https://casablanca.codeplex.com/wikipage?title=Http%20Client%20Tutorial

	When using Visual Studios, just go to:

	1) Tools -> NuGet Package Manager -> Manage NuGet Packages For Solutions
	2) From here, go to the search bar on the top right and type "C++ RESK SDK"
	3) The first result should be "C++ REST SDK". Click "Install".
	4) Now you just need to include the correct headings as well as any other stuff.
*/
/*
	TO DO:
	Figure out to get JSON and work with that in C++
	How to do a POST to iSENSE?


*/

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams


int main()
{
	/*
		GET REQUEST HERE
	*/

	auto fileStream = std::make_shared<ostream>();

	// Open stream to output file.
	pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
	{
		*fileStream = outFile;

		// Create http_client to send the request.
		http_client client(U("http://rsense-dev.cs.uml.edu/api/v1/projects/744"));

		// Build request URI and start the request.
		//uri_builder builder(U("/get"));
		//builder.append_query(U("q"), U("Casablanca CodePlex"));

		return client.request(methods::GET);
	})

	// Handle response headers arriving.
	.then([=](http_response response)
	{
		printf("Received response status code:%u\n", response.status_code());

		// Write response body into the file.
		return response.body().read_to_end(fileStream->streambuf());
	})

	// Close the file stream.
	.then([=](size_t)
	{
		return fileStream->close();
	});

	// Wait for all the outstanding I/O to complete and handle any exceptions
	try
	{
		requestTask.wait();
	}
	catch (const std::exception &e)
	{
		printf("Error exception:%s\n", e.what());
	}

	// WINDOWS ONLY, just to test.
	system("PAUSE");


	/*	POST REQUEST HERE	*/
	// https://casablanca.codeplex.com/discussions/470271
	// http_client client(U("http://rsense-dev.cs.uml.edu/api/v1/projects/744"));
	
	
	pplx::task<int> Post()
	{
		return pplx::create_task([]
		{
			json::value postData;
			postData[L"name"] = json::value::string(L"Joe Smith");
			postData[L"sport"] = json::value::string(L"Baseball");

			http_client client(L"http://localhost:5540/api/values");
			return client.request(methods::POST, L"",
				postData.to_string().c_str(), L"application/json");
		}).then([](http_response response)
		{
			if (response.status_code() == status_codes::OK)
			{
				auto body = response.extract_string();
				std::wcout << L"Added new Id: " << body.get().c_str() << std::endl;

				return std::stoi(body.get().c_str());
			}

			return 0;
		});
	}
	
	
	/*
	return client.request(methods::GET).then([](http_response response) -> pplx::task<json::value>
	{
		if (response.status_code() == status_codes::OK)
		{
			return response.extract_json();
		}

		// Handle error cases, for now return empty json value... 
		return pplx::task_from_result(json::value());
	})
		.then([](pplx::task<json::value> previousTask)
	{
		try
		{
			const json::value& v = previousTask.get();
			// Perform actions here to process the JSON value...
		}
		catch (const http_exception& e)
		{
			// Print error.
			wostringstream ss;
			ss << e.what() << endl;
			wcout << ss.str();
		}
	});
	*/

	return 0;
}