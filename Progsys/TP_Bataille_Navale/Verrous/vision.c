#include <stdio.h>
#include <commun.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include <mer.h>

#define LIGNES 5
#define COLONNES 5

int HeaderVerrou(int fd) {
	// Regarde si le header du fichier mer est verrouille
	struct flock lock;

	lock.l_whence = 0;
	lock.l_start = 0;
	lock.l_len = MER_TAILLE_ENTETE;

	fcntl(fd, F_GETLK, &lock);

	if(lock.l_type == F_RDLCK || lock.l_type == F_WRLCK) {
		return 1;
	} else {
		return 0;
	}
}

int ModifRecente(char * nomFichier) {

	struct stat Stat;
	stat(nomFichier, &Stat);

	return ((time(NULL) - Stat.st_mtime) < 1);//Il a été modifié
}

/*--------------------*
 * Main demon
 *--------------------*/
int
main( int nb_arg , char * tab_arg[] )
{
	char fich_mer[128] ;
	char nomprog[256] ;

	/*----------*/

	if( nb_arg != 2 )
	{
		fprintf( stderr , "Usage : %s <fichier mer>\n",
			 tab_arg[0] );
		exit(-1);
	}

	strcpy( nomprog , tab_arg[0] );
	strcpy( fich_mer , tab_arg[1] );

	time_t derniereModif = time(NULL);
	int fd;								// Descripteur du fichier mer
	int fin = 0;						
	int initFait = 0;
	int nbBateaux;


	printf("\n%s : ----- Debut de l'affichage de la mer ----- \n", nomprog );

	mer_initialiser(tab_arg[1], LIGNES, COLONNES);

	fd = open( fich_mer , O_RDONLY | O_CREAT , 0666);
	mer_afficher(fd);

	while(!fin || !initFait) {
		if(ModifRecente(tab_arg[1]) && derniereModif != time(NULL)) {
			while(HeaderVerrou(fd));//On vérifie qu'un bateau n'est pas en train de bouger
			mer_afficher(fd);
			derniereModif = time(NULL);
			mer_nb_bateaux_lire(fd, &nbBateaux);
			initFait = (nbBateaux >= 2);
			fin = (nbBateaux == 1);
		}
	}

	close(fd);

	printf("\n%s : --- Arret de l'affichage de la mer ---\n", nomprog );

	exit(0);
}
