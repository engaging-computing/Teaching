"use strict";
function submitter(){

    var apiUrl = 'http://isenseproject.org/api/v1/projects/556/jsonDataUpload';
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
        $.post(apiUrl, upload);
}