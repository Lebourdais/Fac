#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif

#include <msg_messages.h>
#define CLE_BAL 42
int
main( int nb_arg , char * tab_arg[] )
{
     char nomprog[128] ;

     /*-----*/

     if( nb_arg !=1 )
       {
	 fprintf( stderr , "%s - Recepteur dans la communication par paquet\n\n" , tab_arg[0] );
	 fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	 exit(-1);
       }
     strcpy( nomprog , tab_arg[0] );
      int id_bal;
      message_t recu;
      int i;
      struct timeval debut, fin, temps;
      float duree , duree_transmission, debut_transmission, fin_transmission;

        id_bal = msgget(CLE_BAL, IPC_CREAT | IPC_EXCL | 0666);//Création BaL

          gettimeofday(&debut, NULL);  //Temps avant récéption

          for(i = 0; i < MESSAGES_NB; i ++){ // Reception des messages
              msgrcv(id_bal, &recu, sizeof(corps_t), MSG_TYPE_RECEPTEUR, 0);
          }

          gettimeofday(&fin, NULL);   // Temps après récéption

          timersub(&fin, &debut, &temps);
          duree = temps.tv_sec + (temps.tv_usec / 1000000);

          printf("Fin de la reception\n");

          msgrcv(id_bal, &recu, sizeof(corps_t), MSG_TYPE_RECEPTEUR, 0);

          debut_transmission = strtod(recu.corps.buffer, NULL); //String -> Double

          fin_transmission = fin.tv_sec + (fin.tv_usec / 1000000);
          duree_transmission = fin_transmission - debut_transmission;

          printf("La durée de récéption est %.3f secondes\n\n", duree);
          printf("La duree de transmission est de %.3f secondes\n\n", duree_transmission);

        msgctl(id_bal, IPC_RMID, 0);//Destruction BaL

          exit(0);
     }/*Fin du main*/
