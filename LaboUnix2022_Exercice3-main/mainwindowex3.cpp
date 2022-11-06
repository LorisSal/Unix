#include "mainwindowex3.h"
#include "ui_mainwindowex3.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>


MainWindowEx3::MainWindowEx3(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindowEx3)
{
    ui->setupUi(this);
}

MainWindowEx3::~MainWindowEx3()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx3::setGroupe1(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe1->clear();
    return;
  }
  ui->lineEditGroupe1->setText(Text);
}

void MainWindowEx3::setGroupe2(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe2->clear();
    return;
  }
  ui->lineEditGroupe2->setText(Text);
}

void MainWindowEx3::setGroupe3(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe3->clear();
    return;
  }
  ui->lineEditGroupe3->setText(Text);
}

void MainWindowEx3::setResultat1(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 || strcmp(Text, "-1")==0)
  {
    ui->lineEditResultat1->clear();
    return;
  }
  ui->lineEditResultat1->setText(Text);
}

void MainWindowEx3::setResultat2(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0  || strcmp(Text, "-1")==0)
  {
    ui->lineEditResultat2->clear();
    return;
  }
  ui->lineEditResultat2->setText(Text);
}

void MainWindowEx3::setResultat3(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0  || strcmp(Text, "-1")==0)
  {
    ui->lineEditResultat3->clear();
    return;
  }
  ui->lineEditResultat3->setText(Text);
}

bool MainWindowEx3::recherche1Selectionnee()
{
  return ui->checkBoxRecherche1->isChecked();
}

bool MainWindowEx3::recherche2Selectionnee()
{
  return ui->checkBoxRecherche2->isChecked();
}

bool MainWindowEx3::recherche3Selectionnee()
{
  return ui->checkBoxRecherche3->isChecked();
}

const char* MainWindowEx3::getGroupe1()
{
  if (ui->lineEditGroupe1->text().size())
  { 
    strcpy(groupe1,ui->lineEditGroupe1->text().toStdString().c_str());
    return groupe1;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe2()
{
  if (ui->lineEditGroupe2->text().size())
  { 
    strcpy(groupe2,ui->lineEditGroupe2->text().toStdString().c_str());
    return groupe2;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe3()
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
void MainWindowEx3::on_pushButtonLancerRecherche_clicked()
{
  fprintf(stderr,"Clic sur le bouton Lancer Recherche\n");

  pid_t idFils1,idFils2,idFils3, id;
  int status, fd, fdDup;

  if((fd = open("Trace.log", O_WRONLY | O_APPEND))==-1)
  {
    fd = open("Trace.log", O_CREAT | O_WRONLY | O_APPEND, 0777);
  }

  fdDup = dup2(fd, 2);

  if(fdDup==-1)
  {
    perror("erreur de dup");
    exit(1);
  }

  if(recherche1Selectionnee()==1)
  {
    if((idFils1 = fork()) == -1 )
    {
      perror("(Pere) Erreur de fork(1)");
      exit(1);
    }
  }

  if (idFils1 == 0)
  {
    // Code du fils 1
    if (execl("./Lecture","Lecture",getGroupe1(),NULL) == -1)
    {
      perror("Erreur de execl()");//execution retourne un exit du nombre d'etudiant
      exit(1);
    }
  }

  if(recherche2Selectionnee()==1)
  {
    if((idFils2 = fork()) == -1)
    {
      perror("(Pere) Erreur de fork(2)");
      exit(1);
    }
  }

  if (idFils2 == 0)
  {
    // Code du fils 2
    if (execl("./Lecture","Lecture",getGroupe2(),NULL) == -1)
    {
      perror("Erreur de execl()");//execution retourne un exit du nombre d'etudiant
      exit(1);
    }
  }


  if(recherche3Selectionnee()==1)
  {
    if((idFils3 = fork()) == -1)
    {
      perror("(Pere) Erreur de fork(3)");
      exit(1);
    }
  }


  if (idFils3 == 0)
  {
    // Code du fils 3
    if (execl("./Lecture","Lecture",getGroupe3(),NULL) == -1)
    {
      perror("Erreur de execl()");//execution retourne un exit du nombre d'etudiant
      exit(1);
    }
  }

  //code pere
  while((id = wait(&status)) != -1)
  {
    printf("(PERE) fils %d se termine\n", id);

    if(id==idFils1)
    {
      setResultat1(WEXITSTATUS(status));
    }
    else if(id==idFils2)
    {
      setResultat2(WEXITSTATUS(status));
    }
    else if(id==idFils3)
    {
      setResultat3(WEXITSTATUS(status));
    }
  }

  // close(fdDup);
}

void MainWindowEx3::on_pushButtonVider_clicked()
{
  fprintf(stderr,"Clic sur le bouton Vider\n");


  // setGroupe1("");
  // setGroupe2("");
  // setGroupe3("");
  ui->lineEditGroupe1->clear();
  ui->lineEditGroupe2->clear();
  ui->lineEditGroupe3->clear();
  ui->lineEditResultat1->clear();
  ui->lineEditResultat2->clear();
  ui->lineEditResultat3->clear();
}

void MainWindowEx3::on_pushButtonQuitter_clicked()
{
  fprintf(stderr,"Clic sur le bouton Quitter\n");

  exit(0);
}
