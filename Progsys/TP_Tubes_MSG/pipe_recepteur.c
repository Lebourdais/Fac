#include <stdio.h>
#include <unistd.h>	/* close, read, write */
#include <stdlib.h>	/* exit */
#include <sys/types.h>	/*open */
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif
#include <pipe_messages.h>

int
main( int nb_arg , char * tab_arg[])
{
     char nomprog[128] ;


     /*-----*/
     strcpy( nomprog , tab_arg[0] );

     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s - Recepteur dans la communication par flot\n\n" , tab_arg[0] );
	  fprintf( stderr , "usage : %s \n" , nomprog );
	  exit(-1);
     }



     int fd_tube,fd_tube1;
     char * NomTube = "TP51";
     char poubelle[2048];
     struct timeval start,end,temps;
     if ((fd_tube=open(NomTube,O_RDONLY,0666)) == -1){
     	 perror("Problème en ouverture sur le tube nommé en lecture");
     	 exit(-2);
     }
      gettimeofday(&start,NULL);
     while(read(fd_tube,poubelle,MESSAGES_TAILLE));

     gettimeofday(&end,NULL);

     //pipe_afficher(poubelle);
     float Tempdepart;
     timersub(&end,&start,&temps);
     close(fd_tube);
     sleep(2);
     if ((fd_tube1=open("TubeRep",O_RDONLY,0666)) == -1){
     	 perror("Problème en ouverture sur le tube nommé en lecture");
     	 exit(-2);
     }
     while(read(fd_tube1, &Tempdepart,sizeof(float)));

     close(fd_tube1);

     float Temparr = end.tv_usec /1000000 + end.tv_sec;
     printf("Durée de récéption : %f s\n",temps.tv_sec+temps.tv_usec/1000000);
     printf("Durée de transfert : %f s\n",(Temparr-Tempdepart));


     exit( 0 );
}
