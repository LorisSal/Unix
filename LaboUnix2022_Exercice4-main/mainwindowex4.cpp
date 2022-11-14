#include "mainwindowex4.h"
#include "ui_mainwindowex4.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

extern MainWindowEx4 *w;

int idFils1, idFils2, idFils3;
// TO DO : HandlerSIGCHLD
void HandlerSIGCHLD(int);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindowEx4::MainWindowEx4(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindowEx4)
{
  ui->setupUi(this);
  ui->pushButtonAnnulerTous->setVisible(false);

  // armement de SIGCHLD
  // TO DO
  struct sigaction A;

  // Armement de SIGCHLD
  A.sa_handler = HandlerSIGCHLD;
  sigemptyset(&A.sa_mask);
  A.sa_flags = 0;

  if(sigaction(SIGCHLD,&A,NULL) == -1)
  {
    perror("Erreur de sigaction");
    exit(1);
  }
}

MainWindowEx4::~MainWindowEx4()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx4::setGroupe1(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe1->clear();
    return;
  }
  ui->lineEditGroupe1->setText(Text);
}

void MainWindowEx4::setGroupe2(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe2->clear();
    return;
  }
  ui->lineEditGroupe2->setText(Text);
}

void MainWindowEx4::setGroupe3(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe3->clear();
    return;
  }
  ui->lineEditGroupe3->setText(Text);
}

void MainWindowEx4::setResultat1(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat1->clear();
    return;
  }
  ui->lineEditResultat1->setText(Text);
}

void MainWindowEx4::setResultat2(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat2->clear();
    return;
  }
  ui->lineEditResultat2->setText(Text);
}

void MainWindowEx4::setResultat3(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat3->clear();
    return;
  }
  ui->lineEditResultat3->setText(Text);
}

bool MainWindowEx4::traitement1Selectionne()
{
  return ui->checkBoxTraitement1->isChecked();
}

bool MainWindowEx4::traitement2Selectionne()
{
  return ui->checkBoxTraitement2->isChecked();
}

bool MainWindowEx4::traitement3Selectionne()
{
  return ui->checkBoxTraitement3->isChecked();
}

const char* MainWindowEx4::getGroupe1()
{
  if (ui->lineEditGroupe1->text().size())
  { 
    strcpy(groupe1,ui->lineEditGroupe1->text().toStdString().c_str());
    return groupe1;
  }
  return NULL;
}

const char* MainWindowEx4::getGroupe2()
{
  if (ui->lineEditGroupe2->text().size())
  { 
    strcpy(groupe2,ui->lineEditGroupe2->text().toStdString().c_str());
    return groupe2;
  }
  return NULL;
}

