#include "arbre.h"
#include "ui_arbre.h"

arbre::arbre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::arbre)
{
    ui->setupUi(this);
    a=NULL;
    interface=new QGraphicsView(this);
    interface->setGeometry(25,0,550,600);
    ecrire =new QGraphicsScene(-230,10,500,570,this);
    interface->setScene(ecrire);
    int i,j;
    i=18;
    j=0;
     QFont font("Times", 12, QFont::Bold);
     QString c("H=");

    while(i<=660){
                      j++;
                      QGraphicsTextItem *v=new QGraphicsTextItem(c+QString::number(j));
                      v->setPos(250,i+30);
                      v->setFont(font);
                      ecrire->addItem(v);
                      ecrire->addLine(-255,i,400,i);
                      i=i+80;




                    }
    this->show();
}

arbre::~arbre()
{
    delete ui;
    if(a){
         if(a->ellipse) delete a->ellipse;
         if(a->l_droite) delete a->l_droite;
         if(a->l_gauche) delete a->l_gauche;
         if(a->sad) delete a->sad;
         if(a->sag) delete a->sag;
         if(a->texte) delete a->texte;
         delete a;

    }
}




//POSITION DES BRANCHES
int arbre::posgauche(lenoeud *un){
    int o;
    double p;
    o=(un->posy-18)/80;
    p=un->posx-(120/puissance(2,o));
    return p;
}

//POSITION DES BRANCHES
int arbre::posdroite(lenoeud *un){
    double p;
    int o;
    o=(un->posy-18)/80;
    p=un->posx+(120/puissance(2,o));
    return p;
}


//CREATION D UN NOEUD
lenoeud *arbre::nouveau_noeud(QGraphicsScene *ecrire, QString val, double x, double y, int ha){

          QPen bic;
          int r,g,b;
          double xg,xd;
          r=couleur(0,255);
          g=couleur(0,255);
          b=couleur(0,255);
          bic.setColor(QColor(70,20,0));
          bic.setWidth(5);
          QBrush brush(QColor(r,g,b), Qt::SolidPattern);
          QFont font("Times", 12, QFont::Bold);
    lenoeud *a;
    a=new lenoeud;
    a->val=val;
    a->sad=NULL;
    a->sag=NULL;
    a->posx=x;
    a->posy=y;
    a->haut=0;
    xg=x-(120/puissance(2,ha));
    xd=x+D+(120/puissance(2,ha));
    a->ellipse=new QGraphicsEllipseItem(x,y,D,D);
    a->l_gauche=new QGraphicsLineItem(x+15,y+D,xg+15,y+80);
    a->l_droite=new QGraphicsLineItem(x+25,y+D,xd-15,y+80);
    a->texte=new QGraphicsTextItem(val);
          a->texte->setPos(x+7,y+7);
          a->texte->setFont(font);
          a->l_droite->setPen(bic);
          a->l_gauche->setPen(bic);
          a->ellipse->setBrush(brush);
          a->ellipse->setPen(bic);
          ecrire->addItem(a->l_droite);
          ecrire->addItem(a->l_gauche);
          ecrire->addItem(a->ellipse);
          ecrire->addItem(a->texte);
this->show();
          return a;
}





int arbre::puissance(int a, int b)
{
    int p=1;
       for(int i=1;i<=b;i++){
                           p=p*a;
                             }
      return p;
}



//FERMER LA FENETRE
void arbre::on_pushButton_clicked()
{
    this->close();
}





int arbre::est_vide(lenoeud *a)
{
    if(a==NULL) return 1;
    else return 0;
}

int arbre::racine(lenoeud *a)
{
    if(a) {
          bool ok;
          int v=a->val.toInt(&ok);
          return v;

          }
    else return -1;
}

lenoeud *arbre::SAG(lenoeud * a)
{
    return a->sag;
}

lenoeud *arbre::SAD(lenoeud * a)
{
    return a->sad;
}

lenoeud *arbre::le_pere()
{
    return a;
}

int arbre::couleur(int a, int b)
{
    return rand()%(b-a)+a;
}






