import json
import urllib2

data = json.load(urllib2.urlopen('http://rsense-dev.cs.uml.edu/api/v1/projects/744'))

print data['id']
print data['name']
print data['fields']
