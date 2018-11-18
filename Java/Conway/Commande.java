/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Mar 20 11:43:06 CET 2018
*
*/
public abstract class Commande {
	Cellule cell;
	public Commande(Cellule c){
		this.cell = c;
	}
	public abstract void executer();
}