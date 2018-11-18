/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Mar 20 10:10:33 CET 2018
*
*/
import java.util.*;
import java.util.stream.*;
import java.lang.*;
import java.io.*;
import java.nio.file.*;
public class JeuDeLaVie {
	private Cellule[][] grille ;
	int xMax;
	int yMax;
	int time;
	Visiteur visiteur;
	private List<Observateur> observateurs;
	private List<Commande> commandes;
	 public JeuDeLaVie(){
	 	this.xMax = 100;
	 	this.yMax = 60;
	 	this.grille = new Cellule[xMax][yMax];
	 	this.observateurs = new ArrayList<Observateur>();
	 	this.commandes = new ArrayList<Commande>();
	 	this.time = 400;
	 }

	 public void initialiseGrille(){
	 	for (int i = 0;i<xMax;i++){
	 		for (int j = 0;j<yMax;j++){
	 			grille[i][j] = new Cellule((Math.random()> 0.7?CelluleEtatVivant.getInstance():CelluleEtatMort.getInstance()),i,j);
	 		}
	 	}	 	
	 }
	 public void initGrilleFic(String f){
	 	List<String> fic = new ArrayList<String>();
	 	try (Stream stream = Files.lines(Paths.get(f))) {
			stream.forEach(x -> fic.add((String)x));

		} catch (IOException e) {
			e.printStackTrace();
		}
		
		for (String e : fic){
			String[] parts = e.split("-");
			grille[Integer.parseInt(parts[0])][Integer.parseInt(parts[1])]= new Cellule(CelluleEtatVivant.getInstance(),Integer.parseInt(parts[0]),Integer.parseInt(parts[1]));
			for (int i = 0;i<xMax;i++){
		 		for (int j = 0;j<yMax;j++){
		 			if (grille[i][j] == null)
		 				grille[i][j] = new Cellule(CelluleEtatMort.getInstance(),i,j);
		 		}
	 	}	 
		}
	 }
	 public void setTime(int t){
	 	this.time = t;
	 }
	 public int time(){
	 	return this.time;
	 }
	 public int getxMax(){
	 	return xMax;
	 }
	 public int getyMax(){
	 	return yMax;
	 }
	 public Cellule getGrilleXY(int x, int y){
	 	return grille[x][y];
	 }
	 public void attacheObservateur(Observateur o){
	 	observateurs.add(o);
	 }
	  public void detacheObservateur(Observateur o){
	 	observateurs.remove(o);
	 }
	 public void notifieObservateur(){
	 	observateurs.stream()
	 				.forEach(x->x.actualise());
	 }
	 public void ajouteCommande(Commande c){
	 	this.commandes.add(c);
	 }
	 public void executeCommande(){
	 	commandes.stream()
	 				.forEach(x->x.executer());
	 	commandes.clear();
	 }
	 public void distribueVisiteur(Visiteur v){
	 	Arrays.stream(grille)
	 		.flatMap(x->Arrays.stream(x))
	 		.forEach(x->x.accept(v));	 	
	 }
	 public void calculerGenerationSuivante(Visiteur v){
	 	distribueVisiteur(v);
	 	executeCommande();
	 	notifieObservateur(); 	
	 }
	 public static void main(String[] args){
	 	JeuDeLaVie jeu = new JeuDeLaVie();
	 	jeu.initialiseGrille();
	 	JeuDeLaVieUI jeuUI= new JeuDeLaVieUI(jeu);
	 	Observateur affTerm = new AffichageTerminal(jeu);
	 	Observateur rand = new Prng(jeu);
	 	jeu.attacheObservateur(jeuUI);
	 	jeu.attacheObservateur(affTerm);
	 	jeu.attacheObservateur(rand);
	 	
	 	
	 }
}