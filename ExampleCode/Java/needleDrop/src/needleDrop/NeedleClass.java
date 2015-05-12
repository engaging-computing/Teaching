package needleDrop;
import java.util.Random;


public class NeedleClass {
	
	//Creates a Needle class with a variable for the number of throws and hits
	
	   private Random generator;
	   private int hits;
	   private int toss;
	   
	  //creates an instance of the class needle and initializes the member variable to 0 
	   public NeedleClass()
	   {
	      hits = 0;
	      toss = 0;
	   
	      // initializes generator to random integer
	      generator = new Random();
	   }
	
	   //"Drops the needle" calculates whether the needle hits the line or not. Increments the value of toss by 1
	   // and determines if the value of hits should by incremented by one
	   public void drop()
	   {
		 double ylow = 2 * generator.nextDouble();
		 double angle = 180 * generator.nextDouble(); 
	   
	     double yhigh = ylow + Math.sin(Math.toRadians(angle));
	     if (yhigh >= 2) hits++;    
	   
	     toss++;
	  	  
	   }
	   
	   public int getHits()
	   {
		 return hits;
	   }

	   //Returns the value of toss
	   public int getToss()
	   {
	      return toss;
	   }

	   //Prints out the values of Toss and Hits
	   public void printValues() {

	   	System.out.println("The total number of drops is " + getToss());
	   	System.out.println("The total number of hits is " + getHits());
	   	}

	}


