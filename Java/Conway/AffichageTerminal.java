/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Thu Mar 22 08:30:02 CET 2018
*
*/

public class AffichageTerminal implements Observateur {

	JeuDeLaVie jeu;
	int iteration;
	public AffichageTerminal(JeuDeLaVie j){
		this.jeu = j;
		this.iteration = 0;
	}
	
	public void actualise(){
		int nbCellVivante=0;
		for(int x=0;x<jeu.getxMax();x++)
			for(int y=0;y<jeu.getyMax();y++)
				if(jeu.getGrilleXY(x,y).estVivante()){
					nbCellVivante++;
				}
		iteration++;
		System.out.println("Au Tour "+iteration+" il y a "+nbCellVivante+" cellules vivantes.");
	}
}