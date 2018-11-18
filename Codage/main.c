#include <stdio.h>
#include <stdlib.h>
#include "emetteur.h"
//#include "recepteur.c"
//#include "canal.h"



int main(void){

	int taille=0;
	char message[20];

	int encodage[200]={0};
	int decodage[20];
	
	int i;	
	int nbuser;
	int user=0;
	printf("Entrez un nombre de users : ");
	scanf("%i",&nbuser);
	printf("\n");
	int tranche=Tranche(nbuser);
	
	while(user != -1){
		printf("Qui envoi le message ? (numéro d'user, -1 pour arreter la saisie): ");
		scanf("%i",&user);
		if (user != -1){
			printf("\n");
			printf("Quel est le message :\n");
			getchar();
			fgets(message,20,stdin);	
					
			etalement(nbuser,user,encodage,message);			
		}	
	}
	printf("Le message après encodage et addition des sources est : \n");
	for (i=0;i<taille*pow(2,tranche);i++)
		printf("%3i",encodage[i]);		
	printf("\n");
	
/*	printf("Veuillez rentrez l'utilisateur que vous souhaitez décoder");
	scanf("%i",&user);
	
	Recepteur(nbuser,encodage,decodage,user,taille*pow(2,tranche));
	
	printf("\nLe message de l'utilisateur %i est :\n",user);
	for (i=0;i<taille;i++)
		printf("%3i",decodage[i]);
	printf("\n");*/
	
	exit(0);
}
			