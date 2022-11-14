#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <unistd.h>
#include <cstring>
#include "protocole.h" // contient la cle et la structure d'un message

int idQ;
int pid1,pid2;

void HandlerSIGINT(int);


int main()
{
  MESSAGE requete;
  pid_t destinataire;
  int ret;
  char tmp[80];

  // Armement du signal SIGINT
  // TO DO (etape 6)
  struct sigaction A;

  A.sa_handler = HandlerSIGINT;
  sigemptyset(&A.sa_mask);
  A.sa_flags = 0 ;

  if (sigaction(SIGINT,&A,NULL) == -1)
  {
    perror("Erreur de sigaction");
    exit(1);
  }

  // Creation de la file de message
  fprintf(stderr,"(SERVEUR) Creation de la file de messages\n");
  // TO DO (etape 2)

  if ((idQ = msgget(CLE,0)) == -1)
  {
    if((idQ = msgget(CLE,IPC_CREAT | IPC_EXCL | 0600)) == -1)
    {
      perror("(SERVEUR) Erreur de msgget");
      exit(1);
    }
  }



  // Attente de connection de 2 clients
  fprintf(stderr,"(SERVEUR) Attente de connection d'un premier client...\n");
  // TO DO (etape 5)
  if ((ret = msgrcv(idQ,&requete,sizeof(MESSAGE)-sizeof(long),2,0)) == -1)
  {
    perror("Erreur de msgrcv");
    exit(1);
  }

  pid1=requete.expediteur;
  fprintf(stderr,"%d\n", pid1);

  fprintf(stderr,"(SERVEUR) Attente de connection d'un second client...\n");
  // TO DO (etape 5)
  if ((ret = msgrcv(idQ,&requete,sizeof(MESSAGE)-sizeof(long),2,0)) == -1)
  {
    perror("Erreur de msgrcv");
    exit(1);
  }

  pid2=requete.expediteur;
  fprintf(stderr,"%d\n", pid2);

  while(1) 
  {
    // TO DO (etapes 3, 4 et 5)
  	fprintf(stderr,"(SERVEUR) Attente d'une requete...\n");


    if ((ret = msgrcv(idQ,&requete,sizeof(MESSAGE)-sizeof(long),1,0)) == -1)
    {
      perror("Erreur de msgrcv");
      exit(1);
    }


    fprintf(stderr,"(SERVEUR) Requete recue de %d : --%s--\n",requete.expediteur,requete.texte);
    

    if(requete.expediteur==pid1)
    {
      destinataire=pid2;
      requete.type=long(pid2);
    }
    else
    {
      destinataire=pid1;
      requete.type=long(pid1);
    }

    requete.expediteur=getpid();
    strcpy(tmp, requete.texte);
    strcpy(requete.texte,"(SERVEUR)");
    strcat(requete.texte, tmp);
    
    fprintf(stderr,"(SERVEUR) Envoi de la reponse a %d\n",destinataire);

    if (msgsnd(idQ,&requete,sizeof(MESSAGE)-sizeof(long), 0) == -1)
    {
      perror("Erreur de msgsnd");
      exit(1);
    }
    if(kill(destinataire,SIGUSR1) == -1)
    {
      perror ("Erreur de kill");
      exit(1);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handlers de signaux ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO DO (etape 6)
void HandlerSIGINT(int sig)
{
  
  fprintf(stderr,"(Traitement %d) Reception du signal (%d), SUPRESSION FILE DE MESSAGE\n",getpid(),sig);

  if (msgctl(idQ,IPC_RMID,NULL) == -1)
  {
    perror("Erreur de msgctl");
    exit(1);
  }
  exit(0);
}
