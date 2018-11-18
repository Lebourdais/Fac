/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Mar 20 10:01:38 CET 2018
*
*/
public class CelluleEtatVivant implements CelluleEtat{
	public static CelluleEtatVivant vivantuniq;
	private CelluleEtatVivant(){}
	
	public static CelluleEtatVivant getInstance(){
		if (vivantuniq == null){
			vivantuniq = new CelluleEtatVivant();
		}
		return vivantuniq;
	}
	public CelluleEtat vit(){
		return this;
	}
	public CelluleEtat meurt(){
		return CelluleEtatMort.getInstance();
	}
	public boolean estVivante(){
		return true;
	}
	public void accept(Visiteur visiteur, Cellule cell){
		visiteur.visiteCelluleVivante(cell);
	}
}