#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* fcntl */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> /* errno */
#include <string.h>

#include <bateau.h>
#include <mer.h>

#define Lock 1
#define Unlock 0
#define NB_MIN_BATEAUX 2

void Couler(int fd, int * nbBateaux, bateau_t * bateau) {
	mer_nb_bateaux_ecrire(fd, --(*nbBateaux));
	bateau_destroy(&bateau);
}

int LockAll(const int fd, bateau_t * bateau, int verrouiller) {
	// Verrouille tout
	struct flock lock;

	lock.l_whence = 0;
	lock.l_start = 0;
	lock.l_len = 0;

	if(verrouiller) {
		lock.l_type = F_WRLCK;

	} else {
		lock.l_type = F_UNLCK;

	}

	fcntl(fd, F_SETLKW, &lock);


	return CORRECT;
}

int ShieldLock(const int fd, bateau_t * bateau, int verrouiller) {
	// Verrouille les cases appartenant au bateau
	int i;
	coords_t * bateauCellules = bateau_corps_get(bateau);
	coord_t * bateauCellule = bateauCellules->coords;

	struct flock lock;

	lock.l_whence = 0;
	lock.l_len = MER_TAILLE_CASE;

	if(verrouiller) {
		lock.l_type = F_WRLCK;
	} else {
		lock.l_type = F_UNLCK;
	}

	for(i = 0; i < bateauCellules->nb; i++) {
		lock.l_start = bateauCellule[i].pos;

		fcntl(fd, F_SETLKW, &lock);
	}

	return CORRECT;
}

int HeaderLock(const int fd, bateau_t * bateau, int verrouiller) {
	struct flock lock;

	lock.l_whence = 0;
	lock.l_start = 0;
	lock.l_len = MER_TAILLE_ENTETE;

	if(verrouiller) {
		lock.l_type = F_WRLCK;
	} else {
		lock.l_type = F_UNLCK;
	}

	if (fcntl(fd, F_SETLKW, &lock) == -1) {
		return 0;
	}
	return 1;
}

int NeighborLock(int fd, bateau_t * bateau, coords_t listeVoisins, int verrouiller) {
	int i;
	case_t merCase;
	struct flock lock;

	lock.l_whence = 0;
	lock.l_len = 0;

	if(verrouiller) {
		lock.l_type = F_WRLCK;
	} else {
		lock.l_type = F_UNLCK;
	}

	for(i = 0; i < listeVoisins.nb; i++) {
		mer_case_lire(fd, listeVoisins.coords[i], &merCase);
		if(merCase == MER_CASE_LIBRE) {
			lock.l_start = listeVoisins.coords[i].pos;

			fcntl(fd, F_SETLK, &lock);


		}
    else {
      return ERREUR;
    }
	}

	return CORRECT;
}

int TargetLock(const int fd, bateau_t * bateau, coord_t cible, int verrouiller) {
	// Verrou pour le tir
	struct flock lock;

	lock.l_whence = 0;
	lock.l_start = cible.pos;
	lock.l_len = MER_TAILLE_CASE;

	if(verrouiller) {
		lock.l_type = F_WRLCK;
	} else {
		lock.l_type = F_UNLCK;
	}

	fcntl(fd, F_SETLKW, &lock);
}

/*
 *	Programme principal
 */


