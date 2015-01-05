import requests, json, sys,time, datetime
import IsenseModule

total_walks_strings = []
total_bases_strings = []
total_walks = []
total_bases = []
calculated_runs = []

total_walks_strings = IsenseModule.getDatasetFieldData('106','MLB Team Statistics 2013','Walks')
total_bases_strings = IsenseModule.getDatasetFieldData('106','MLB Team Statistics 2013','Total Bases')

for i in range(0,30):
    total_walks.append(int(total_walks_strings[i]))
    total_bases.append(int(total_bases_strings[i]))
    calculated_runs.append((total_walks[i] + total_bases[i])/4.0)

print total_walks
print "\n"
print "Walks: " , total_walks
print "Total Bases: " , total_bases
print "Calculated Runs: " , calculated_runs

IsenseModule.postDataset('106','Key','Calculated Runs','TEST','Tyler',calculated_runs)

print '\n'
