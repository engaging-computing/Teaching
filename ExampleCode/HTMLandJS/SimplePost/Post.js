//This script is hard coded for project 556. To change project you must change the 556 in the url and add the appropriate field numbers.
function submitter()
{
    var API_URL = 'http://isenseproject.org/api/v1/projects/556/jsonDataUpload';
    var formData = [];
    var upload = {
        'email': 'j@j.j',
        'password': 'j',
        'title': 'TEST',
        'data':
        {
            '2685': [5],
            '2640': [4],
            '2641': [4],
            '2642': [7],
            '2643': [8]
        }
    }
        $.post(API_URL, upload);
}