/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Mar 20 09:58:18 CET 2018
*
*/
public interface CelluleEtat {
	public CelluleEtat vit();
	public CelluleEtat meurt();
	public boolean estVivante();
	public void accept(Visiteur visiteur, Cellule cell);
}