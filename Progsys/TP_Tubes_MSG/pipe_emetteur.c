#include <stdio.h>
#include <stdlib.h>	/* exit */
#include <sys/stat.h>	/* mknod */
#include <sys/types.h>	/* open */
#include <fcntl.h>
#include <unistd.h>	/* close , write */
#include <sys/time.h>
#include "pipe_messages.h"

#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif


int Tempdepart;

int
main( int nb_arg , char * tab_arg[])
{
     char nomprog[128] ;

     /*----------*/

     strcpy( nomprog , tab_arg[0] );

     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s - Emetteur dans la communication par flot\n\n" , nomprog );
	  fprintf( stderr , "usage : %s \n" , nomprog );
	  exit(-1);
     }

     int fd_tube,fd_tube1;
     char message[MESSAGES_TAILLE];
     char * NomTube = "TP51";
     mknod(NomTube,S_IFIFO | 0666,0);
     mknod("TubeRep",S_IFIFO | 0666,0);
     if ((fd_tube=open( NomTube,O_WRONLY,0)) == -1){
     	 perror ("Pb sur ouverture du tube nommé en écriture");
     	 exit(-2);
     }
     struct timeval start,end,temps;
     pipe_remplir(&message,'a');
     gettimeofday(&start,NULL);
     int i;
     for (i=0;i<MESSAGES_NB;i++)
     	write(fd_tube, message,MESSAGES_TAILLE);

    gettimeofday(&end,NULL);
    timersub(&end,&start,&temps);

    float Tempdepart = start.tv_usec /1000000 + start.tv_sec;
    close(fd_tube);
    sleep(2);
    if ((fd_tube1=open( "TubeRep",O_WRONLY,0)) == -1){
     	 perror ("Pb sur ouverture du tube nommé en écriture");
     	 exit(-2);
     }
     write(fd_tube1,&Tempdepart,sizeof(float));

     close(fd_tube1);
     printf("la durée de transmission est de %f s",temps.tv_usec / 1000000 + temps.tv_sec);
     exit(0);
}
