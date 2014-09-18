import requests, json

"""

POST / GET REQUESTS
USES "REQUESTS"
http://docs.python-requests.org/en/latest/

http://docs.python-requests.org/en/latest/user/quickstart/

FIELDs
http://rsense-dev.cs.uml.edu/api/v1/projects/744

"""

# Seems to be able to GET, at least gets a code 200 apparently.
# Also able to print a ton of JSON.
r = []
r = requests.get("http://rsense-dev.cs.uml.edu/api/v1/projects")

#print r.json()
print r.text

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

# Data stuff
email = 'j@j.j'
password = 'j'
title = 'Hello World.'

# POST stuff.
url = 'http://rsense-dev.cs.uml.edu/api/v1/projects/744/jsonDataUpload'

payload = {
    'email': email,
    'password': password,
    'title': title,
    'data':
    {
    	'3398': [5]
    }
}

headers = {'content-type': 'application/json'}

r = requests.post(url, data=json.dumps(payload), headers=headers)
r.raise_for_status()
r.status_code