function get(){

	isense.isense(106,'key','JIM');

	console.log(isense.getDatasetFieldData('MLB Team Statistics 2013','Runs'));

	data = [2,5,4,8,7,4,4];

	//isense.postDataset('Runs','lsifjel684iefj',data);
	fields = ['Runs','Hits','Walks'];

<<<<<<< HEAD
fields = ['Runs','Hits','Walks']

isense.appendToDataset(fields,'titlesldfijsleifj',data);
/*
	console.log(isense.getDatasetFieldData(106,"MLB Team Statistics 2013","Hits"));  // Project ID, Dataset Name, Field Name


	data = [5,4,8,4,5,3,3,84,5484]



	isense.postDataset(927,"Key","Dice Roll","TEST","Tyler",data);  // Project ID,Contributor Key,Title,Contributor Name,data as an array
<<<<<<< HEAD
=======
	//isense.appendToDataset(fields,'titlesldfijsleifj',data);
>>>>>>> d399607340af7861913249812baf4cda0b0971d5

	fieldNameArray = ['Walks','Home Runs'];

	data1 = [1,2];
	data2 = [10,11,12,13];

	ArrayofDataArrays = [data1,data2];



<<<<<<< HEAD
	isense.postMultipleDataset(106,'Key',fieldNameArray,'title','Tyler',ArrayofDataArrays)
=======
	*/
>>>>>>> upstream/master
}
=======
	isense.postMultipleDataset(106,'key',fieldNameArray,'title4684','contributorName',ArrayofDataArrays);

	isense.postDatasetHorizontal(fieldNameArray,'title',ArrayofDataArrays);

}

>>>>>>> d399607340af7861913249812baf4cda0b0971d5