const char* MainWindowEx4::getGroupe3()
{
  if (ui->lineEditGroupe3->text().size())
  { 
    strcpy(groupe3,ui->lineEditGroupe3->text().toStdString().c_str());
    return groupe3;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx4::on_pushButtonDemarrerTraitements_clicked()
{
  fprintf(stderr,"Clic sur le bouton Demarrer Traitements\n");
  // TO DO


  //pid_t idFils1,idFils2,idFils3, id;
  //pid_t id;
  int fd, fdDup;
  //???
  // struct sigaction A;

  // // Armement de SIGCHLD
  // A.sa_handler = HandlerSIGCHLD;
  // sigemptyset(&A.sa_mask);
  // A.sa_flags = 0;

  if((fd = open("Trace.log", O_WRONLY | O_APPEND))==-1)
  {
    fd = open("Trace.log", O_CREAT | O_WRONLY | (O_APPEND), 0777);
  }

  fdDup = dup2(fd, 2);

  if(fdDup==-1)
  {
    perror("erreur de dup");
    exit(1);
  }


  

  if(traitement1Selectionne()==1)
  {
    if((idFils1 = fork()) == -1 )
    {
      perror("(Pere) Erreur de fork(1)");
      exit(1);
    }
    if (idFils1 == 0)
    {
      // Code du fils 1
      if (execl("./Traitement","Traitement",getGroupe1(),"200",NULL) == -1)
      {
        perror("Erreur de execl(1)");//execution retourne un exit du nombre d'etudiant
        exit(1);
      }
    }

  }

  if(traitement2Selectionne()==1)
  {
    if((idFils2 = fork()) == -1)
    {
      perror("(Pere) Erreur de fork(2)");
      exit(1);
    }

    if (idFils2 == 0)
    {
      // Code du fils 2
      if (execl("./Traitement","Traitement",getGroupe2(),"450",NULL) == -1)
      {
        perror("Erreur de execl(2)");//execution retourne un exit du nombre d'etudiant
        exit(1);
      }
    }
  }
  if(traitement3Selectionne()==1)
  {
    if((idFils3 = fork()) == -1)
    {
      perror("(Pere) Erreur de fork(3)");
      exit(1);
    }

    if (idFils3 == 0)
    {
      // Code du fils 3
      if (execl("./Traitement","Traitement",getGroupe3(),"700",NULL) == -1)
      {
        perror("Erreur de execl(3)");//execution retourne un exit du nombre d'etudiant
        exit(1);
      }
    }
  }

  //PERE


  //id = getpid();


  // while(1)
  // {
  //   if(id==idFils1)
  //   {
  //     // if(WIFEXITED(status))
  //       setResultat1(WEXITSTATUS(status));
  //   }
  //   else if(id==idFils2)
  //   {
  //     // if(WIFEXITED(status))
  //       setResultat2(WEXITSTATUS(status));
  //   }
  //   else if(id==idFils3)
  //   {
  //     // if(WIFEXITED(status))
  //       setResultat3(WEXITSTATUS(status));
  //   }
  // }




  //  id = wait(&status);
  //   printf("(PERE) fils %d se termine\n", id);

  //   if(id==idFils1)
  //   {
  //     if(WIFEXITED(status))
  //       setResultat1(WEXITSTATUS(status));
  //   }
  //   else if(id==idFils2)
  //   {
  //     if(WIFEXITED(status))
  //       setResultat2(WEXITSTATUS(status));
  //   }
  //   else if(id==idFils3)
  //   {
  //     if(WIFEXITED(status))
  //       setResultat3(WEXITSTATUS(status));
  //   }
}

void MainWindowEx4::on_pushButtonVider_clicked()
{
  fprintf(stderr,"Clic sur le bouton Vider\n");
  // TO DO
  ui->lineEditGroupe1->clear();
  ui->lineEditGroupe2->clear();
  ui->lineEditGroupe3->clear();
  ui->lineEditResultat1->clear();
  ui->lineEditResultat2->clear();
  ui->lineEditResultat3->clear();
}

void MainWindowEx4::on_pushButtonQuitter_clicked()
{
  fprintf(stderr,"Clic sur le bouton Quitter\n");
  // TO DO
  exit(0);
}

void MainWindowEx4::on_pushButtonAnnuler1_clicked()
{
  fprintf(stderr,"Clic sur le bouton Annuler1\n");

  if(kill(idFils1,SIGUSR1) == -1)
  {
    perror ("Erreur de kill");
    exit(1);
  }
}

void MainWindowEx4::on_pushButtonAnnuler2_clicked()
{
  fprintf(stderr,"Clic sur le bouton Annuler2\n");
  // TO DO

  if(kill(idFils2,SIGUSR1) == -1)
  {
    perror ("Erreur de kill");
    exit(1);
  }
}

void MainWindowEx4::on_pushButtonAnnuler3_clicked()
{
  fprintf(stderr,"Clic sur le bouton Annuler3\n");
  // TO DO

  if(kill(idFils3,SIGUSR1) == -1)
  {
    perror ("Erreur de kill");
    exit(1);
  }
}

void MainWindowEx4::on_pushButtonAnnulerTous_clicked()
{
  // fprintf(stderr,"Clic sur le bouton Annuler tout\n");
  // NOTHING TO DO --> bouton supprimé
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////// Handlers de signaux //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TO DO : HandlerSIGCHLD

void HandlerSIGCHLD(int sig)
{

  fprintf(stderr,"(Traitement %d) Reception du signal SIGALRM (%d)\n",getpid(),sig);

  int id, status;
  id = wait(&status);
  printf("\n(PERE) Suppression du fils %d de la table des processus\n",id);

  if(id==idFils1)
  {
    if(WIFEXITED(status))
      w->setResultat1(WEXITSTATUS(status));
  }
  else if(id==idFils2)
  {
    if(WIFEXITED(status))
      w->setResultat2(WEXITSTATUS(status));
  }
  else if(id==idFils3)
  {
    if(WIFEXITED(status))
      w->setResultat3(WEXITSTATUS(status));
  }


  //w->setResultat1(WEXITSTATUS(status));
}