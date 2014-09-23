
import json
import urllib2
import requests


choice = raw_input('Email upoload or contributor key [1/2]')

project = raw_input('Enter a project id: ')




data = json.load(urllib2.urlopen('http://rsense-dev.cs.uml.edu/api/v1/projects/'+project))

# Data stuff
email = ''+ email
password = ''+password
title = ''+title

# POST stuff.

if(choice == 1)
{
	title = raw_input('Enter a project title: ')

	email = raw_input('Enter email: ')

	password = raw_input('Enter password: ')


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
}
else
{
	contributor_key = raw_input('Enter contributor key: ')

	url = 'http://rsense-dev.cs.uml.edu/api/v1/projects/744/jsonDataUpload'

	payload = {
		'title': title,						# Note, spent forever trying to figure this out.
	    'contribution_key': contributor_key,	# But it's contribution_key - not contributor_key
	    'contributor_name': "python",	
	    'data':
	    {
	    	''+ str(data['fields'][0]['id']): [25]
	    }
	}
}