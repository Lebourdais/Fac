import java.net.*;
import java.io.*;

public class Server extends Threads{
	private Socket          socket   = null;
    private ServerSocket    server   = null;
    private DataInputStream streamIn =  null;

    public Server(int port){
    	try{
    		System.out.println("Binding to port " + port + ", please wait  ...");
            server = new ServerSocket(port);
            System.out.println("le serveur est à l'écoute du port : "+server.getLocalPort());
            System.out.println("Server started: " + server);
            System.out.println("Waiting for a client ...");
						while(true){
							//attente d'un connexion
							Socket sockServ=serveur.accept();
							System.err.println("Connexion from : "+sockServ.getInetAddress());
							Serveur thread = new Serveur(sockServ);
							thread.start();
							thread.run();

						}
            close();
        }
    	catch(IOException ioe){
    	   ioe.printStackTrace();
        }
    }
    public void open() throws IOException {
	    streamIn = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
    }
    public void close() throws IOException{
	    if (socket != null)    socket.close();
        if (streamIn != null)  streamIn.close();
    }
    public static void main(String args[]){
	    Server server = new Server(0);
    }
}
