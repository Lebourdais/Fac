import java.awt.*;
import java.awt.Color;
import java.lang.Math;
import java.awt.event.*;
import javax.swing.*;
import java.net.*;
import java.io.*;
import java.util.*;
import javax.swing.text.*;
public class IHM extends JFrame implements ActionListener{

	private JButton btConnection;
	private JButton btEnvoyer;
	private JTextField txNom;
	private JTextField txIP;
	private JTextField txPort;
	private JTextPane txConnectes;
	private JTextPane txDiscussion;
	private JTextArea txMessage;
	private Socket socket              = null;
	private DataInputStream  console   = null;
	private DataOutputStream streamOut = null;
	private ChatClientThread client    = null;
	private String serverName;
	private String serverPort;
	private Hashtable<String,Color> connectes;


	public IHM(){
		this.connectes = new Hashtable<String, Color>();
		setSize(500,600);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setResizable(false);

		BorderLayout bord = new BorderLayout();
		bord.setVgap(20);
		bord.setHgap(20);

		getContentPane().setLayout(bord);
		getContentPane().add(pannelOuest(), BorderLayout.WEST);
		getContentPane().add(pannelNord(), BorderLayout.NORTH);
		getContentPane().add(pannelCentre(), BorderLayout.CENTER);

		setVisible(true);
	}




	private JPanel pannelOuest(){
		System.out.println("----1----");
		JPanel box = new JPanel(new BorderLayout());

		JLabel lbConnectes = new JLabel("Connectés");
		lbConnectes.setHorizontalAlignment(0);


		this.txConnectes = new JTextPane();



		box.add(lbConnectes, BorderLayout.NORTH);
		box.add(txConnectes, BorderLayout.CENTER);

		return box;
	}
	private JPanel pannelNord(){
		System.out.println("----2----");
		GridLayout grid = new GridLayout(0,4);
		JPanel box = new JPanel(grid);

		grid.setVgap(10);

		JLabel lbNom = new JLabel("Nom");
		JLabel lbVide = new JLabel("");
		JLabel lbIP = new JLabel("IP");
		JLabel lbPort = new JLabel("Port");
		lbNom.setHorizontalAlignment(0);
		lbIP.setHorizontalAlignment(0);
		lbPort.setHorizontalAlignment(0);

		this.txNom = new JTextField();
		this.txIP = new JTextField();
		this.txPort = new JTextField();
		this.btConnection = new JButton("Connection");
		this.btConnection.addActionListener(this);
		box.add(lbNom);
		box.add(txNom);
		box.add(lbVide);
		box.add(btConnection);
		box.add(lbIP);
		box.add(txIP);
		box.add(lbPort);
		box.add(txPort);


		return box;
	}
	private JPanel pannelCentre(){
		System.out.println("----3----");
		BorderLayout nwBord = new BorderLayout();
		JPanel box = new JPanel(nwBord);
		nwBord.setVgap(10);


		JLabel lbDiscussion = new JLabel("Discussion");
		lbDiscussion.setHorizontalAlignment(0);
		JLabel lbMessage = new JLabel("Message");

		this.txDiscussion = new JTextPane();

		this.txMessage = new JTextArea();

		this.btEnvoyer = new JButton("Envoyer");
		this.btEnvoyer.addActionListener(this);
		JPanel bordNord = new JPanel(new BorderLayout());
		bordNord.add(lbDiscussion, BorderLayout.NORTH);
		bordNord.add(new JScrollPane(txDiscussion), BorderLayout.CENTER);

		JPanel bordCentre = new JPanel(new BorderLayout());
		bordCentre.add(lbMessage, BorderLayout.NORTH);
		bordCentre.add(txMessage, BorderLayout.CENTER);

		JPanel bordCentreBis = new JPanel(new BorderLayout());
		bordCentreBis.add(bordNord, BorderLayout.CENTER);
		bordCentreBis.add(bordCentre, BorderLayout.SOUTH);

		JPanel bordSud = new JPanel();
		bordSud.add(btEnvoyer);


		box.add(bordCentreBis, BorderLayout.CENTER);
		box.add(bordSud, BorderLayout.SOUTH);

		return box;
	}

