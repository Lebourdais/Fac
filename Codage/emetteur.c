#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TAILLE 64

int H[TAILLE][TAILLE];
int Tranche(int nbuser){

	int degre;
	
	for (degre=0;pow(2,degre)<nbuser;degre++){
		
	}

	return degre;


int generer_matrice(int old_mat[TAILLE][TAILLE],int n,int size,int size_old){

	int ligne;
	int colonne;
	if (n==0) return 0;

	int indice=0;

	for (ligne=0;ligne<size_old;ligne++){
		for (int i=0;i<2;i++){
			for (colonne=0;colonne<size_old;colonne++){
				H[ligne][colonne+size_old*i]=old_mat[ligne][colonne];
			}
		}

	}

	for (ligne=size_old;ligne<size;ligne++)
		for (colonne=0;colonne<size_old;colonne++)
				H[ligne][colonne]=old_mat[ligne-size_old][colonne];



	for (ligne=size_old;ligne<size;ligne++){
		for (colonne=size_old;colonne<size;colonne++){
			H[ligne][colonne]=old_mat[ligne-size_old][colonne-size_old]*-1;

		}
	}

	for (ligne=0;ligne<size;ligne++){
		for (colonne=0;colonne<size;colonne++)
			old_mat[ligne][colonne]=H[ligne][colonne];
	}

	return generer_matrice(old_mat,n-1,size*2,size);
}

int etalement (int nbuser,int user,int encodage[200],char message[20]){
			
			int taille = strlen(message)-1;
			int indice=0;
			int cpt=0;
			int code[200];
			int i;
			H[0][0]=1;
			H[1][1]=-1;
			H[1][0]=1;
			H[0][1]=1;
			int tranche = Tranche(nbuser);
			int imessage[20];	
			if (nbuser>2){
			generer_matrice(H,tranche,4,2);
			}
			
			for (i=0;i<taille;i++)
				if (message[i]=='0') imessage[i]=-1;//BON
				else imessage[i]=1;
	
								  
			for (i=0;i<taille;i++){
				for (cpt=0;cpt<pow(2,tranche);cpt++){
					code[indice++]=(H[user-1][cpt]*imessage[i]);
				}		
			}				
			for (i=0;i<taille*pow(2,tranche);i++){
				
				encodage[i]=encodage[i]+code[i];
				
			}
			return 0;
}