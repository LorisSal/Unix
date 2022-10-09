#include "FichierClient.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>



int estPresent(const char* nom)
{
  // TO DO
  
  int fd;
  int i=1;
  int test;
  CLIENT* client;

  //printf("yo1");

  fd = open("client.dat", O_RDONLY);
  if(fd == -1)
  {
    printf("erreur d'ouverture");
    return -1;
  }
  else  
  {
    //printf("yo");
    //sizeof
    int size;
    
    size = sizeof(CLIENT);
    //tant que retour de a fonction egale au nombre de byte que l'on veut lire
    test=read(fd, client, size);
    while(test==size && strcmp(client->nom,nom)!=0)
    {
      test=read(fd, client, size);
      i++;
    }
    if (close(fd))
    {
    perror("Erreur de close()");
    exit(1);
    }

    if(test==size)
    {
      return i;
    }
    else
    {
      return 0;
    }
  
  }
 // return 0;
}

////////////////////////////////////////////////////////////////////////////////////
int hash(const char* motDePasse)
{
  // TO DO

  int lnom;
  int i=0, r=0;
  char c;

  lnom = strlen(motDePasse);

  while(i<lnom)
  {
    c = motDePasse[i];
    r=r+(int(c)*i);
    i++;

  }

  r = r%97;

  return r;
}

////////////////////////////////////////////////////////////////////////////////////
void ajouteClient(const char* nom, const char* motDePasse)
{
  // TO 
  int fd;
  CLIENT client;

  int size;

  size=sizeof(CLIENT);

  if((fd = open("client.dat", O_WRONLY|O_APPEND))==-1)
  {
    fd = open("client.dat", O_CREAT|O_WRONLY);
  }

  strcpy(client.nom, nom);
  client.hash=hash(motDePasse);

  write(fd, &client, size);

  if (close(fd))
  {
    perror("Erreur de close()");  
    exit(1);
  }
  
}

////////////////////////////////////////////////////////////////////////////////////
int verifieMotDePasse(int pos, const char* motDePasse)
{
  // TO DO

  CLIENT client;
  int fd, test, i=0, mdp;


  if((fd = open("client.dat", O_RDONLY|O_APPEND))==-1)
  {
    printf("fichier n'exsite pas");
    return -1;
  }

  int size;
    
  size = sizeof(CLIENT);    //tant que retour de a fonction egale au nombre de byte que l'on veut lire
  lseek(fd, size*(pos-1), SEEK_SET);
  read(fd, &client, size);


  //printf("caca");


  if (close(fd))
  {
  perror("Erreur de close()");
  exit(1);
  }

  //puts(motDePasse);

  //puts(client.nom);
  //printf("hash : %d", client.hash);

  //printf("v1");

  mdp=hash(motDePasse);

  //printf("v2");

  //printf("%d", mdp);


  if(client.hash==mdp)
    return 1;
  else
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////
int listeClients(CLIENT *vecteur) // le vecteur doit etre suffisamment grand
{
  // TO DO

  int fd;
  int i, test;
  CLIENT client;

  if((fd = open("client.dat", O_RDONLY))==-1)
  {
    printf("fichier n'exsite pas");
    exit(1);
  }

  int size;
    
  size = sizeof(CLIENT);
  //tant que retour de a fonction egale au nombre de byte que l'on veut lire
  test=read(fd, &client, size);
  i=0;
   while(test==size)// && strcmp(client.nom,vecteur->nom)!=0)
   {
    *vecteur=client;
    i++;
    vecteur++;
    test=read(fd, &client, size);
  }

  if (close(fd))
  {
  perror("Erreur de close()");
  exit(1);
  }

  //printf("i = %d\n", i);


  return i;
 
}
