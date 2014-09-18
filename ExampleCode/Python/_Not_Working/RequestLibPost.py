import http.client
import json

connection = http.client.HTTPSConnection('rsense-dev.cs.uml.edu')

headers = {'Content-type': 'application/json'}

foo = {'email': 't@t.t','password':'t','title':'Test','data':{'3129':'5'}}
json_foo = json.dumps(foo)

connection.request('POST', '/api/v1/projects/683/jsonDataUpload', json_foo, headers)

response = connection.getresponse()
print(response.read().decode())