	public static void main(String[] args){
		JFrame fenetre = new IHM();

	}

	public void actionPerformed(ActionEvent argO){
		if(argO.getActionCommand().equals("Connection")){
			if (txIP.getText() != ""){
				if (txPort.getText() != ""){
					if (txNom.getText() != ""){
						connectes.put(txNom.getText(),Color.GREEN);
						addCo(txNom.getText()+": ");
						connect(txIP.getText(), txPort.getText());
						btConnection.setText("Deconnection");
					}
				}
			}
		}
		if(argO.getActionCommand().equals("Deconnection")){

		}
		if(argO.getActionCommand().equals("Envoyer")){
			send(); txMessage.requestFocus();
		}
	}

	public void connect(String serverName, String serverPort){

		println("Establishing connection. Please wait ...");
		 try{
			 	socket = new Socket(serverName, Integer.parseInt(serverPort));
				println("Connected\n");
				System.out.println("On est connecté");
				open();
			}
		 catch(UnknownHostException uhe){
			 println("Host unknown: " + uhe.getMessage());
		 }
		 catch(IOException ioe){
			 println("Unexpected exception: " + ioe.getMessage());
		 }
	 }

	 private void send(){
		 try{
				streamOut.writeUTF(txNom.getText()+": "+txMessage.getText());
			  streamOut.flush(); txMessage.setText("");
			 }
	 	 catch(IOException ioe){
			 	println("Sending error: " + ioe.getMessage());
		 }
	 }
	 public void handle(String msg){

	 	println(msg);
	 }
	 public void open(){
		try{
			 	streamOut = new DataOutputStream(socket.getOutputStream());
      	client = new ChatClientThread(this, socket);
		}
    catch(IOException ioe){
			println("Error opening output stream: " + ioe);
		}
	}
	public void appendString(String str,Color color){
		SimpleAttributeSet style_pseudo = new SimpleAttributeSet();
		StyleConstants.setForeground(style_pseudo, color);
		String[] chaine = str.split(":");
		String message="";
		int i;
		StyledDocument document = (StyledDocument) txDiscussion.getDocument();
		try{
			document.insertString(document.getLength(), chaine[0], style_pseudo);
		}
		catch(BadLocationException ble){
			ble.printStackTrace();
		}
		for(i=1;i<chaine.length;i++){
			message+=chaine[i];
		}
		System.out.println(message);
		try{
			document.insertString(document.getLength(), message, null);
		}
		catch(BadLocationException ble){
			ble.printStackTrace();
		}

	}
	public void addCo(String str){
		SimpleAttributeSet style_pseudo = new SimpleAttributeSet();
		String[] chaine = str.split(":");
		StyleConstants.setForeground(style_pseudo, this.connectes.get(chaine[0]));
		StyledDocument document = (StyledDocument) txConnectes.getDocument();
		try{
			document.insertString(document.getLength(), chaine[0]+"\n", style_pseudo);
		}
		catch(BadLocationException ble){
			ble.printStackTrace();
		}
	}
  private void println(String msg){
		String[] chaine = msg.split(":");
		String message="";
		if(this.connectes.containsKey(chaine[0])){
		}
		else{
			if(msg != "Establishing connection. Please wait ..." && msg != "Connected\n"){
				this.connectes.put(chaine[0],new Color((float)Math.random(),(float)Math.random(),(float)Math.random()));
				addCo(msg);
			}
		}
			if(msg != "Establishing connection. Please wait ..." && msg != "Connected\n"){
				appendString(msg + "\n",this.connectes.get(chaine[0]));
			}
			else{
				appendString(msg + "\n",Color.RED);
			}

	}

    public void getParameters(){
			serverName = txIP.getText();
      serverPort = txPort.getText();
		}

}