int arbre::la_hauteur(lenoeud *un)
{
    if(un->sag==0 && un->sad==0)  un->haut=0;
    else if(un->sad==0 && un->sag!=0) un->haut=1+la_hauteur(un->sag);
    else if(un->sag==0 && un->sad!=0) un->haut=1+la_hauteur(un->sad);
    else un->haut=1+maximum(la_hauteur(un->sag),la_hauteur(un->sad));

   return un->haut;


}




int arbre::maximum(int xa, int xb)
{
    if(xa>xb) return xa;
    else return xb;
}



int arbre::pile_est_vide()
{
    if(sommet==0) return 1;
    else return 0;
}


int arbre::empiler(lenoeud *un)
{
    int ok=0;
    if(sommet<tailleP){
                        tab[sommet]=un;
                        sommet++;
                        ok=1;
                        }

    return ok;
}



lenoeud *arbre::depiler()
{
    int pos;
    lenoeud *un=NULL;
    if(sommet>0){
                   pos=sommet-1;
                   un=tab[pos];
                   delete tab[pos];
                   tab[pos]=NULL;
                   sommet--;
                  }
    return un;

}




void arbre::afficher()
{
   lenoeud * v;





   if(est_vide(a)==1) {

                       qDebug()<<"VIDE";
                       return ;
                      }

   v=a;

   while(1){
             while(est_vide(v->sag)==0){
                                     empiler(v);
                                     v=v->sag;
                                     }
                qDebug()<<racine(v);



             while(est_vide(v->sad)==1){
                                        if(pile_est_vide()==1) return ;
                                        v=depiler();
                                        qDebug()<<racine(v);



                                        }
             v=v->sad;
            }


}







void arbre::lenouveau_pere(lenoeud *un)
{
    a=un;
}





//DEPLACEMENT DES NOEUDS
void arbre::deplacer(lenoeud *un,double xfin,double yfin)
{

         QEventLoop eventLoop;
         double coef,b,depx,depy,xdeb,ydeb,xa,ya,difx,dify;

         xdeb=un->posx;
         ydeb=un->posy;



         xa=xdeb;
         ya=ydeb;
         depx=xa;
         depy=ya;

         int hx;


         if(xdeb==xfin){
                  while(depy!=yfin){
                                  difx=depx;
                                  dify=depy;
                                  if(depy<yfin)depy++;
                                  else depy--;

                                  hx=(depy-18)/80;


                                  un->posx=un->posx+depx-difx;
                                  un->posy=un->posy+depy-dify;


                                  un->ellipse->moveBy(depx-difx,depy-dify);


                                  un->l_gauche->setLine(un->posx+15,un->posy+D,un->posx+15-120/puissance(2,hx),un->posy+80);
                                  un->l_droite->setLine(un->posx+25,un->posy+D,un->posx+25+120/puissance(2,hx),un->posy+80);

                                  un->texte->moveBy(depx-difx,depy-dify);

                                  if(un->sag)   deplacer(un->sag,un->posx-120/puissance(2,hx),un->posy+80);
                                  if(un->sad) deplacer(un->sad,un->posx+120/puissance(2,hx),un->posy+80);

                                  QTimer::singleShot (10, &eventLoop, SLOT (quit ()));
                                  eventLoop.exec ();
                                  this->show();
                                 }
                         }
         else{
                   coef=(yfin-depy)/(xfin-depx);
                   b=depy-coef*depx;
                   while(depx!=xfin){

                       difx=depx;
                       dify=depy;
                       if(depx<xfin) depx++;
                       else depx--;
                       depy=coef*depx+b;


                       un->posx=un->posx+depx-difx;
                       un->posy=un->posy+depy-dify;

                       hx=(depy-18)/80;

                       un->ellipse->moveBy(depx-difx,depy-dify);
                       un->l_gauche->setLine(un->posx+15,un->posy+D,un->posx+15-120/puissance(2,hx),un->posy+80);
                       un->l_droite->setLine(un->posx+25,un->posy+D,un->posx+25+120/puissance(2,hx),un->posy+80);
                       un->texte->moveBy(depx-difx,depy-dify);

                       if(un->sag)  deplacer(un->sag,un->posx-120/puissance(2,hx),un->posy+80);
                       if(un->sad) deplacer(un->sad,un->posx+120/puissance(2,hx),un->posy+80);


                       QTimer::singleShot (10, &eventLoop, SLOT (quit ()));
                       eventLoop.exec ();
                       this->show();

                                    }
         }




}





