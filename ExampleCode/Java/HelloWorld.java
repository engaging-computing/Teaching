import java.io.BufferedReader;
import java.io.Console;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;


class HelloWorld
{
   public static void main(String args[])
   {
        System.out.println("Hello World");
        System.out.println("This is a test.");

        // Required for taking user input from the terminal.
        Scanner reader = new Scanner(System.in);

        // Get email / password
        System.out.print("Enter your email:  ");
        String email = console.readLine();
        String password = console.readPassword("Enter your password: ");
        System.out.print("Enter a number:  ");      // Use print for no new line.
        int number = reader.nextInt();

        System.out.println("You entered the number: " + number);

        // Now to try GET / POST in Java
        String isense = "http://rsense-dev.cs.uml.edu/api/v1/projects/744/jsonDataUpload";
   }
}