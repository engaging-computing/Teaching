import requests, json, sys,time, datetime

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


print calculated_runs

url2 = 'http://rsense-dev.cs.uml.edu/api/v1/projects/106/jsonDataUpload'

payload = {
    'title': 'title '+timestamp2,                     # Note, spent forever trying to figure this out.
    'contribution_key': 'key',    # But it's contribution_key - not contributor_key
    'contributor_name': "Tyler",
    'data':
    {
        '4279': calculated_runs
    }
}

# This is needed, otherwise I got code 422s and the data wasn't showing up right in the log.
headers = {'content-type': 'application/json'}

r2 = requests.post(url2, data=json.dumps(payload), headers=headers)

print r2.status_code


