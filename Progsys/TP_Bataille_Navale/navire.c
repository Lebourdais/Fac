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
  pid_t pid_amiral ;
  pid_t pid_bateau;

/*
 * Handlers
 */
 void hand_switch(int sig){
 	Energie-=(25/100*BATEAU_MAX_ENERGIE);//Le bateau s'est déplacé
 }
 /*void bateau_fantome(int sig, siginfo_t * info, void * context){
 	int pid=info->si_pid;
 	if ( pid == pid_amiral){
 		
 	}
 	else {
 		kill(pid_bateau,SIGKILL);
 	}
 	
 }*/
/*
 * Programme Principal
 */

int
main( int nb_arg , char * tab_arg[] )
{
  char nomprog[128] ;


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
	pid_t pid_bateau = getpid()  ;
  printf( "\n\n--- Debut bateau [%d]---\n\n" , pid_bateau );

  /*
   * Deroulement du jeu
   */

   struct sigaction sig;
  sig.sa_flags = 0;
  sig.sa_handler = hand_switch;
  
  sigaction(SIGRTMIN+5, &sig, NULL);
  
 /* struct sigaction alrm;
  alrm.sa_sigaction = bateau_fantome;
  alrm.sa_flags=SA_SIGINFO;
  sigaction(SIGALRM, &alrm, NULL);*/

  while(Energie>0){  
	//alarm(8);
		
    kill(pid_amiral, SIGRTMIN+1);
    sleep(2);
}
	
  printf( "\n\n--- Arret bateau (%d) ---\n\n" , pid_bateau );

  exit(0);
}
