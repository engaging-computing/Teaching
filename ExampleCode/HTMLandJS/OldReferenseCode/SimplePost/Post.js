function post() {
    
    var apiUrl = 'http://rsense-dev.cs.uml.edu/api/v1/projects/106/jsonDataUpload';
    var upload = {

        'title': 'YOUR NAME HERE',
        'contribution_key':'Key',
        'contributor_name':'YOUR NAME HERE',
        'data':
        {
            '4279': [5,2,9,10,222]
        }
    }
    $.post(apiUrl, upload);
    alert("Post Successful");
}