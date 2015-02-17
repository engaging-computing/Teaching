function get(){

	isense.isense(106,'key','Tyler');
	console.log(isense.getDatasetFieldData('MLB Team Statistics 2013','Runs'));

	data = [5,4,8,4,8,4,8];
	isense.postDataset('Runs','TYLERTEST',data);

	fields = ['Runs'];
	data = [[5]];
	isense.postDatasetHorizontal(fields,'TEST12345654',data);

	fields2 = ['Runs','Walks'];
	data2 = [[5],[6]];
	isense.appendToDataset('TEST12345654 "2015-02-16T19:34:53.650Z"',fields2,data2);
}
