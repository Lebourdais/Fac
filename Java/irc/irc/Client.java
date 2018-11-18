

import java.io.*;
import java.util.*;
import java.net.*;

public class Client implements Runnable {
    private Socket socket;
    private DataOutputStream dout;
    private DataInputStream din;
    public String history;
    // Constructor

    public Client(){

    }
    public String getHistory(){
      return history;
    }

    public Client(String host, int port) {

        try {
            socket = new Socket(host, port);
            System.out.println("connected to " + socket);
            din = new DataInputStream(socket.getInputStream());
            dout = new DataOutputStream(socket.getOutputStream());
            new Thread(this).start();
        } catch (IOException ie) {
            System.out.println(ie);
        }
    }

    private void processMessage(String message) {
        this.history += message+"\n";
    }

    public void run() {
    try {
        String message = din.readUTF();
        System.out.println(message);
    } catch (IOException ie) {
        System.out.println(ie);
    }
}


    public static void goOnline(String host, String port, String userName) {
        int portNumber = Integer.parseInt(port);
        Client c = new Client(host, portNumber);
        c.processMessage("Username: " + userName);
        String prompt;
        System.out.println("Le client démarre");
        while (true) {
            prompt = "test";
            c.processMessage(prompt);
            c.run();
        }
    }
}
