import requests, json, sys

print "Basic iSENSE JSON uploader using Contributor Keys\n";

# POST stuff.
url = 'http://rsense-dev.cs.uml.edu/api/v1/data_sets/append'

payload = {
    'contribution_key': '123',
    'id' : '7742',
    'data':
    {
        '4566': [123456789]
    }
}

# This is needed, otherwise I got code 422s and the data wasn't showing up right in the log.
headers = {'content-type': 'application/json'}

r = requests.post(url, data=json.dumps(payload), headers=headers)

print "HTTP Code: ", r.status_code;