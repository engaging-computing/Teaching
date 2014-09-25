import json
import urllib2
import requests,sys

choice = raw_input('Email upoload or contributor key [1/2] ')

while choice != '1' and choice != '2':
    print "Not a valid input"
    choice = raw_input('Email upoload or contributor key [1/2] ')

if choice == '1':
    project = raw_input('Enter a project id: ')
    data = json.load(urllib2.urlopen('http://rsense-dev.cs.uml.edu/api/v1/projects/'+project))
    title = raw_input('Enter a project title: ')
    email = raw_input('Enter email: ')
    password = raw_input('Enter password: ')
    number = raw_input('Enter a number to be uploaded: ')
    url = 'http://rsense-dev.cs.uml.edu/api/v1/projects/'+project+'/jsonDataUpload'

    payload = {
        'email': email,
        'password': password,
        'title': title,
        'data':
        {
            ''+ str(data['fields'][0]['id']): [number]
        }
    }

    headers = {'content-type': 'application/json'}
    r = requests.post(url, data=json.dumps(payload), headers=headers)

    print "\nUPLOADING TO iSENSE."

    if r.status_code == 200:
        print "\nUploaded fine, with a code of 200!"

    if r.status_code == 401:
        print "\nHmm, got an error code of 401."
        print "Try entering  the correct contributor key."

    if r.status_code == 422:
        print "\nGot an error code of 422."
        print "Try entering all the data fields correctly, with the right type for each field."
        print "Examples: A number must be a number, a string must be a series of characters,"
        print "Lat/Long should be GPS coordinates and a timestamp should be correctly formatted."

elif choice == '2':
    project = raw_input('Enter a project id: ')
    contributor_name = raw_input("Enter a contibutor name")
    contributor = raw_input("Enter a contributor key: ")
    title = raw_input("Enter the title of the dataset: ")
    number = raw_input("Enter a number: ")
    data = json.load(urllib2.urlopen('http://rsense-dev.cs.uml.edu/api/v1/projects/'+project))

    print "\nUPLOADING TO iSENSE."

    # POST stuff.
    url = 'http://rsense-dev.cs.uml.edu/api/v1/projects/683/jsonDataUpload'
    payload = {
        'title': title,                     # Note, spent forever trying to figure this out.
        'contribution_key': contributor,    # But it's contribution_key - not contributor_key
        'contributor_name': contributor_name,   
        'data':
        {
            ''+ str(data['fields'][0]['id']): [number]
        }
    }

    # This is needed, otherwise I got code 422s and the data wasn't showing up right in the log.
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
        print "Examples: A number must be a number, a string must be a series of characters,"
        print "Lat/Long should be GPS coordinates and a timestamp should be correctly formatted."