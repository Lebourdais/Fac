/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Mar 20 09:06:04 CET 2018
*
*/
public class Cellule {
	private CelluleEtat etat; //true vivant / false mort
	private int x;
	private int y;
	public Cellule(CelluleEtat state,int px,int py){
		this.etat = state;
		this.x = px;
		this.y = py;
	}
	public boolean estVivante(){
		return etat.estVivante();
	}
	public void vit(){
		etat = etat.vit();
	}
	public void meurt(){
		etat = etat.meurt();
	}
	public int nombreVoisineVivantes(JeuDeLaVie jeu){
		int nbVoisins = 0;
		for(int i=x-1;i<=x+1;i++){
			for(int j=y-1;j<=y+1;j++){				
				if (i>=0 && i<jeu.getxMax() && j>=0 && j<jeu.getyMax())
					if (jeu.getGrilleXY(i,j).estVivante())
						nbVoisins++;
			}
		}
		if(this.estVivante())
			nbVoisins --;
			
		return nbVoisins;
	}
	public void accept(Visiteur visiteur){
		etat.accept(visiteur,this);
	}
	
}