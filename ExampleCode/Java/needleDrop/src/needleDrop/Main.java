package needleDrop;

import java.util.ArrayList;
import java.util.Scanner;

import org.json.JSONObject;

public class Main {

	private final static String conKey = "testing";
	private final static String name = "Jeremy";
	private final static int projID = 1003;

	public static void main(String[] arg) throws Exception {

		NeedleClass needle = new NeedleClass();
		Scanner input = new Scanner(System.in);
		iSENSE isense = new iSENSE(projID, conKey, name);

		//hit count variable
		int hits;

		//gets the fields
		ArrayList<String> fields;
		fields = isense.getFields();
		
		//initializes data 
		ArrayList<Integer> data = new ArrayList<Integer>();

		//asks user for number of needles to drop
		System.out.println("How many needles would you like to drop?");
		int drops = input.nextInt();

		//drops needle specified number of times
		for(int i = 0; i < drops; i++)
			needle.drop();

		//gets value of hits
		hits = needle.getHits();
		 
		//puts the drops and hits into the data array list
		data.add(drops);
		data.add(hits);

		//prints the number of drops and hits
		needle.printValues();
		 
		//puts data in the fields
		isense.putData(fields, data);
		 
		//Uploads data using contributor key
		isense.uploadConKey(conKey);
		 
		//Pulls down data from specified data set
		JSONObject values = isense.getDataSet(8702);
		
		System.out.println(values);
	}

}	
