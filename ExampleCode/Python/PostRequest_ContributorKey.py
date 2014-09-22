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
r.raise_for_status() # Prints an error if something goes wrong.

#print r.json()
#print r.text

""" 
WORKING CODE BELOW, REJOICE.
"""
# Data stuff
print "Basic iSENSE JSON uploader using Contributor Keys\n";

contributor = raw_input("Enter a contributor key: ")
title = raw_input("Enter the title of the dataset: ")
data = raw_input("Enter a number: ")
choice = raw_input("Do you want to upload to iSENSE? (Y/N) -> ")

if choice == 'Y':
	print "\nUPLOADING TO iSENSE."

	# POST stuff.
	url = 'http://rsense-dev.cs.uml.edu/api/v1/projects/744/jsonDataUpload'

	payload = {
	    'contributor_key': [contributor],
	    'contributor_name': "python-test",
	    'title': title,
	    'data':
	    {
	    	'3398': [data]
	    }
	}

	headers = {'content-type': 'application/json'}

	r = requests.post(url, data=json.dumps(payload), headers=headers)

	# Detects status codes and tells the user what went right or wrong.
	if r.status_code == 200:
		print "\nUploaded fine, with a code of 200!"
	if r.status_code == 401:
		print "\nHmm, got an error code of 401."
		print "Try entering  the correct contributor key."
	if r.status_code == 422:
		print "\nGot an error code of 422."
		print "Try entering all the data fields correctly, with the right type for each field."
		print "IE a number must be a number, a string must be a series of characters,"
		print "Lat/Long should be GPS coordinates and a timestamp should be correctly formatted."


else:
	print "\nUSER CHOOSE NOT TO UPLOAD. \n"