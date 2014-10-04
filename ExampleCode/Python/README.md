Python
=====

These examples use a variety of python libraries.

For HTTP GET/POST requests, there are two that seem to work:

1) urllib2 / json - working for basic GET requests

2) requests - works for GET and POST requests

To install those, simply use the following command (on Linux. Windows How-To coming soon):

pip install requests

More information about the Requests library can be found here:
http://docs.python-requests.org/en/latest/user/quickstart/

Notes

1) For POST requests, it seems you need to format the request a specific way.

This is an example of a request that should work, given a valid iSENSE URL:

import json

url = 'http://rsense-dev.cs.uml.edu/api/v1/projects/744/jsonDataUpload'

payload = {'FIELDS': '[DATA, DATA, DATA]'}

headers = {'content-type': 'application/json'}

r = requests.post(url, data=json.dumps(payload), headers=headers)

The above code is based off of the following page:

http://docs.python-requests.org/en/latest/user/quickstart/#json-response-content

2) To get the fields for an iSENSE project, go to the following URL:

http://rsense-dev.cs.uml.edu/api/v1/projects/PROJECT_ID

(Replace PROJECT_ID with the ID of the project you want to use.)