import java.io.*;
import java.io.IOException;


public class Reception implements Runnable {

	private DataInputStream in;
	private String message = null;

	public Reception(DataInputStream in){

		this.in = in;
	}

	public void run() {

		while(true){
	        try {

			message = in.readLine();
			System.out.println(message);

		    } catch (IOException e) {

				e.printStackTrace();
			}
		}
	}

}
