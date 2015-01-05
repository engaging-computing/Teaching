import requests,json,sys,time,datetime,IsenseModule

total_walks = []
total_bases = []
calculated_runs = []

total_walks = IsenseModule.getDatasetFieldData('106','MLB Team Statistics 2013','Walks')
total_bases = IsenseModule.getDatasetFieldData('106','MLB Team Statistics 2013','Total Bases')

for i in range(0,30):
    calculated_runs.append((total_walks[i] + total_bases[i])/4.0)

print "\n"
print "Walks: " , total_walks
print "Total Bases: " , total_bases
print "Calculated Runs: " , calculated_runs

IsenseModule.postDataset('106','Key','Calculated Runs','TEST','Tyler',calculated_runs)

print '\n'
