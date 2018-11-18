import java.io.IOException;
import java.io.*;
import java.util.Scanner;


public class Emission implements Runnable {

	private DataOutputStream out;
	private String login = null, message = null;
	private Scanner sc = null;

	public Emission(DataOutputStream out) {
		this.out = out;

	}


	public void run() {

		  sc = new Scanner(System.in);

		  while(true){
			    System.out.println("Votre message :");
				try{
					message = sc.nextLine();
					out.writeChars(message);
				  out.flush();
				}
				catch(IOException ioe){
					ioe.printStackTrace();
				}

			  }
	}
}
