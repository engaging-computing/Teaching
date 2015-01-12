function get(){


isense.isense(106,'Key','JIM');

console.log(isense.getDatasetFieldData('MLB Team Statistics 2013','Runs'));

data = [2,5,4,8,4];

isense.postDataset('Runs','title',data);
/*
	console.log(isense.getDatasetFieldData(106,"MLB Team Statistics 2013","Hits"));  // Project ID, Dataset Name, Field Name


	data = [5,4,8,4,5,3,3,84,5484]



	isense.postDataset(927,"Key","Dice Roll","TEST","Tyler",data);  // Project ID,Contributor Key,Title,Contributor Name,data as an array
	*/
}