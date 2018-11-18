#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>

#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif

#include <file_messages.h>

#define BIG_TAILLE MESSAGES_NB*MESSAGES_TAILLE
char big_buffer[BIG_TAILLE] ;



int
main( int nb_arg , char * tab_arg[] )
{

     char nomprog[128] ;

     /*-----*/
     strcpy( nomprog , tab_arg[0] );

     if( nb_arg != 2 )
       {
	 fprintf( stdout , "%s - Recepteur dans la communication par fichier\n\n" , nomprog ) ;
	 fprintf( stderr , "Usage : %s pid\n" , nomprog ) ;
	 exit(1) ;
       }
    float temps_debut,temps_fin,temps_depart;
    int fd;
    struct timeval temps;
    struct flock lock;
	  int pid;
		fd=open("File",O_RDONLY,0666);

		lock.l_whence = 0;
		lock.l_len = 0;
		lock.l_type = F_RDLCK;
		lock.l_start=0;
		lock.l_len=0;


    char message[MESSAGES_TAILLE];

    while(fcntl(fd, F_SETLKW, &lock) == -1);

    gettimeofday(&temps, NULL);
    printf("Je commence la lecture\n");
    read(fd,big_buffer,MESSAGES_TAILLE*10);
    printf("j'ai fini la lecture \n");

    temps_debut = temps.tv_sec+(temps.tv_usec/1000000.0);
    gettimeofday(&temps,NULL);

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);

    kill(atoi(tab_arg[1]),30);
    temps_fin = temps.tv_sec+(temps.tv_usec/1000000.0);

    while(fcntl(fd, F_SETLKW, &lock) == -1);

    read(fd,&temps_depart,sizeof(float));
    printf("La durée de récéption est %.3f secondes\n\n", temps_fin-temps_debut);
    printf("La duree de transmission est de %.3f secondes\n\n", temps_fin-temps_depart);

     exit(0);
}
