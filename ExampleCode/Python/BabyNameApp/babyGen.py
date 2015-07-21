import requests, random, json, IsenseModule
"""
class Car(object):
    condition = "new"
    def __init__(self, model, color, mpg):
        self.model = model
        self.color = color
        self.mpg   = mpg

my_car = Car("DeLorean", "silver", 88)
"""

class name(object):
    def __init__(self, name, gender, position):
        self.name = name
        self.gender = gender
        self.position = position
    def printNameStats(self):
        print "Name: " + self.name
        print "Gender: " + self.gender
        print "Rank: " + str(self.position)

boy_names  = [] #171 boy names
girl_names = [] #169 girl names
gender = "none"
position = 0
run = True

boy_names  = IsenseModule.getDatasetFieldData('503','Most Popular Boy Names','Child First Name') 
girl_names = IsenseModule.getDatasetFieldData('503','Most Popular Girl Names','Child First Name')
all_names = boy_names + girl_names

while (run == True):
    rdm = random.randint(0,len(all_names))
    
    if(rdm > 171):
        #know that it's a girls name
        position = rdm - 170
        gender = "Female"
    else:
        position = rdm + 1
        gender = "Male"
        
    my_name = name(all_names[rdm], gender, position)
    print ''
    my_name.printNameStats()
        
    #find a new name? false = true = false
    while True:
        cont = raw_input("Would you like to find another name (y/n)?")
        if(cont != 'y') and (cont  != 'Y'):
            run = False
        break
        #else we consider it a 'no'
