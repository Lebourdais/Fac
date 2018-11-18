/*
 * Programme pour processus navire :
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <mer.h>
#include <bateaux.h>

/*
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */
int Energie;


/*
 * Handlers
 */
 void hand_switch(int sig){
   printf("Bug handler navire\n");
 	Energie-=(15/100*Energie);//Le bateau s'est déplacé
 }
/*
 * Programme Principal
 */

int
main( int nb_arg , char * tab_arg[] )
{
  char nomprog[128] ;
  pid_t pid_amiral ;
  pid_t pid_bateau = getpid()  ;

  /*----------*/

  /*
   * Capture des parametres
   */

  if( nb_arg != 2 )
    {
      fprintf( stderr , "Usage : %s <pid amiral>\n",
	       tab_arg[0] );
      exit(-1);
    }

  /* Nom du programme */
  strcpy( nomprog , tab_arg[0] );
  sscanf( tab_arg[1] , "%d" , &pid_amiral ) ;

  /* Initialisation de la generation des nombres pseudo-aleatoires */
  srandom((unsigned int)pid_bateau);


  /* Affectation du niveau d'energie */
  Energie = random()%BATEAU_MAX_ENERGIE ;

  printf( "\n\n--- Debut bateau [%d]---\n\n" , pid_bateau );

  /*
   * Deroulement du jeu
   */

   struct sigaction sig;
  sig.sa_flags = 0;
  sig.sa_handler = hand_switch;
  sigaction(SIGRTMIN+5, &sig, NULL);

  while(Energie>0){

    kill(pid_amiral, SIGRTMIN+1);
    sleep(2);
}

  printf( "\n\n--- Arret bateau (%d) ---\n\n" , pid_bateau );

  exit(0);
}