//ROTATION GAUCHE
lenoeud* arbre::rotationgauche( lenoeud * un)
{

int x1,y1,x2,y2,h1;

QEventLoop eventLoop;
QTimer::singleShot (1200, &eventLoop, SLOT (quit ()));
eventLoop.exec ();

if(SAD(un)) {
            lenoeud *B;
            h1=(un->posx-18)/80;
            x1=un->posx+(120/puissance(2,h1+1));
            y1=un->sad->posy+80;
            x2=un->posx;
            y2=un->posy;


            B=un->sad;
            un->sad=B->sag;

            //DEPLACEMENT
            deplacer(un,x1,y1);

            B->sag=un;

            //DEPLACEMENT
            deplacer(B,x2,y2);


            un=B;
           }

lenouveau_pere(un);
la_hauteur(un->sag);
la_hauteur(un);

return un;
}





//ROTATION DROITE
lenoeud *arbre::rotationdroite(lenoeud* un)
{

    QEventLoop eventLoop;
    QTimer::singleShot (1200, &eventLoop, SLOT (quit ()));
    eventLoop.exec ();
    int x1,y1,x2,y2,h1;
    if(SAG(un)) {


                 lenoeud *B;
                 h1=(un->posx-18)/80;
                 x1=un->posx-(120/puissance(2,h1+1));
                 y1=un->sag->posy+80;
                 x2=un->posx;
                 y2=un->posy;



                 B=un->sag;
                 un->sag=B->sad;

                 //DEPLACEMENT
                 deplacer(un,x1,y1);


                 B->sad=un;

                 //DEPLACEMENT
                 deplacer(B,x2,y2);

                 un=B;

                }

lenouveau_pere(un);
la_hauteur(un->sad);
la_hauteur(un);

return un;
}




//ROTATION GAUCHE DROITE
lenoeud *arbre::rotationGD(lenoeud *un)
{
if(un->sag){
            un->sag=rotationgauche(un->sag);
            un=rotationdroite(un);
                }
return un;

}




//ROTATION DROITE GAUCHE
lenoeud *arbre::rotationDG(lenoeud *un)
{
if(un->sad){
    un->sad=rotationdroite(un->sad);
      un=rotationgauche(un);
          }

return un;
}


//LE DESEQUILIBRE

int arbre::desequilibre(lenoeud *un)
{

    int hg,hd;

    if(un==NULL) return 0;
    if(un->sag!=NULL && un->sad!=NULL) {
                                   hg=un->sag->haut;
                                   hd=un->sad->haut;
                                     }
    else if(un->sag==NULL && un->sad!=NULL) {
                                             hg=0;
                                             hd=un->haut;
                                             }
    else if(un->sad==NULL && un->sag!=NULL) {
                                            hd=0;
                                            hg=un->haut;
                                             }
    else {
          hd=hg=0;
          }


    return hg-hd;

}





lenoeud* arbre::reequilibrage(lenoeud *un)
{
    int d;
    d=desequilibre(un);

    if(d==2){
          qDebug()<<"si bir";
           if(desequilibre(un->sag)==2 || desequilibre(un->sag)==-2) {
                                                                  un->sag=reequilibrage(un->sag);
                                                                 }
          else if(desequilibre(un->sag)==-1) un=rotationGD(un);
          else un=rotationdroite(un);
           }
    else if(d==-2){
                   if(desequilibre(un->sad)==2 || desequilibre(un->sad)==-2){

                                                         un->sad=reequilibrage(un->sad);

                                                         }
                  else  if(desequilibre(un->sad)==1) un=rotationDG(un);
                   else un=rotationgauche(un);
                  }
             else {
                   if(un->sag) un->sag=reequilibrage(un->sag);
                   if(un->sad) un->sad=reequilibrage(un->sad);
                   }


    return un;
}





