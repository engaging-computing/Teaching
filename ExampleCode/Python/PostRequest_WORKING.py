import requests, json

"""
POST / GET REQUESTS
USES "REQUESTS"
http://docs.python-requests.org/en/latest/

More information here:
http://docs.python-requests.org/en/latest/user/quickstart/

The actual working code is based on the following URL:
http://docs.python-requests.org/en/latest/user/quickstart/#json-response-content

Specifically this piece of code, modified for iSENSE:
>>> import json
>>> url = 'https://api.github.com/some/endpoint'
>>> payload = {'some': 'data'}
>>> headers = {'content-type': 'application/json'}
>>> r = requests.post(url, data=json.dumps(payload), headers=headers)

FIELDs
http://rsense-dev.cs.uml.edu/api/v1/projects/744
"""

""" 
GET REQUEST
"""
# Seems to be able to GET, at least gets a code 200 apparently.
# Also able to print a ton of JSON.
r = []
r = requests.get("http://rsense-dev.cs.uml.edu/api/v1/projects")

#print r.json()
print r.text

""" 
WORKING CODE BELOW, REJOICE.
"""
# Data stuff
email = 'j@j.j'
password = 'j'
title = 'Hello World. WOO HOO'

# POST stuff.
url = 'http://rsense-dev.cs.uml.edu/api/v1/projects/744/jsonDataUpload'

payload = {
    'email': email,
    'password': password,
    'title': title,
    'data':
    {
    	'3398': [20]
    }
}

headers = {'content-type': 'application/json'}

r = requests.post(url, data=json.dumps(payload), headers=headers)
r.raise_for_status()
r.status_code