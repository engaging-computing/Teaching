function post() {
    
    var url = 'http://rsense-dev.cs.uml.edu/api/v1/projects/106/jsonDataUpload';
    var upload = {

        'title': 'YOUR NAME HERE',
        'contribution_key':'Key',
        'contributor_name':'YOUR NAME HERE',
        'data':
        {
            '4279': [5]
        }
    }
    $.post(url, upload);
    alert("Post Successful");
}