int main( int nb_arg , char * tab_arg[] ) {
	char fich_mer[128] ;
	case_t marque = MER_CASE_LIBRE ;
	char nomprog[128] ;
	float energie = 0.0 ;

	/*----------*/

	strcpy( nomprog , tab_arg[0] ) ;

	if( nb_arg != 4 )
		{
			fprintf( stderr , "Usage : %s <fichier mer> <marque> <energie>\n",
				 nomprog );
			exit(-1);
		}

	if( strlen(tab_arg[2]) !=1 )
		{
			fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
				 nomprog , tab_arg[2] );
			exit(-1) ;
		}


	strcpy( fich_mer , tab_arg[1]);
	marque = tab_arg[2][0] ;
	sscanf( tab_arg[3] , "%f" , &energie );

	/* Initialisation de la generation des nombres pseudo-aleatoires */
	srandom((unsigned int)getpid());



	printf( "\n\n%s : ----- Debut du bateau %c (%d) -----\n\n ",
	nomprog , marque , getpid() );

	/***********************INIT MER******************/
	bateau_t * bateau = BATEAU_NULL ;
	int nbBateaux = 0 ;
	int fd;


	fd = open( fich_mer , O_RDWR | O_CREAT , 0666);

	bateau	= bateau_new(NULL, marque, energie);

	/********************INIT BATEAU*****************/
	LockAll(fd, bateau, Lock);

	mer_bateau_initialiser(fd, bateau);

	mer_nb_bateaux_lire(fd, &nbBateaux);
	mer_nb_bateaux_ecrire(fd, ++nbBateaux);

	LockAll(fd, bateau, Unlock);

	/**********************INIT BOUCLIER************************/
	if(energie >= BATEAU_SEUIL_BOUCLIER) {
		ShieldLock(fd, bateau, 1);
	}

	booleen_t hit = FAUX;
	booleen_t deplacement = VRAI;
	booleen_t acquisition;
	coords_t * listeVoisins = NULL;
	coord_t cible;
	char bateauNom;

	while(1) {
		sleep((rand() % 4) + 2);

    /*****************RAFRAICHISSEMENT DES VARIABLES***************/
		bateauNom = bateau_marque_get(bateau);
		mer_bateau_est_touche(fd, bateau, &hit);
		mer_nb_bateaux_lire(fd, &nbBateaux);
    listeVoisins = coords_new(); //Penser à les supprimer
		mer_voisins_rechercher(fd, bateau, &listeVoisins);

		if(hit && energie < BATEAU_SEUIL_BOUCLIER) {
			printf("\n - Bateau %c : Destruction -\n", bateauNom);
			mer_nb_bateaux_ecrire(fd, --nbBateaux);
			mer_bateau_couler(fd, bateau);
			bateau_destroy(&bateau);
			close(fd);

			exit(0);
		}

		if(nbBateaux == 1) {
			// Fin de partie
			printf("\n - Bateau %c : Vainqueur -\n", bateauNom);
      sleep(1);
			close(fd);
			exit(0);
		}

		/********************* DEPLACEMENT*********************/
		if(energie > 0) {
			if(NeighborLock(fd, bateau, *listeVoisins, 1) == ERREUR) {
				// On verifie que les cases autour sont libres.
				printf("Le bateau ne peux pas se déplacer\n");
				deplacement = FAUX;
			} else {
				ShieldLock(fd, bateau, 0);
			}

			HeaderLock(fd, bateau, 1);//Lock du header

			mer_bateau_deplacer(fd, bateau, listeVoisins, &deplacement);
			energie -= BATEAU_MAX_ENERGIE * 0.05;

			HeaderLock(fd, bateau, 0);//Delock du header
		}

		if(energie >= BATEAU_SEUIL_BOUCLIER) {
			//Si y'a assez d'energie on remet les boucliers
			ShieldLock(fd, bateau, 1);
		}

		NeighborLock(fd, bateau, *listeVoisins, 0);//On delock les voisins


		coords_destroy(&listeVoisins);//On vide la listevoisin

		/**********************TIR SUR CIBLE**************************/

		mer_bateau_cible_acquerir(fd, bateau, &acquisition, &cible);

		if(acquisition) {
			if(TargetLock(fd, bateau, cible, 1) != ERREUR)  // On peut tirer
				TargetLock(fd, bateau, cible, 0);
			mer_bateau_cible_tirer(fd, cible);

			TargetLock(fd, bateau, cible, 0);
    }


	}



	printf( "\n\n%s : ----- Fin du navire %c (%d) -----\n\n ",
	nomprog , marque , getpid() );

	exit(0);
}
