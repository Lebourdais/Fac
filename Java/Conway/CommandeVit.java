/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Mar 20 11:44:15 CET 2018
*
*/
public class CommandeVit extends Commande{
	public CommandeVit(Cellule c){
		super(c);
	}
	public void executer(){
		cell.vit();
	}
}