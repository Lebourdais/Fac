

import java.io.*;
import java.net.*;
import java.util.*;

public class Server { // The ServerSocket we'll use for accepting new
                        // connections
    private ServerSocket ss;

    private HashMap<String, Socket> userInfo = new HashMap<String, Socket>();

    // A mapping from sockets to DataOutputStreams.
    private Hashtable<Socket, DataOutputStream> outputStreams = new Hashtable<Socket, DataOutputStream>();

    // Constructor and while-accept loop all in one.
    public Server(int port) throws IOException {
        // All we have to do is listen
        listen(port);
    }

    private void listen(int port) throws IOException {
        // ServerSocket
        ss = new ServerSocket(port);
        System.out.println("Listening on " + ss);
        while (true) {
            Socket s = ss.accept();
            System.out.println("Connection from " + s);

            DataOutputStream dout = new DataOutputStream(s.getOutputStream());
            DataOutputStream userInfo = new DataOutputStream(s.getOutputStream());
            System.out.println("Test de passage : listen");
            outputStreams.put(s, dout);
            outputStreams.put(s, userInfo);
            new ServerThread(this, s);
        }
    }

    Enumeration<DataOutputStream> getOutputStreams() {
        return outputStreams.elements();
    }

    void sendToAll(String message) {
        for (Enumeration<DataOutputStream> e = getOutputStreams(); e.hasMoreElements();) {
            // Output Stream
            DataOutputStream dout = (DataOutputStream) e.nextElement();
            // Send Message
            try {
                dout.writeUTF(message);
            } catch (IOException ie) {
                System.out.println(ie);
            }
        }
    }

    // Remove socket,
    void removeConnection(Socket s) {
        // Synchronize
        synchronized (outputStreams) {
            // Tell the world
            System.out.println("Removing connection to " + s);
            // Remove it from hashtable
            outputStreams.remove(s);
            try {
                s.close();
            } catch (IOException ie) {
                System.out.println("Error closing " + s);
                ie.printStackTrace();
            }
        }
    }

    void addInfo(String user, Socket s) {
        userInfo.put(user, s);
    }

    // Main
    static public void main(String args[]) throws Exception {
        // Get port
        int port = Integer.parseInt(args[0]);
        // Create Server object
        new Server(port);
    }
}
