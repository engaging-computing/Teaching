import IsenseModule

data = IsenseModule.getDatasetFieldData('106','MLB Team Statistics 2013','Runs')

print data

IsenseModule.postDataset('106','Key','Calculated Runs','TEST','TYLER',data)