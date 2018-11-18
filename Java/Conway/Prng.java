/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Apr 04 09:05:09 CEST 2018
*
*/
public class Prng implements Observateur {
	JeuDeLaVie jeu;
	int iteration;
	public Prng(JeuDeLaVie j){
		this.jeu = j;
		
	}
	
	public void actualise(){
		int num=0;
		for(int x=0;x<jeu.getxMax();x++)
			for(int y=0;y<jeu.getyMax();y++)
				if(jeu.getGrilleXY(x,y).estVivante()){
					num= (num+1)%2;
				}
		iteration++;
		System.out.println(num);
	}
}