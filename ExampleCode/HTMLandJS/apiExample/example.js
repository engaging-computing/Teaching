function run() {

//	/api/v1/projects/XX

    var urlProject = 'http://isenseproject.org/api/v1/projects/835';
    var responseProject = $.ajax({ type: "GET",
                        url: urlProject,
                        async: false,
                        dataType: "JSON"
    }).responseText;

    var parsedResponseProject = JSON.parse(responseProject); 

    console.log(parsedResponseProject);

//	/api/v1/projects

    var urlProject = 'http://isenseproject.org/api/v1/projects';
    var responseProject = $.ajax({ type: "GET",
                        url: urlProject,
                        async: false,
                        dataType: "JSON"
    }).responseText;

    var parsedResponseProject = JSON.parse(responseProject); 

    console.log(parsedResponseProject);

//	/api/v1/projects

    var apiUrl = 'http://isenseproject.org/api/v1/projects';

    var upload = {

        'email': 't@t.t',
        'password': 't',
        'project_name': 'TEST123456',
    }
    $.post(apiUrl, upload);

//	/api/v1/projects/XX/add_key

    var apiUrl = 'http://isenseproject.org/api/v1/projects/835/add_key';

    var upload = {

        'email': 't@t.t',
        'password': 't',
        'contrib_key': {'name' : 'key',
        				'project_id' : 835,
        				'key' : 'key'
        			   }
    }
    $.post(apiUrl, upload);

//	/api/v1/fields

    var apiUrl = 'http://isenseproject.org/api/v1/fields';

    var upload = {

        'email': 't@t.t',
        'password': 't',
        'field' : {'project_id' : 835,
        		   'field_type' : 1,
        		   'name' : 'TEST3',
        		   'unit' : 'degrees',
        		   'restrictions': 'test'
        		  }
    }
    $.post(apiUrl, upload);

//	/api/v1/fields/XX

    var urlProject = 'http://isenseproject.org/api/v1/fields/4169';
    var responseProject = $.ajax({ type: "GET",
                        url: urlProject,
                        async: false,
                        dataType: "JSON"
    }).responseText;

    var parsedResponseProject = JSON.parse(responseProject); 


    console.log(parsedResponseProject);

//	/api/v1/projects/XX/jsonDataUpload

    var apiUrl = 'http://isenseproject.org/api/v1/projects/835/jsonDataUpload';

    var upload = {

        'email': 't@t.t',
        'password': 't',
        'title' : 'TEST123',
        'data' : {
        		   '4162' : [1,2,3]
        		 }
    }
    $.post(apiUrl, upload);

//	/api/v1/projects/XX/jsonDataUpload

    var apiUrl = 'http://isenseproject.org/api/v1/projects/835/jsonDataUpload';

    var upload = {

        'title' : 'TEST1234',
        'contribution_key': 'key',
        'contributor_name': 'Tyler',
        'data' : {
        		   '4162' : [1,2,3]
        		 }
    }
    $.post(apiUrl, upload);

//	/api/v1/data_sets/XX/edit

    var apiUrl = 'http://isenseproject.org/api/v1/data_sets/7583/edit';

    var upload = {

        'email' : 't@t.t',
        'password': 't',
        'data' : {
        		   '4162' : [1,5,6]
        		 }
    }
    $.get(apiUrl, upload);

//	/api/v1/data_sets/XX/edit

    var apiUrl = 'http://isenseproject.org/api/v1/data_sets/7584/edit';

    var upload = {

        'contribution_key' : 'key',
        'data' : {
        		   '4162' : [1,2,3,4]
        		 }
    }
    $.get(apiUrl, upload);

//	/api/v1/data_sets/append

    var apiUrl = 'http://isenseproject.org/api/v1/data_sets/append';

    var upload = {

        'email' : 't@t.t',
        'password' : 't',
        'id' : 7584,
        'data' : {
        		   '4162' : [4,5,6]
        		 }
    }
    $.post(apiUrl, upload);

//	/api/v1/data_sets/append

    var apiUrl = 'http://isenseproject.org/api/v1/data_sets/append';

    var upload = {


        'contribution_key' : 'key',
        'id' : 7584,
        'data' : {
        		   '4162' : [4,5,6]
        		 }
    }
    $.post(apiUrl, upload);

	//DONT KNOW HOW TO DO MEDIA OBJECTS
	//DONT KNOW HOW TO DO MEDIA OBJECTS

//	/api/v1/users/myInfo

    var urlProject = 'http://isenseproject.org/api/v1/users/myInfo';
    var responseProject = $.ajax({ type: "GET",
                        url: urlProject,
                        data : {'email' : 't@t.t', 'password' : 't'},
                        async: false,
                        dataType: "JSON"
    }).responseText;

    var parsedResponseProject = JSON.parse(responseProject); 

    console.log(parsedResponseProject);
}
