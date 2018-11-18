/*
 * Programme pour processus navire-amiral :
 */

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <mer.h>
#include <bateaux.h>
#include <assert.h>
#include <signal.h>
#include <wait.h>


/*
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */
#define NB_LIGNES 5
#define NB_COLONNES 5
#define NB_BATEAUX 26
char Nom_Prog[256] ;
char marqueActuelle = 'A';
char marqueDetruite = '*';

int fd;
int nbBateaux = 0;
int init = 1;
int nbBateauxTotal = 0;
int nbBateauxMax = NB_COLONNES * NB_LIGNES / 4;

bateau_t * flotte[NB_BATEAUX];

/*
 * FONCTIONS LOCALES
 */
void hand_switch(int sig, siginfo_t * info, void * context){

	printf("\e[1;1H\e[2J");
	mer_afficher(fd);
	
	static int turn=0;
	int pid = info->si_pid;
	assert(turn <80) ;
	turn++;
	
	bateau_t * bateau = NULL;
	booleen_t deplacement = VRAI ;
	coords_t * listeVoisins = NULL ;
	booleen_t success;
	coord_t target;
	int i;
	int insert = 0;

	for(i = 0; i<nbBateaux && bateau == NULL; i++){
		if(flotte[i] != NULL && flotte[i]->pid == pid)
			bateau = flotte[i];

	}
		/************************LE BATEAU EXISTE DEJA***********************/
	if(bateau != NULL){
		sleep(1);
		//kill(pid,SIGALRM);
		printf("\nBateau n°%i\n\n", pid);
		/*Fin de partie*/
		if(nbBateaux == 1 && !init){
			printf("Fin de partie, bateau %i vainqueur\n",pid);
			kill(pid, SIGKILL);
			exit(0);
		}

		if(init && nbBateaux !=0){
			//L'initialisation est faite
			init = 0;
		}


		booleen_t hit;

		mer_bateau_est_touche(fd, bateau, &hit);

			/*Bateau détruit*/
		if(hit == VRAI){
			bateau->marque=marqueDetruite;
			mer_bateau_couler(fd, bateau);
			bateau_destroy(&bateau);
			kill(pid, SIGKILL);
			
			mer_nb_bateaux_ecrire(fd, --nbBateaux);
			
			
		} else {
				if(bateau != NULL && marqueDetruite != bateau->marque) {
				/***********************DEPLACEMENT**************************/
					mer_voisins_rechercher(fd, bateau, &listeVoisins);

					mer_bateau_deplacer(fd, bateau, listeVoisins, &deplacement );

					kill(pid, SIGRTMIN+5);//Retrait d'énergie
					
					/************************TIR*********************************/
					mer_bateau_cible_acquerir(fd, bateau, &success, &target);
					if(success == VRAI){
						mer_bateau_cible_tirer(fd, target);
					}
				}
				else{ >
					printf("\e[1;1H\e[2J");
					mer_afficher(fd);
					printf("\nFin de partie, bateau %i vainqueur\n",pid);
					kill(pid, SIGKILL);
					exit(0); 
				}
			}

	} else {
		/************************CREATION D'UN BATEAU*******************/
		if(nbBateauxTotal < nbBateauxMax) {
			for(i=0; i<NB_BATEAUX && !insert; i++){
				if(flotte[i] == NULL){
					bateau = bateau_new(NULL, marqueActuelle, pid);
					mer_bateau_initialiser(fd, bateau);
					marqueActuelle++;
					flotte[i] = bateau;
					mer_nb_bateaux_ecrire(fd, ++nbBateaux);
					nbBateauxTotal++;
					insert++;
				}

			}
		} else {
		Webma	kill(pid, SIGKILL);
		}
	}
}

/*
 * Programme Principal
 */
int
main( int nb_arg , char * tab_arg[] )
{
     char fich_mer[128] ;
     struct sigaction sig;
     sigemptyset(&sig.sa_mask);
     sigaddset(&sig.sa_mask, SIGRTMIN+1);
     sig.sa_flags=SA_SIGINFO;
     sig.sa_sigaction=hand_switch;


    	/*Signaux Utilisés*/
    	sigaction(SIGRTMIN+1,&sig,NULL);// C'est mon tour ?

    	//sigaction(SIGRTMIN+5,&sig);//Retrait d'énergie




    /*
      * Capture des parametres
      */

     if( nb_arg != 2 )
     {
	  fprintf( stderr , "Usage : %s <fichier mer> \n",
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( Nom_Prog , tab_arg[0] );
     strcpy( fich_mer , tab_arg[1] );

     /*
      * Affichage pid bateau amiral
      */



     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());


     mer_initialiser(fich_mer, NB_COLONNES, NB_LIGNES);

	fd = open(fich_mer, O_RDWR, 0666);
	mer_afficher(fd);
	printf(" PID bateau amiral = %d\n" , getpid() ) ;
	 while(1){
	 	
	 }




	 printf("\n\n\t----- Fin du jeu -----\n\n");

	 close(fd);

	 exit(0);
}
