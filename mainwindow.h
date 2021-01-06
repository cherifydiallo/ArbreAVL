#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "arbre.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionRotation_Gauche_triggered();

    void on_actionRotation_Droite_triggered();

    void on_actionFERMER_triggered();

    void on_actionRotation_Droite_Gauche_triggered();

    void on_actionRotation_Gauche_Droite_triggered();

    void on_actionNouveau_triggered();

private:
    Ui::MainWindow *ui;
    arbre *a;
};

#endif // MAINWINDOW_H
