import IsenseModuleFields
#Testing file written by Katherine Brunelle 2015

"""    CHECK NUM
# takes a string and checks to make sure that the value is in fact a number
# designed to check raw input for the user input of variables
# as the variables we are measuring must be positive, in a non-number case it returns -1
# will also return an error if a negative symbol is input, since that is not valid data
# returns -1 for an error or the float version of the variable if a correct value
"""
def check_num(var):
    decimal_count = 0    #keeps track of the number of .s in the number
    for char in var:
        if char == '-':
            print 'Error: a negative value is not possible for this test'
            return -1
        elif char == '.':
            decimal_count += 1
            if decimal_count > 1:
                print 'Error: multiple decimal places detected'
                return -1
        elif not('0' <= char and char <= '9'):
            print 'Error: non-digit character detected'
            return -1
    #if we got out of the loop, it's a valid num
    print '\nData successfully stored\n'
    return float(var)
    
"""     STRINGIFY
# takes the number to turn into a string
# returns that the number is not stored if the passed number is -1
# else returns the number in string form
"""
def stringify(num):
    if num == -1:
        return "No data stored"
    else:
        return str(num)
"""      PUBLISH DATASET
# takes no parameters
# checks to make sure all the data is valid, then publishes if true
# returns nothing
"""
def publish_dataset():
    values = [] 
    allow_publish = True
    values.append(stringify(nitrate))
    values.append(stringify(pH))
    values.append(stringify(dis_ox))
    values.append(stringify(temp))
    values.append(latitude)
    values.append(longitude)
    for x in range(0, len(values)):
        if values[x] == 'No data stored':
            print '\nPlease enter all data before publishing.\n'
            allow_publish = False
            break
    if allow_publish == True:
        IsenseModuleFields.postDataset(project_number,'upload',fields,'Table ' + table.capitalize(),'Katherine',values)
        print '\nData published\n'
    #no else case

#data that is the same regardless
project_number = '1190'
latitude = 42.640385675075414
longitude = -71.3520118906738

#the fields to upload, must be in the same order as fieldData to upload.
#both must be lists, as a dictionary will randomize the order pairings for postDataset
fields = ['Nitrate',
          'pH',
          'Dissolved Oxygen',
          'Temperature',
          'Latitude',
          'Longitude']

#data that changes for running
table   = ''
temp    = -1
dis_ox  = -1
pH      = -1
nitrate = -1
lat     = -1
long    = -1

while True:
    table = raw_input('Enter your table letter(A, B, or C): ')
    if table == 'A' or table == 'a':
        break
    elif table == 'B' or table == 'b':
        break
    elif table == 'C' or table == 'c':
        break;

while True:
    ans = raw_input('1) Enter Temperature\n'
                    '2) Enter Dissolved Oxygen\n'
                    '3) Enter pH\n'
                    '4) Enter Nitrates\n'
                    '5) Print Stored Data\n'
                    '6) Publish Data\n'
                    '7) Quit\n')
    ans = int(ans)
    if ans == 1:
        temp = raw_input('\nEnter your temperature reading: ')
        temp = check_num(temp)
    elif ans == 2:
        dis_ox = raw_input('\nEnter your disolved oxygen reading: ')
        dis_ox = check_num(dis_ox)
    elif ans == 3:
        pH = raw_input('\nEnter your pH reading: ')
        pH = check_num(pH)
    elif ans == 4:
        nitrate = raw_input('\nEnter your nitrate reading: ')
        nitrate = check_num(nitrate)
    elif ans == 5:
        #print out each stored value, stringify accounts for unstored values
        print '            Temp: ' + stringify(temp)
        print 'Dissolved Oxygen: ' + stringify(dis_ox)
        print '              pH: ' + stringify(pH)
        print '         Nitrate: ' + stringify(nitrate)
        print '\n'
    elif ans == 6:
        publish_dataset()
    else:
        #stops the loop if the user enters anything that isn't the correct number/exits
        break
       
       
       
       
       
       
       