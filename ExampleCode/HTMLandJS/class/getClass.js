function get(){


	isense.isense(106,'key','JIM');

	console.log(isense.getDatasetFieldData('MLB Team Statistics 2013','Runs'));

	data = [2,5,4,8,7,4,4];

	isense.postDataset('Runs','lsifjel684iefj',data);
	fields = ['Runs','Hits','Walks'];

	isense.appendToDataset(fields,'titlesldfijsleifj',data);
/*
	console.log(isense.getDatasetFieldData(106,"MLB Team Statistics 2013","Hits"));  // Project ID, Dataset Name, Field Name


	data = [5,4,8,4,5,3,3,84,5484]



	isense.postDataset(927,"Key","Dice Roll","TEST","Tyler",data);  // Project ID,Contributor Key,Title,Contributor Name,data as an array
<<<<<<< HEAD
	*/
}



=======

	fieldNameArray = ['Walks','Home Runs'];

	data1 = [1,2];
	data2 = [10,11,12,13];

	ArrayofDataArrays = [data1,data2];



	isense.postMultipleDataset(106,'Key',fieldNameArray,'title','Tyler',ArrayofDataArrays)
}
>>>>>>> d284520582fc9b92075f98da6b6a3cbfc90b2d5a
