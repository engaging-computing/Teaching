function post()
{
    var API_URL = 'http://rsense-dev.cs.uml.edu/api/v1/projects/106/jsonDataUpload';
    var formData = [];
    var upload = {

        'title': 'TEST',
	    "contribution_key":"Key",
	    "contributor_name":"Tyler",
        'data':
        {
            '4279': [5]
        }
    }
        $.post(API_URL, upload);
}