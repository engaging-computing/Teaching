import requests, json, sys, random

# Requests will probably need to be installed.
# Try pip install requests
# (Which requires Python 2.7 and pip)

print "Basic iSENSE JSON uploader using Contributor Keys\n";

title = raw_input("Enter the title of the dataset: ")
choice = raw_input("Do you want to upload to iSENSE? (Y/N) -> ")

# User typed "N" or some other random character. So they didn't want to POST.
if choice == 'N' or choice == 'n':
    print "\nUSER CHOOSE NOT TO UPLOAD. \n"
    sys.exit(0)     # Exit this script, the user is done.

# User wants to upload to iSENSE.
print "\nUPLOADING TO iSENSE."

# POST stuff.
url = 'http://rsense-dev.cs.uml.edu/api/v1/projects/911/jsonDataUpload'

# Random number stuff here.
random.seed();                # Seed the random function with the system time.

# Define these so the below loop works
red_dice = []
white_dice = []

# Generate random numbers between 1 and 6 here.
for i in range(0, 99):
    red_dice.append(random.randint(1, 6))
    white_dice.append(random.randint(1, 6))
    print "%d %d" %red_dice[i], %white_die[i]


payload = {
    'title': title,                                             # Note, spent forever trying to figure this out.
    'contribution_key':  "123",                     # But it's contribution_key - not contributor_key
    'contributor_name': "python",
    'data':
    {
        '4160': [json.loads(red_die)],
        '4161': [json.loads(white_die)]
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
