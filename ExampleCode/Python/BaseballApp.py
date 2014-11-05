import requests, json, sys,time, datetime

print '\n'

timestamp = time.time()

timestamp2 = datetime.datetime.fromtimestamp(timestamp).strftime('%Y-%m-%d %H:%M:%S')

URL1 = "http://rsense-dev.cs.uml.edu/api/v1/data_sets/1190?recur=true.json"

r1 = []
r1 = requests.get(URL1)

status = r1.status_code

total_walks = []
total_bases = []
calculated_runs = []

for i in range(0, 30):
	total_walks.append(int(r1.json()['data'][i]['644']))
	total_bases.append(int(r1.json()['data'][i]['647']))	
	calculated_runs.append((total_walks[i] + total_bases[i])/4.0)

print "Walks: " , total_walks
print "Total Bases: : " , total_bases
print "Calculated Runs: " , calculated_runs

url2 = 'http://rsense-dev.cs.uml.edu/api/v1/projects/106/jsonDataUpload'

payload = {
    'title': 'title '+timestamp2,           
    'contribution_key': 'key',    
    'contributor_name': "Tyler",
    'data':
    {
        '4279': calculated_runs
    }
}

headers = {'content-type': 'application/json'}

r2 = requests.post(url2, data=json.dumps(payload), headers=headers)

print "Runs have been posted"

print '\n'



