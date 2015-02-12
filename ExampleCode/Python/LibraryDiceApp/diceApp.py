
# MUST COPY NEW LIBRARY INTO THIS DIRECTORY AFTER PULL REQUEST

import IsenseModule,random,sys

rolls = []

while 1:

	print "1) Roll"
	print "2) Post Rolls"
	print "3) Clear Rolls"
	print "4) Post 1000 Rolls"
	print "5) Exit"

	choice = raw_input()
	if choice == '1':
		rolls.append(random.randint(1,6))
		print "Rolls: " , rolls
	elif choice == '2':
		IsenseModule.postDataset('927','Key','Dice Roll','TEST','TYLER',rolls)
		rolls = []
		print "Rolls: " , rolls
	elif choice == '3':
		rolls = []
		print "Rolls: " , rolls
	elif choice == '4':
		rollse = []
		for i in range(0,1000):
			rolls.append(random.randint(1,6))
		IsenseModule.postDataset('927','Key','Dice Roll','TEST5','TYLER',rolls)
	elif choice == '5':
		sys.exit()
