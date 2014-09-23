import requests, json

# Requests will probably need to be installed.
# Try pip install requests
# (Which requires Python 2.7 and pip)

# Currently this code is not working.
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