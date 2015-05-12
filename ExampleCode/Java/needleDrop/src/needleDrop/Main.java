package needleDrop;

import java.util.ArrayList;
import java.util.Scanner;

import org.json.JSONObject;

public class Main {

	public static void main( String[] arg) throws Exception {
		
		 NeedleClass needle = new NeedleClass();
		 Scanner input = new Scanner(System.in);
		 iSENSE isense = new iSENSE(95500, "Testing", "Jeremy");
		 
		 int hits;
		 
		 ArrayList<String> fields;
		 fields = isense.getFields();
		
		 ArrayList<Integer> data = new ArrayList<Integer>();
		 
		/* System.out.println("How many needles would you like to drop?");
		 int drops = input.nextInt();
		 
		 for(int i = 0; i < drops; i++)
			 needle.drop();
		 
		 hits = needle.getHits();
		 
		 data.add(drops);
		 data.add(hits);
		 
		 needle.printValues();
		 isense.putData(fields, data);
		 
		 isense.uploadConKey("new");
		 */
		 JSONObject values = isense.getDataSet(10000);
		 System.out.println("hello");
		 System.out.println(values);
	}
		
}	