//INSERTION DANS UN AVL
int arbre::insertion(QString valeur,int choix)
{
    lenoeud * un=NULL;
    int v;
    int ok=0;
    bool ok1;


         lenoeud *cour,*pere;
         cour=pere=a;
         int h=0;

         //choix==0 pour les valeurs entieres ;
         //choix==1 pour exemple rotation gauche;
         //choix==2 pour exemple rotation droite;
         //choix==3 pour exemple rotation gauche droite
         //choix==4 pour exemple rotation droite gauche


         if(choix==0){

         v=valeur.toInt(&ok1);

         while(cour!=NULL){

                           if(v<cour->val.toInt(&ok1)) { // LA VALEUR A INSERE EST INFERIEUR AU COURANT
                                          // cour->des++;
                                           pere=cour;
                                           cour=cour->sag;
                                           h++;
                                           }
                           else if(v>cour->val.toInt(&ok1)){ // LA VALEUR A INSERE EST SUPERIEUR AU COURANT
                                           //   cour->des--;
                                               pere=cour;
                                               cour=cour->sad;
                                               h++;
                                               }
                           else cour=NULL;
                           }
         if(pere==NULL){
                        a=nouveau_noeud(ecrire,valeur,0,20,h);
                        ok=1;
                        //qDebug()<<"INSERTION EFFECTUE";
                       }
         else{
              if(v<pere->val.toInt(&ok1)) {

                               ok=1;
                               un=nouveau_noeud(ecrire,valeur,posgauche(pere),pere->posy+80,h);
                               pere->sag=un;
                               }
             else if(v>pere->val.toInt(&ok1)){

                                  ok=1;
                                  un=nouveau_noeud(ecrire,valeur,posdroite(pere),pere->posy+80,h);
                                  pere->sad=un;
                                  }
             }





                            if(ok==1){
                                     QEventLoop eventLoop;
                                     QTimer::singleShot (400, &eventLoop, SLOT (quit ()));
                                     eventLoop.exec ();
                                     la_hauteur(a);
                                     a=reequilibrage(a);
                                     }

         }
else if(choix==1){
              if(cour==NULL)  a=nouveau_noeud(ecrire,valeur,0,20,0);
              else  a->sad=nouveau_noeud(ecrire,valeur,posdroite(a),a->posy+80,1);
              ok=1;
                  }
else if(choix==2){
             if(cour==NULL)  a=nouveau_noeud(ecrire,valeur,0,20,0);
             else  a->sag=nouveau_noeud(ecrire,valeur,posgauche(a),a->posy+80,1);
             ok=1;

                 }
else if(choix==3){
             if(cour==NULL)  a=nouveau_noeud(ecrire,valeur,0,20,0);
             else  if(a->sag==NULL) a->sag=nouveau_noeud(ecrire,valeur,posgauche(a),a->posy+80,1);
                    else a->sag->sad=nouveau_noeud(ecrire,valeur,posdroite(a->sag),a->sag->posy+80,2);
             ok=1;
                  }
else if(choix==4){
             if(cour==NULL)  a=nouveau_noeud(ecrire,valeur,0,20,0);
             else  if(a->sad==NULL) a->sad=nouveau_noeud(ecrire,valeur,posdroite(a),a->posy+80,1);
                    else a->sad->sag=nouveau_noeud(ecrire,valeur,posgauche(a->sad),a->sad->posy+80,1);
             ok=1;
                 }

 return ok;


}





void arbre::on_pushButton_2_clicked()
{
    QString ent;
   // int entre;
    //bool ok;
    ent=ui->lineEdit->text();
    if(ent!=NULL){
           //entre=ent.toInt(&ok);
           insertion(ent,0);
          }

}












void arbre::cacher()
{
ui->lineEdit->hide();
ui->pushButton_2->hide();
}



