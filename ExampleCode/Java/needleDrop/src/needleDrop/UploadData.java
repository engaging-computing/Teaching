package needleDrop;

import java.util.ArrayList;

import org.json.JSONArray;
import org.json.JSONObject;

import edu.uml.cs.isense.api.API;
import edu.uml.cs.isense.objects.RPerson;
import edu.uml.cs.isense.objects.RProjectField;

import java.util.Scanner;
import org.json.JSONObject;
import edu.uml.cs.isense.objects.RPerson;
import java.util.ArrayList;
import org.json.JSONArray;
import edu.uml.cs.isense.api.API;
import edu.uml.cs.isense.objects.RProjectField;

public class UploadData {

	private NeedleClass mNeedle;

	//Uploads the data to a specific data set on iSENSE
	public UploadData(NeedleClass needle) {
		mNeedle = needle;
	}
	
	public void upload() {
		
		//causes the data to upload to rSENSE
		API api = API.getInstance();
		api.useDev(true);
		
		Scanner input2 = new Scanner(System.in);
		
		System.out.println("Please input a project ID that the data will be uploaded to.");
		int projectID = input2.nextInt();
		
		//Pulls down the fields from specified project
		ArrayList<RProjectField> fields = api.getProjectFields(projectID );
		
		int hits = mNeedle.getHits();
		int toss = mNeedle.getToss();
		
		//initializes variables to the fields pulled down
		String field1 = Long.toString(fields.get(0).field_id);
		String field2 = Long.toString(fields.get(1).field_id); 
		
		//Logs user in as development account
		RPerson me = api.createSession("mobile.fake@example.com", "mobile");
		
		//creates JSONObject data  
		JSONObject data = new JSONObject();
		
		//puts value of toss and hits into the JSONObject data
		data.put(field1,new JSONArray().put(toss));
		data.put(field2, new JSONArray().put(hits));
		
		//prints out the data
		System.out.print(data.toString());
		
		//uploads the data
		api.uploadDataSet(projectID, data, "Drops and Hits");
		
	}
	
}
