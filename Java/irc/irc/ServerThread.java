

import java.io.*;
import java.util.*;
import java.net.*;

public class ServerThread extends Thread { // The Server that spawned us
    private Server server;
    private Socket socket;

    public ServerThread(Server server, Socket socket) {
        this.server = server;
        this.socket = socket;
        start();
    }

    public void run() {
      System.out.println("Test de passage : Démarrage du thread");
        try {
            DataInputStream din = new DataInputStream(socket.getInputStream());
            while (true) {
                String message = din.readUTF();
                StringTokenizer stt = new StringTokenizer(message, " ");
                System.out.println(message);
                while (stt.hasMoreTokens()) {
                    String token = stt.nextToken();
                    if (token.equals("Username:")) {
                        String username = stt.nextToken();
                        System.out.println("username : "+username);
                        server.addInfo(username, socket);
                    }
                }
                System.out.println("Sending " + message);

                server.sendToAll(message);
                if (message.equals("Exit")) {
                    System.out.println("Bye Bye");
                    server.removeConnection(socket);
                    System.exit(1);
                }
            }
        } catch (EOFException ie) {
        } catch (IOException ie) {
            ie.printStackTrace();
        } finally {
            server.removeConnection(socket);
        }
    }
}
