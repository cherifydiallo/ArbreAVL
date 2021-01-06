#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    a=NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionRotation_Gauche_triggered()
{

 if(a)delete a;
  a=new arbre;
  a->cacher();
  QString p("p");
  QString q("q");

  a->insertion(p,1);
  a->insertion(q,1);
  a->rotationgauche(a->le_pere());



}

void MainWindow::on_actionRotation_Droite_triggered()
{

    if(a)delete a;
     a=new arbre;
     a->cacher();
     QString p("p");
     QString q("q");

     a->insertion(p,2);
     a->insertion(q,2);
     a->rotationdroite(a->le_pere());


}

void MainWindow::on_actionFERMER_triggered()
{
    this->close();
}

void MainWindow::on_actionRotation_Droite_Gauche_triggered()
{
    if(a)delete a;
     a=new arbre;
     a->cacher();
     QString p("p");
     QString q("q");
     QString m("m");

     a->insertion(p,4);
     a->insertion(q,4);
     a->insertion(m,4);
     a->rotationDG(a->le_pere());

}

void MainWindow::on_actionRotation_Gauche_Droite_triggered()
{
    if(a)delete a;
     a=new arbre;
       a->cacher();

       QString p("p");
       QString q("q");
       QString m("m");

     a->insertion(p,3);
     a->insertion(q,3);
     a->insertion(m,3);
     a->rotationGD(a->le_pere());
}

void MainWindow::on_actionNouveau_triggered()
{
    if(a)delete a;
     a=new arbre;



}
