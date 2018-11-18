#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include "messages.h"
#include <signal.h>

key_t cleExterne;

void hand_switch(int sig){

  int nBaL = msgget(cleExterne, 0);
  printf("Signal reçu\n");
  requete_t coureur;
	coureur.corps.dossard = getpid();// Affectation du num au coureur
	coureur.type = PC_COURSE;// Adresse du serveur
  coureur.corps.etat= ABANDON;
  msgsnd(nBaL, &coureur, sizeof(corps_requete_t), 0);

  reponse_t reponse;
	reponse.corps.compte_rendu=ABANDON_ACK; // Le serveur a noté l'abandon

  msgrcv(nBaL, &reponse, sizeof(corps_reponse_t), getpid(), 0);
  printf("Abandon pris en compte \n");
  exit(0);
}

int main(int argc, char * argv[]) {

  if(argc != 2) {
		printf("Nombre d'argument incorect, Usage%s : <cle externe>\n", argv[0]);
		exit(0);
	}
  struct sigaction sig;
  sig.sa_handler=hand_switch;
  sigaction(SIGINT,&sig,NULL);

	cleExterne = atoi(argv[1]);
  int nBaL = msgget(cleExterne, 0);// Numéro de la boite aux lettres
	//Requete envoyée par le coureur
	requete_t coureur;
	coureur.corps.dossard = getpid();// Affectation du num au coureur
	coureur.corps.etat=EN_COURSE;
	coureur.type = PC_COURSE;// Adresse du serveur

	//Reponse du serveur
	reponse_t reponse;
	reponse.corps.etat = EN_COURSE; // Le coureur court toujours



	messages_initialiser_attente(); //A mettre avant messages_attendre_tour)

	while(reponse.corps.etat == EN_COURSE) {
		
		msgsnd(nBaL, &coureur, sizeof(corps_requete_t), 0); // Envoi de la requete au serveur

		msgrcv(nBaL, &reponse, sizeof(corps_reponse_t), getpid(), 0); // On attend sa réponse(bloquant)
		system("clear");
		messages_afficher_etat(reponse.corps.etat) ; //Actualiser l'état


	
		messages_afficher_reponse(&reponse);

	
		messages_afficher_parcours(&reponse);

	
		messages_attendre_tour();
	}
	
}
