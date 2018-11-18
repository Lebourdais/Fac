/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Mar 20 11:45:42 CET 2018
*
*/
public class CommandeMeurt extends Commande {
	public CommandeMeurt(Cellule c){
		super(c);
	}
	public void executer(){
		cell.meurt();
	}
}