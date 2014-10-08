#include <iostream>
#include <curl/curl.h>      //CURL to make HTTP requests
#include <stdio.h>

using namespace std;

int main()
{
    /*
        C++ libraries to try
        boost.asio
        curl
        win socks /
    */

        /*
            How to get CURL working on Ubuntu 14.04LTS

            sudo apt-get install curl
            sudo apt-get update

            (this one is for NON SSL requests. iSENSE doesn't use SSL, so this should be fine.)
            sudo apt-get install libcurl4-gnutls-dev

            (This one is for SSL requests. I have it installed as well, until I realized I didn't need it. Left it here for future reference)
            sudo apt-get install libcurl4-openssl-dev

            See this site for help:
            http://curl.haxx.se/docs/httpscripting.html

            WHEN COMPILING A WITH CURL, MAKE SURE TO INCLUDE "-lcurl" at the end of the gcc/g++ command.
            Example:
            g++ GET_basic.cpp -lcurl


            Also: wow, the following actual works! It grabs the project page for project #744 and displays it to the terminal!
            And the following is straight off of the cURL webpage. See:
            http://curl.haxx.se/libcurl/c/example.html
        */

    // This project will try using CURL to make a basic GET request to rSENSE
        CURL *curl;
        CURLcode res;

        curl = curl_easy_init();

        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "http://rsense-dev.cs.uml.edu/api/v1/projects/744");

            /* example.com is redirected, so we tell libcurl to follow redirection */
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    cout<<"\n\n";

    return 0;
}