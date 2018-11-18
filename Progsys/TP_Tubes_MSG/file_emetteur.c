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

int
main( int nb_arg , char * tab_arg[] )
{
     char nomprog[128] ;
		struct timeval temps;
     /*-----*/

     strcpy( nomprog , tab_arg[0] );

     if( nb_arg != 1 )
       {
	 fprintf( stdout , "%s - Emetteur dans la communication par fichier\n\n" , nomprog ) ;
	 fprintf( stdout , "Usage : %s \n" , nomprog ) ;
	 exit(1) ;
       }

    float temps_debut,temps_fin;
    int fd;
    struct flock lock;

		fd=open("File",O_WRONLY | O_CREAT,0666);


		lock.l_len = 0;
		lock.l_type = F_WRLCK;
		lock.l_start=0;
		fcntl(fd, F_SETLKW, &lock);

    printf("Pid emetteur : %i\n",getpid());
    char message[MESSAGES_TAILLE];
    file_remplir(message,'X');
    gettimeofday(&temps, NULL);
    for (int i=0;i<10;i++){
    	write(fd,message,MESSAGES_TAILLE);
    }
    printf("J'ai fini d'écrire\n");
    temps_debut = temps.tv_sec+(temps.tv_usec/1000000.0);
    gettimeofday(&temps,NULL);
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    printf("Dévérouillé\n");
    temps_fin = temps.tv_sec+(temps.tv_usec/1000000.0);
    pause();// On attend le signal de délock
    lock.l_type = F_WRLCK;
    fcntl(fd, F_SETLKW, &lock);
    write(fd,&temps_debut,sizeof(float));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    printf("Durée d'envoi %f\n",temps.tv_sec + (temps.tv_usec / 1000000));
     exit(0);
}
