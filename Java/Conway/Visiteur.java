/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Mar 20 11:53:26 CET 2018
*
*/
public abstract class Visiteur {
	JeuDeLaVie jeu;
	public Visiteur(JeuDeLaVie j){
		jeu = j;
	}
	public abstract void visiteCelluleVivante(Cellule cell);
	public abstract void visiteCelluleMorte(Cellule cell);
}