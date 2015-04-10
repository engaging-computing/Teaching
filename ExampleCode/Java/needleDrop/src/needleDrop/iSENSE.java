package needleDrop;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

import org.json.JSONArray;
import org.json.JSONObject;

import edu.uml.cs.isense.api.API;
import edu.uml.cs.isense.api.UploadInfo;
import edu.uml.cs.isense.objects.RDataSet;
import edu.uml.cs.isense.objects.RPerson;
import edu.uml.cs.isense.objects.RProjectField;

public class iSENSE {

	private API m_api;
	private ArrayList<RProjectField> m_fields;
	private String m_userName;
	private String m_passWord;
	private RPerson m_logIn;
	private HashMap<String, Long> fieldInfoByName;
	private HashMap<Long, String> fieldInfoByID;
	private JSONArray data;
	private int m_projectID;
	private String m_contribKey;
	private String m_name;
	
	//Creates instance of iSENSE class using user credentials
	public iSENSE(int projectID, String userName, String passWord, String name ) throws Exception
	{
		init(projectID, name);
		
		m_name = name;
		m_userName = userName;
		m_passWord = passWord;
		m_logIn = m_api.createSession(m_userName, m_passWord);
		
	}
	
	//Creates instance of iSENSE using contributor key
	public iSENSE(int projectID, String contribKey, String name) throws Exception
	{
		
		init(projectID, name);

		m_userName = null;
		m_contribKey = contribKey;
		
	}
	
	//Function that initializes part of the iSENSE object
	private void init(int projectID, String name) throws Exception 
	{	
		m_api = API.getInstance();
		m_api.useDev(true);
		m_fields = m_api.getProjectFields(projectID);
		if(m_fields.size() == 0)
			throw new Exception("No fields for project #" + projectID);
			
		m_projectID = projectID;
		data = new JSONArray();
		m_name = name;
		
		if(m_fields == null ){
			
			throw new Exception("Fields are null.");
			
		}
			
		fieldInfoByName = new HashMap<String,Long>();
		fieldInfoByID = new HashMap<Long,String>();
		for( RProjectField f : m_fields ) 
		{
			fieldInfoByName.put(f.name, f.field_id);
			fieldInfoByID.put(f.field_id, f.name);
		}
			
	}
	
	
	//Uploads a data set to specified project using credentials
	public void uploadDataSet(String dataSetName)
	{
		JSONObject colData = m_api.rowsToCols(new JSONObject().put("data", data));
		
		UploadInfo info = m_api.uploadDataSet(m_projectID, colData, dataSetName);
		data = new JSONArray();
	}
	
	//Uploads a data set using contributor key
	public void uploadConKey( String dataSetName )
	{
		JSONObject colData = m_api.rowsToCols(new JSONObject().put("data", data));
		
		m_api.uploadDataSet(m_projectID, colData, dataSetName,  m_contribKey, m_name);
		data = new JSONArray();
	}
	
	//Pulls down the fields from the designated project and stores them in hashmap
	public ArrayList<String> getFields()
	{
		ArrayList<String> fields = new ArrayList<String>();
		
		for (RProjectField f : m_fields )
		{
			fields.add(f.name);
		}
		return fields;
	}
	
	//Puts data in fields
	public void putData( ArrayList<String> fields, ArrayList<?> userData)
	{
		int i = 0;
		
		JSONObject row = new JSONObject();
		
		if( fields.size() != userData.size())
		{
			System.out.println("Error: field size does not equal data size.");
			return;
		}
		
		for(String s : fields )
		{
			String id = "" + fieldInfoByName.get(s);
			row.put(id, userData.get(i++).toString());
		}
		data.put(row);
	}
	
	//Pulls down data set from website and returns fields w/ data
	public JSONObject getDataSet(int dsID) throws Exception 
	{
		JSONObject retData = new JSONObject();
		try{
		
			RDataSet dataSet = m_api.getDataSet(dsID);
			if (dataSet == null)
				throw new Exception("Data for data set #" + dsID + "  is null");
			
			JSONObject apiData = dataSet.data;
			Iterator<?> keys = apiData.keys();
			
	        while( keys.hasNext() ){
	            String key = (String)keys.next();
	         
	           	Long fID = Long.parseLong(key);
	           	String fieldName = fieldInfoByID.get(fID);
	           	retData.put(fieldName, apiData.get(key));
         
	        }
		}catch(Exception e){
			throw e;
		}
		return retData;
	}
	
}
