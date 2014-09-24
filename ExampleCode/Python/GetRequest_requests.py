import requests, json

# Get a project ID from the user. Format the URL for a GET request.
project_id = raw_input("Enter a project ID for me to check: ")
URL = "http://rsense-dev.cs.uml.edu/api/v1/projects/%s" % project_id

#* GET Request
r = []
r = requests.get(URL)

status = r.status_code

# Check to see if the project ID that the user gave us is valid
if status == 200:
	print "GET worked. Code 200!"
	
	# Print out the project information.
	print r.json()['id']
	print r.json()['name']
	print r.json()['fields']
	print "URL: %s" % r.json()['url']


if status == 404:
	print "Couldn't find that project! You had entered %s for a project ID." % project_id

else:
	print "Got a code of: %d" % status
