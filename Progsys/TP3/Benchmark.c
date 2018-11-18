
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

void tri_bulles(float * tab,int taille)
{
    int tab_en_ordre = 0;
    int tmp;
    while(!tab_en_ordre)
    {
        tab_en_ordre = 1;
        for(int i=0 ; i < taille-1 ; i++)
        {
            if(tab[i] > tab[i+1])
            {
                tmp=tab[i];
                tab[i]=tab[i+1];
                tab[i+1]=tmp;
                tab_en_ordre = 0;
            }
        }
        taille--;
    }
  }

int main(int argc, char * argv[]){
  if( argc != 4 ){

        fprintf( stderr , "Usage : %s <Nb d'execution par fils> <./commande> <Nb fils>\n",
  	       argv[0] );
        exit(-1);
  }//     
  /****************************************************************************************/
                                  // NE JAMAIS ESSAYER AVEC TOP
  /****************************************************************************************/
  int K = atoi(argv[1]);
  struct timeval tpstart; //temps de départ des fonctions
  struct timeval tparr; //Temps de fin des fonctions
  char commande[20];
  float buf=0.0;
  int cr;
  int fd;
  int arret=0;
  strcpy(commande,argv[2]);
  int N = atoi(argv[3]);
  float tab[N];
  float tmoyen=0.0;
  int tube[N][2];
  /*On ouvre un canal pour chaque fils*/
  for (int i=0; i<N ;i++){
    pipe(tube[i]);
  }

  for (int i=0;i<N;i++) { if (N%2==0)
    tmoyen=(tab[N/2]+tab[N/2+1])/2;
  else
    tmoyen=tab[N/2+1];
    switch(fork()){
      case -1: perror("Problème de fork \n");
               exit(-1);
      case 0:

            //printf("Fils numéro %i\n",i);
            close(tube[i][0]);// On ferme l'entrée en écriture
 
            for(int j=0; j<K; j++){

              gettimeofday(&tpstart,NULL);//On récupère le temps de départ
              switch(fork()){
              	case -1 : perror("Problème de fork \n");
              				 exit(-1);
              	
              	case 0 :
              		fd = open("/dev/null",O_WRONLY,0666);
  						close(1);
  						
 						dup(fd);
              		execlp(commande,commande,NULL);
              		perror("Problème avec execlp\n");
              		exit(42);            		
              }
              wait(&cr);
              
              if (WIFEXITED(cr) && WEXITSTATUS(cr)==42){
              	exit(42);
              }
              if (WIFEXITED(cr) && WEXITSTATUS(cr)!=0){
              	fprintf(stderr,"Exit avec code d'erreur : %i\n",WEXITSTATUS(cr));
              	exit(-1);
              }
              if (WIFEXITED(cr) && WEXITSTATUS(cr)==0){
              	fprintf(stderr,"Ok\n");
              	exit(256);
              }
              if (WIFSIGNALED(cr)){
             	 fprintf(stderr,"Interruption par le signal %i\n",WTERMSIG(cr));
              	 exit(-20);
              }
              gettimeofday(&tparr,NULL);
              
              buf+=((tparr.tv_sec * 1000 + tparr.tv_usec / 1000) -
							(tpstart.tv_sec * 1000 + tpstart.tv_usec / 1000)); //Passage en ms

            }
             buf/=K;
              write(tube[i][1], &buf, sizeof(float));

          close(tube[i][1]); //On ferme la sortie d'écriture
          exit(0);
			}
			
			
			if (WIFEXITED(cr) && WEXITSTATUS(cr)==42){
              	exit(42);
          }
         if(WIFEXITED(cr) && WEXITSTATUS(cr)==-20){
         	//SIGNAL
         	exit(-20);      
         }
         if (WIFEXITED(cr) && WEXITSTATUS(cr)!=0){
           
           exit(-1);
          }
         
          
    }
  for (int i=0;i<N;i++){
    close(tube[i][1]);
		read(tube[i][0], &(tab[i]), sizeof(float));
		close(tube[i][0]);
  }

  tri_bulles(tab,N);
  if (N%2==0)
    tmoyen=(tab[N/2]+tab[N/2+1])/2;
  else
    tmoyen=tab[N/2+1];
	

	if (tmoyen>0){
	for(int i=0;i<N;i++){
		printf("%f\n",tab[i]);
	}
  printf("\nLe temps d'execution moyen de la commande <%s> est %.2f ms\n",commande,tmoyen);
  }
  exit(0);

//com1 1s
//com2 Problème dans la commande : Success
//com3 Interuption par le signal 3
//com4 Interruption par le signal 2

}
