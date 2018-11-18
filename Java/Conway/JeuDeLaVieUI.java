/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Mar 20 11:14:16 CET 2018
*
*/
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.event.*;
import java.util.*;

public class JeuDeLaVieUI extends JFrame implements Observateur {
	JPanel container;
	Panneau pan;
	JTextField regle = new JTextField();
	JButton boutonGo = new JButton("Go");
	JButton boutonStop = new JButton("Stop");
	JButton boutonGenS = new JButton("Gen suivante");
	JButton changerRegle = new JButton("Regle");
	JSlider vitesse = new JSlider(JSlider.HORIZONTAL,10,1000,500);
	Visiteur v;
	private boolean animated = true;
	private JeuDeLaVie jeu;
	private Thread t;
	public JeuDeLaVieUI(JeuDeLaVie j){
		super();
		this.jeu = j;
		this.pan = new Panneau(j);
		this.container = new JPanel();
		this.setSize(1100,700);
		this.vitesse.addChangeListener(new SliderListener());
		vitesse.setMajorTickSpacing(50);
		vitesse.setMinorTickSpacing(10);
		
		vitesse.setInverted(true);
		Hashtable labelTable = new Hashtable();
		labelTable.put(new Integer(2000),new JLabel("Lent"));
		labelTable.put(new Integer(50),new JLabel("Rapide"));
		vitesse.setLabelTable(labelTable);
		vitesse.setPaintLabels(true);
		
		this.getContentPane().setBackground(Color.BLACK);
		
		container.setLayout(new BorderLayout());
		container.add(pan, BorderLayout.CENTER);
		JPanel south = new JPanel();
		south.setLayout(new GridLayout(1,3));
		JPanel ssouth = new JPanel();
		ssouth.setLayout(new GridLayout(2,1));
		
		boutonGo.addActionListener(new BoutonGoListener());
		boutonStop.addActionListener(new BoutonStopListener());
		boutonGenS.addActionListener(new BoutonGenSListener());
		changerRegle.addActionListener(new BoutonChangerRegle());
		boutonStop.setEnabled(false);
		changerRegle.setEnabled(false);
		south.add(boutonGo);
		south.add(boutonStop);
		v = new VisiteurNouveau(jeu,2,3,3);
		south.add(boutonGenS);
		south.add(regle);
		south.add(changerRegle);
		ssouth.add(south);
		ssouth.add(vitesse);
		
		container.add(ssouth,BorderLayout.SOUTH);
		this.setContentPane(container);
		this.setVisible(true);
		
	}
	public void go(){
		while (this.animated){	 	
	 		this.jeu.calculerGenerationSuivante(this.v);
	 		try{
	 		Thread.sleep(jeu.time);
	 		}
	 		catch(InterruptedException ie){
	 			ie.printStackTrace();
	 		}
		}
	}
	public void actualise(){
		pan.repaint();
	}
	public class BoutonGoListener implements ActionListener{
		public void actionPerformed(ActionEvent arg0){
			animated = true;
			t = new Thread(new Lancer());
			t.start();
			boutonGo.setEnabled(false);
			boutonStop.setEnabled(true);
			boutonGenS.setEnabled(false);
		}
	}
	
	public class BoutonStopListener implements ActionListener{
		public void actionPerformed(ActionEvent arg0){
			animated = false;
			boutonGo.setEnabled(true);
			boutonStop.setEnabled(false);
			boutonGenS.setEnabled(true);
			changerRegle.setEnabled(true);
		}
	}
	public class BoutonGenSListener implements ActionListener{
		public void actionPerformed(ActionEvent arg0){
			jeu.calculerGenerationSuivante(v);
		}
	}
	public class BoutonChangerRegle implements ActionListener{
		public void actionPerformed(ActionEvent arg0){
			String newregle = regle.getText();
			v = new VisiteurNouveau(jeu,Integer.parseInt(newregle.split("-")[0]),Integer.parseInt(newregle.split("-")[1]),Integer.parseInt(newregle.split("-")[2]));
		}
	}
	public class Lancer implements Runnable{
		public void run(){
			go();
		}
	}
	public class SliderListener implements ChangeListener{
		public void stateChanged(ChangeEvent e){
			JSlider source = (JSlider)e.getSource();
			if (!source.getValueIsAdjusting()){
				int temps = source.getValue();
				jeu.setTime(temps);
			}
		}
	}
	
}