import requests,json

baseUrl = 'http://rsense-dev.cs.uml.edu/api/v1/projects/';

def projectGetRequest(projectID):
    urlProject = baseUrl+projectID+'?recur=true';

    data = requests.get(urlProject)

    return data
def getDatasetLocation(datasetName,parsedResponseProject):

    j = 0


    while j < parsedResponseProject.json()['dataSetCount']:


        if parsedResponseProject.json()['dataSets'][j]['name'] == datasetName:
            print 'heyyyyyyyyyyyyyyy'
            datasetLocation = j
            datasetID = parsedResponseProject.json()['dataSets'][j]['id']
            return datasetLocation
        j+=1

    return 'Dataset not found'

def getFieldID(fieldName,parsedResponseProject):

    i = 0

    while i < parsedResponseProject.json()['fieldCount']:

        if parsedResponseProject.json()['fields'][i]['name'] == fieldName:
            fieldID = parsedResponseProject.json()['fields'][i]['id']
            return fieldID;
        i += 1
        
    return "Field Not Found"
    
def getDatasetFieldData(projectID,datasetName,fieldName):

    values = []
    k = 0

    parsedResponseProject = projectGetRequest(projectID)

    datasetLocation = getDatasetLocation(datasetName,parsedResponseProject)

    fieldID = getFieldID(fieldName,parsedResponseProject)

    fieldID = str(fieldID)

    while k < parsedResponseProject.json()['dataSets'][datasetLocation]['datapointCount']:

        values.append(parsedResponseProject.json()['dataSets'][datasetLocation]['data'][k][fieldID])  
        k += 1 
    

    return values

def postDataset(projectID,datasetName,fieldName,contributionKey,contributorName,fieldData):
    
    parsedResponseProject = projectGetRequest(projectID)
    fieldID = getFieldID(fieldName,parsedResponseProject)
    url = 'http://rsense-dev.cs.uml.edu/api/v1/projects/106/jsonDataUpload'


    payload = {
        'title': datasetName,                                 
        'contribution_key':  contributionKey,                    
        'contributor_name': contributorName,
        'data':
        {
            fieldID: fieldData
        }
    }
    headers = {'content-type': 'application/json'}

    r = requests.post(url, data=json.dumps(payload), headers=headers)





