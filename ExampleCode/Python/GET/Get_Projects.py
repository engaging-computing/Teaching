"""
        This script will be a test of getting a list of projects from rSENSE
        It will try to send different parameters to the GET PROJECTS API
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
    print "*  GET PROJECTS Script    *"
    print "***************************"

    # Get a project ID from the user. Format the URL for a GET request.
    search_term = raw_input("Enter a search term: ")
    print "\n"

    # GET Request:      /api/v1/projects
    URL = "http://rsense-dev.cs.uml.edu/api/v1/projects?utf8=true&search=%s&sort=updated_at&order=DESC" % search_term
    r = []
    r = requests.get(URL)

    # Convert to Python Array
    arg = r.json()

    # Turns out this GET only returns a 200... We'll have to see if arg is null instead.
    empty = is_empty(arg)
    if empty == True:
        try_again = raw_input("Seems like I couldn't find anything on that search. Want to try again? (Y/N) -> ")
        print "\n"

        if try_again == 'N' or try_again == 'n':
            break;

    # This prints out all the projects that the search result found.
    # The GET request we made gave us an array of projects. Each item in the array
    #  is a list containing info about a given project.
    for x in arg:
        print "Project Name: ", x['name']
        print "Projct ID: ", x['id']
        print "Project URL: ", x['url']
        print "Number of project fields: ", x['fieldCount']
        print "This project was created: ", x['createdAt']
        print "The project owner is: ", x['ownerName']
        print "\n"

    # Only ask the user ONCE if they want to continue.
    if empty == False:
        try_again = raw_input("Would you like to search again? (Y/N) -> ")
        if try_again == 'N' or try_again == 'n':
            print "Exiting..."
            break;
        print "\n\n"