#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <msg_messages.h>
#define CLE_BAL 42
int
main( int nb_arg , char * tab_arg[] )
{
     char nomprog[128] ;

     /*-----*/

     if( nb_arg !=1 )
       {
	 fprintf( stderr , "%s - Emetteur dans la communication par paquet\n\n" , tab_arg[0] );
	 fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	 exit(-1);
       }
     strcpy( nomprog , tab_arg[0] );

     int i;
     int id_bal;
     message_t envoi;
     struct timeval debut, fin, temps;
     float duree, debut_transmission;
    id_bal = msgget(CLE_BAL, 0666); // Récupération de la BaL

    msg_remplir(&envoi, 'a');

    gettimeofday(&debut, NULL);//Temps avant l'envoi


     for(i = 0; i < MESSAGES_NB; i ++){
        msgsnd(id_bal, &envoi, sizeof(corps_t), 0); // Envoi des messages
     }

     gettimeofday(&fin, NULL); // Temps après l'envoi

     timersub(&fin, &debut, &temps);//Récupération de la durée d'envoi
     duree = temps.tv_sec + (temps.tv_usec /1000000);

     debut_transmission = debut.tv_sec + (debut.tv_usec /1000000);
     sprintf(envoi.corps.buffer, "%f", debut_transmission);//Création d'un message avec la date de début
     msgsnd(id_bal, &envoi, sizeof(corps_t), 0);


     printf("La duree d'emission est : %.3f secondes\n\n", duree);


     exit(0);
}
