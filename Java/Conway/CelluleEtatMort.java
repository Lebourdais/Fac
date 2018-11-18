/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Mar 20 10:03:56 CET 2018
*
*/
public class CelluleEtatMort implements CelluleEtat{
	public static CelluleEtatMort mortuniq;
	private CelluleEtatMort(){}
	
	public static CelluleEtatMort getInstance(){
		if (mortuniq == null){
			mortuniq = new CelluleEtatMort();
		}
		return mortuniq;
	}
	
	public CelluleEtat vit(){
		return CelluleEtatVivant.getInstance();
	}
	public CelluleEtat meurt(){
		return this;
	}
	public boolean estVivante(){
		return false;
	}
	public void accept(Visiteur visiteur, Cellule cell){
		visiteur.visiteCelluleMorte(cell);
	}
}