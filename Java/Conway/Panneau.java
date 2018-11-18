/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Mar 21 18:25:18 CET 2018
*
*/
import javax.swing.*;
import java.awt.*;
public class Panneau extends JPanel {

	JeuDeLaVie jeu;
	public Panneau(JeuDeLaVie j){
		this.jeu = j;
	}
	public void paintComponent(Graphics g){
		g.setColor(Color.BLACK);
		g.fillRect(0,0,1100,700);
		for(int x=0;x<jeu.getxMax();x++)
			for(int y=0;y<jeu.getyMax();y++)
				if(jeu.getGrilleXY(x,y).estVivante()){
					g.setColor(Color.GREEN);
					g.fillOval(x*10+50,y*10+50,10,10);
				}
	}
}