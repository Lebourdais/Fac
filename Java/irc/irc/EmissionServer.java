import java.io.IOException;
import java.io.*;

import java.net.*;

public class EmissionServer implements Runnable {

	private DataOutputStream out;
	private String login = null, message = null;
	private String h ;
	private Socket sock;

	public EmissionServer(Socket socket,String h) {
		this.sock = new Socket();
		this.h = h;
		try{
			this.out = new DataOutputStream(socket.getOutputStream());
		}
		catch(IOException ioe){
			ioe.printStackTrace();
		}

	}


	public void run() {


				try{
					message = h;
					out.writeChars(message);
				  out.flush();
				}
				catch(IOException ioe){
					ioe.printStackTrace();
				}

	}
}
