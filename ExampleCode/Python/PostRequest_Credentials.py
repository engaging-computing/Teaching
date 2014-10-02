import requests, json, getpass

# Requests will probably need to be installed.
# Try pip install requests
# (Which requires Python 2.7 and pip)
# getpass hides the password entry for security.

print "Basic iSENSE JSON uploader using email/password\n";

email = raw_input("Enter an email: ")
password = getpass.getpass("Enter your password: ")     # These chars are hidden from the user.
title = raw_input("Enter the title of the dataset: ")
data = raw_input("Enter a number: ")
choice = raw_input("Do you want to upload to iSENSE? (Y/N) -> ")

# Do a GET request to see if the user entered the correct email/password.
r = requests.get("http://rsense-dev.cs.uml.edu/api/v1/users/myInfo?email="+email+'&password='+password)

# See if the user's email/password is valid. Loop until they enter the correct credentials.
while r.status_code != 200:
    print"\n\n**************************************************************************"
    print "\tThe email and/or password you entered was incorrect."
    print"**************************************************************************\n"
    email = raw_input("Enter an email: ")
    password = getpass.getpass("Enter your password: ")     # These chars are hidden from the user.

    r = requests.get("http://rsense-dev.cs.uml.edu/api/v1/users/myInfo?email="+email+'&password='+password)

# User typed "N" or some other random character. So they didn't want to POST.
if choice == 'N':
    print "\nUSER CHOOSE NOT TO UPLOAD. \n"

# Yes branch, tries to POST to iSENSE
print "\nUPLOADING TO iSENSE."

# POST stuff.
POST_URL = 'http://rsense-dev.cs.uml.edu/api/v1/projects/744/jsonDataUpload'

payload = {
    'email': email,
    'password': password,
    'title': title,
    'data':
    {
        '3398': [data]
    }
}

# This is needed, otherwise I got code 422s and the data wasn't showing up right in the log.
headers = {'content-type': 'application/json'}

r = requests.post(POST_URL, data=json.dumps(payload), headers=headers)

# Detects status codes and tells the user what went right or wrong.
if r.status_code == 200:
    print "\nUpload completed successfully!"
if r.status_code == 401:
    print "\nError code: 401."
    print "Try entering  the correct email and password combination."
if r.status_code == 422:
    print "\nError code: 422."
    print "Try entering all the data fields correctly, with the right type for each field."
    print "Examples: "
    print "Numbers must be numbers: 1, 2, 5.555435, etc"
    print "Strings must be a series of characters: \'hello world\', \'this is a string\', etc."
    print "Latitude and Longitude must be degrees:  42.65 -71.32, 33.83 -118,  etc."
    print "Timestamps must be in the form \"yyyy/MM/dd hh:mm:ss\" or as a UNIX timestamp."
    print "\n\nTry rerunning this program, making sure to follow the above format restrictions."
