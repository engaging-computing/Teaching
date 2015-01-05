import requests,json,time,datetime

baseUrl = 'http://rsense-dev.cs.uml.edu/api/v1/projects/';

def projectGetRequest(projectID):
    
    urlProject = baseUrl+projectID+'?recur=true';

    data = requests.get(urlProject)

    return data

def getDatasetLocation(datasetName,parsedResponseProject):

    for i in range(0,parsedResponseProject.json()['dataSetCount']):

        if parsedResponseProject.json()['dataSets'][i]['name'] == datasetName:
            datasetLocation = i
            datasetID = parsedResponseProject.json()['dataSets'][i]['id']
            return datasetLocation

    return 'Dataset not found'

def getFieldID(fieldName,parsedResponseProject):

    for i in range(0,parsedResponseProject.json()['fieldCount']):

          if parsedResponseProject.json()['fields'][i]['name'] == fieldName:
            fieldID = parsedResponseProject.json()['fields'][i]['id']
            return fieldID;
   
    return "Field Not Found"      
  
def getDatasetFieldData(projectID,datasetName,fieldName):

    values = []

    parsedResponseProject = projectGetRequest(projectID)

    datasetLocation = getDatasetLocation(datasetName,parsedResponseProject)

    fieldID = getFieldID(fieldName,parsedResponseProject)

    fieldID = str(fieldID)

    for i in range(0,parsedResponseProject.json()['dataSets'][datasetLocation]['datapointCount']):
        values.append(parsedResponseProject.json()['dataSets'][datasetLocation]['data'][i][fieldID])  

    return values

def postDataset(projectID,contributionKey,fieldName,datasetName,contributorName,fieldData):
    
    timestamp = time.time()
    timestamp_reformatted = datetime.datetime.fromtimestamp(timestamp).strftime('%Y-%m-%d %H:%M:%S')

    parsedResponseProject = projectGetRequest(projectID)
    fieldID = getFieldID(fieldName,parsedResponseProject)
    url = baseUrl+projectID+'/jsonDataUpload'

    payload = {
        'title': datasetName + ' ' + timestamp_reformatted,                                 
        'contribution_key':  contributionKey,                    
        'contributor_name': contributorName,
        'data':
        {
            fieldID: fieldData
        }
    }
    headers = {'content-type': 'application/json'}

    r = requests.post(url, data=json.dumps(payload), headers=headers)

    print "Post Complete"
