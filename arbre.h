#ifndef ARBRE_H
#define ARBRE_H

#include <QDebug>
#include <QDialog>


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QLineEdit>
#include <QPushButton>
#include <stdlib.h>


const int D=40;

const int tailleP=15;

typedef struct lenoeud{
    QString val;
    struct lenoeud *sag;
    struct lenoeud *sad;
    int haut;
    double posx;
    double posy;

    QGraphicsEllipseItem *ellipse;
    QGraphicsLineItem *l_droite;
    QGraphicsLineItem *l_gauche;
    QGraphicsTextItem *texte;


}*pnoeud;




namespace Ui {
class arbre;
}

class arbre : public QDialog
{
    Q_OBJECT

public:
    explicit arbre(QWidget *parent = 0);
    ~arbre();
          lenoeud *nouveau_noeud(QGraphicsScene *, QString , double , double , int );
          int puissance(int a,int b);
          int est_vide(lenoeud *);
          int racine(lenoeud *);
          lenoeud *SAG(lenoeud *);
          lenoeud *SAD(lenoeud *);
          lenoeud *le_pere();

          int couleur(int a,int b);
          int la_hauteur(lenoeud*);

          int maximum(int xa,int xb);
          int desequilibre(lenoeud *);

          int insertion(QString valeur, int choix);


          int pile_est_vide();
          int empiler(lenoeud *a);
          lenoeud *depiler();
          int posgauche(lenoeud *un);
          int posdroite(lenoeud *un);
          void cacher();

          void afficher();


          void lenouveau_pere(lenoeud *un);


         void fils_vide(lenoeud *);

         


          void deplacer(lenoeud *un, double xfin, double yfin);
          lenoeud *rotationgauche(lenoeud* un);
          lenoeud *rotationdroite(lenoeud* un);
          lenoeud* rotationGD(lenoeud *un);
          lenoeud* rotationDG(lenoeud *un);


          lenoeud *reequilibrage(lenoeud *un);


private slots:
          void on_pushButton_clicked();
          void on_pushButton_2_clicked();

private:
       Ui::arbre *ui;

       lenoeud * a;
       int sommet;
       lenoeud *tab[tailleP];

       QGraphicsView * interface;
       QGraphicsScene *ecrire;


};

#endif // ARBRE_H
