"""
        This script will be a test of getting a project's fields
"""
import requests, json

# Pass a structure to this function to get a TRUE/FALSE response on
# whether a structure is empty or not.
def is_empty(struct):
    if struct:
        return False
    else:
        return True

# Run til the user quits. Otherwise this just loops over and over again.
while True:
    print "***************************"
    print "*  GET FIELDS Script    *"
    print "***************************"

     # Get a project ID from the user. Format the URL for a GET request.
    project_ID = raw_input("Enter a project ID: ")
    print "\n"

    # GET Request:      /api/v1/projects/XX     (XX = PROJECT ID)
    URL = "http://rsense-dev.cs.uml.edu/api/v1/projects/%s" % project_ID
    r = []
    r = requests.get(URL)
    status = r.status_code          # Save this to compare later.

    # Convert to Python List
    arg = r.json()

    # This GET request returns either a 200 or a 404 Not Found.
    # So we should check to see if the project ID that the user gave us is valid.
    if status == 200:
        print "GET worked. Code 200!"               # It worked if it is a 200

        # Print out the project information.
        print r.json()['id']
        print r.json()['name']
        print r.json()['fields']                                # We will probably use just the fields in the future.
        print "URL: %s" % r.json()['url']

    if status == 404:                                           # 404 means not found.
        print "Couldn't find that project! You had entered %s for a project ID." % project_id

    # Ask the user if they want to continue.
    try_again = raw_input("\nWould you like to search again? (Y/N) -> ")

    if try_again == 'N' or try_again == 'n':
        print "Exiting..."
        break;
        print "\n\n"