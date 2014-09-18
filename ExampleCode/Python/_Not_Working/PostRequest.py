
import urllib
import urllib2

url = 'http://rsense-dev.cs.uml.edu/api/v1/projects/683/jsonDataUpload'
values = {'email' : 't@t.t',
          'password' : 't',
          'title':'Test',
          'data':'{"3129":5}'}
print values
data = urllib.urlencode(values)
print data
req = urllib2.Request(url, data)
print req
response = urllib2.urlopen(req)
the_page = response.read()