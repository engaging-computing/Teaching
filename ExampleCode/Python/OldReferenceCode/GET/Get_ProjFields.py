"""
        This script will be a test of getting a project's fields
"""
import requests, json, sys

# This function will loop until the user tells it to quit.
def loop_user():
    print "***************************"
    print "*    GET FIELDS Script    *"
    print "***************************"

     # Get a project ID from the user. Format the URL for a GET request.
    project_ID = raw_input("Enter a project ID: ")

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

        # Print out the project information.
        print "\nPROJECT INFORMATION"
        print "  Project ID: %s" % r.json()['id']
        print "Project Name: %s" % r.json()['name']
        print " Project URL: %s" % r.json()['url']

        # Let's make sure there are fields for us to check. FieldCount should be 0 if there aren't any fields to show.
        empty = r.json()['fieldCount']

        # If there aren't any fields, just go back to the beginning.
        if empty == 0:
            print "\nI didn't find any fields for this project! Try a different Project that has fields."
            loop_again()    # See if they want to search for more projects.

        # Even more info:
        print "\nName & ID of each field found in this project: "
        arg = r.json()['fields']

        for i in arg:
            print "Field Name: %s" % i['name']
            print "Field ID: %s" % i['id']

        loop_again()    # See if they want to search for more projects.

    # 404 means not found.
    if status == 404:
        print "\nCouldn't find that project! You had entered %s for a project ID." % project_ID
        print "Try a project ID that exists."
        loop_again()

def loop_again():
    # Ask the user if they want to continue.
    try_again = raw_input("\nWould you like to search again? (Y/N) -> ")

    if try_again == 'Y' or try_again == 'y':
        print "\n"
        loop_user()

    else:
        exit_script()

# Prints out after the looping is over.
def exit_script():
    print "\nExiting..."
    sys.exit()

loop_user()