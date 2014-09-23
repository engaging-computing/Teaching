
import json
import urllib2
import requests

project = raw_input('Enter a project id: ')

title = raw_input('Enter a project title: ')

email = raw_input('Enter email: ')

password = raw_input('Enter password: ')

data = json.load(urllib2.urlopen('http://rsense-dev.cs.uml.edu/api/v1/projects/'+project))

# Data stuff
email = ''+ email
password = ''+password
title = ''+title

# POST stuff.
url = 'http://rsense-dev.cs.uml.edu/api/v1/projects/'+project+'/jsonDataUpload'

payload = {
    'email': email,
    'password': password,
    'title': title,
    'data':
    {
    	''+ str(data['fields'][0]['id']): [20]
    }
}

headers = {'content-type': 'application/json'}

r = requests.post(url, data=json.dumps(payload), headers=headers)
r.raise_for_status()
r.status_code