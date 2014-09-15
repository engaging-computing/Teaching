import requests, json

# Seems to be able to GET, at least gets a code 200 apparently.
r = []
r = requests.get("http://rsense-dev.cs.uml.edu/api/v1/projects")

print r

"""
	EXAMPLE JAVASCRIPT CODE.

	var upload = {
		'email': email,
		'password': password,
		'title': title,
		'data':
	  	{
	  		// 	Fill in the fields for your project here.
	  		// 	use the following URL to find this:
	  		//	http://isenseproject.org/api/v1/projects/PROJECT_ID/
	 	}
	}

"""

email = 'j@j.j'
password = 'j'
title = 'YOLO'

url = "http://rsense-dev.cs.uml.edu/api/v1/projects/744/jsonDataUpload"
payload = {
		'email': 'j@j.j',
		'password': 'j',
		'title': 'hey',
		'data':
	  	{
	  		'3398' : 5
	 	}
	}

r = requests.post(url, data=json.dumps(payload))
r.raise_for_status()