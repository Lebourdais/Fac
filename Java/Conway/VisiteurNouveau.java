/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Apr 04 09:46:43 CEST 2018
*
*/
public class VisiteurNouveau extends Visiteur{
	JeuDeLaVie jeu;
	int vivantmin;
	int vivantmax;
	int rez;
	public VisiteurNouveau(JeuDeLaVie j,int vmin,int vmax,int r){
		super(j);
		this.jeu = j;
		this.vivantmin = vmin;
		this.vivantmax = vmax;
		this.rez = r;
	}
	public void visiteCelluleVivante(Cellule cell){
		int nbVoisins = cell.nombreVoisineVivantes(jeu);
		if (nbVoisins<this.vivantmin || nbVoisins > this.vivantmax){
			jeu.ajouteCommande(new CommandeMeurt(cell));
		}
	}
	public void visiteCelluleMorte(Cellule cell){
		int nbVoisins = cell.nombreVoisineVivantes(jeu);
		if (nbVoisins==this.rez){
			jeu.ajouteCommande(new CommandeVit(cell));
		}
	}
}