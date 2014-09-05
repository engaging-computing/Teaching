import json
import urllib2

data = json.load(urllib2.urlopen('http://rsense-dev.cs.uml.edu/api/v1/projects/683'))

print data['id']
print data['name']