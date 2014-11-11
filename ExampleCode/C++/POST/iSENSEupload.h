#include <iostream>

using namespace std;

/*
    At some point this will hold all the upload related stuff for iSENSE uploading in C++
    Probably functions like:

    - Upload with Contributor key
    - Upload with username / password
    - GET JSON of a project given project ID
    - GET Project Fields given project ID
    - POST JSON dataset.
    - POST JSON appending to a dataset

*/

class iSENSE_Upload
{
public:
    iSENSE_Upload();        // Default constructor

    GET_PROJ_INFO();
    GET_PROJ_FIELDS();
    POST_JSON_KEY();

private:
    char* URL;
    char* Data;
    int project_ID;


}