/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Mar 20 11:12:25 CET 2018
*
*/
public interface Observable {
	void attacheObservateur(Observateur o);
	void detacheObservateur(Observateur o);
	void notifieObservateurs();
}