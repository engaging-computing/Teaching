import requests,json

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

def getFieldID(fieldNames,parsedResponseProject):

    fields = []

    for i in range(0,parsedResponseProject.json()['fieldCount']):
        for x in range(0,len(fieldNames)):
          if parsedResponseProject.json()['fields'][i]['name'] == fieldNames[x]:
            fieldID = parsedResponseProject.json()['fields'][i]['id']
            fields.append(parsedResponseProject.json()['fields'][i]['id'])
    
    if len(fields) == 0:
        return "No valid fields found"
    else:
        return fields
  
def getDatasetFieldData(projectID,datasetName,fieldName):

    values = []

    parsedResponseProject = projectGetRequest(projectID)

    datasetLocation = getDatasetLocation(datasetName,parsedResponseProject)

    fieldID = getFieldID(fieldName,parsedResponseProject)

    fieldID = str(fieldID)

    for i in range(0,parsedResponseProject.json()['dataSets'][datasetLocation]['datapointCount']):
        values.append(parsedResponseProject.json()['dataSets'][datasetLocation]['data'][i][fieldID])         

    return values

def postDataset(projectID,contributionKey,fieldNames,datasetName,contributorName,fieldData):
    
    if len(fieldNames) != len(fieldData):
        print 'Error: not the same number of fields and data'
        exit()
    
    parsedResponseProject = projectGetRequest(projectID)
    fieldID = getFieldID(fieldNames,parsedResponseProject)
    url = baseUrl+projectID+'/jsonDataUpload'

    payload = {
        'title': datasetName,                                 
        'contribution_key':  contributionKey,                    
        'contributor_name': contributorName,
        'data':
        {
        }
    }
    
    #now we need to add all the data to upload in payload
    for x in range(0, len(fieldID)):
        payload['data'][fieldID[x]] = fieldData[x:(x+1)]
        
    headers = {'content-type': 'application/json'}

    r = requests.post(url, data=json.dumps(payload), headers=headers)








