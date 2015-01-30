function get(){


	isense.isense(106,'key','JIM');

	console.log(isense.getDatasetFieldData('MLB Team Statistics 2013','Runs'));

	data = [2,5,4,8,7,4,4];

	//isense.postDataset('Runs','lsifjel684iefj',data);
	fields = ['Runs','Hits','Walks'];

	//isense.appendToDataset(fields,'titlesldfijsleifj',data);

	fieldNameArray = ['Walks','Home Runs'];

	data1 = [1,2];
	data2 = [10,11,12,13];

	ArrayofDataArrays = [data1,data2];



	isense.postMultipleDataset(106,'Key',fieldNameArray,'title','Tyler',ArrayofDataArrays)
}

