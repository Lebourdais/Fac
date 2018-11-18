/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Mar 20 11:55:39 CET 2018
*
*/
public class VisiteurClassique extends Visiteur{
	JeuDeLaVie jeu;
	public VisiteurClassique(JeuDeLaVie j){
		super(j);
		this.jeu = j;
	}
	public void visiteCelluleVivante(Cellule cell){
		int nbVoisins = cell.nombreVoisineVivantes(jeu);
		if (nbVoisins<2 || nbVoisins > 3){
			jeu.ajouteCommande(new CommandeMeurt(cell));
		}
	}
	public void visiteCelluleMorte(Cellule cell){
		int nbVoisins = cell.nombreVoisineVivantes(jeu);
		if (nbVoisins==3){
			jeu.ajouteCommande(new CommandeVit(cell));
		}
	}
}