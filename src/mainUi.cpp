#include "mainwindow.h"
#include "connecteur_programme.h"
#include <QtGui>
#include <QGroupBox>
#include <QRadioButton>
#include <QProgressBar>
using namespace std;


int main( int argc, char **argv )
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication app( argc, argv );

    QWidget w;
    QGridLayout *grid= new QGridLayout(&w);

    QVBoxLayout *partie_commande=new QVBoxLayout();

        QPushButton *button_run=new QPushButton("Lancer le programme");

        QHBoxLayout *partie_lancement=new QHBoxLayout();
        QVBoxLayout *partie_lancement_2=new QVBoxLayout();
        QLineEdit *pourcentage= new QLineEdit();
        pourcentage->setPlaceholderText("Donnez le pourcentage");
        pourcentage->setToolTip("Indiquez le pourcentage de noeuds testés de 1 à 100");
        pourcentage->setFixedHeight(40);

        QProgressBar *progress = new QProgressBar();
        progress->setFixedHeight(30);


        QPushButton *button_choisir_graphe=new QPushButton("Choisir le graphe");

        QTextEdit *file_name= new QTextEdit("Choisissez un graphe");
        file_name->setFixedHeight(80);
        file_name->setReadOnly(true);

        QTextEdit *caracteristique_graphe= new QTextEdit("Caractéristiques du graphe");
        caracteristique_graphe->setFixedHeight(150);
        caracteristique_graphe->setReadOnly(true);

        QGroupBox *groupbox = new QGroupBox("Choix d'algo");

        QRadioButton *iteratif = new QRadioButton("Itératif");
        QRadioButton *recursif = new QRadioButton("Récursif");
        iteratif->setChecked(true);
        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->addWidget(iteratif);
        vbox->addWidget(recursif);
        groupbox->setLayout(vbox);

        partie_commande->addWidget(caracteristique_graphe);
        partie_commande->addStretch(10);
        partie_commande->addWidget(file_name);
        partie_commande->addWidget(button_choisir_graphe);
        partie_commande->addStretch(30);

        partie_lancement_2->addWidget(progress);
        partie_lancement_2->addWidget(pourcentage);


        partie_lancement->addWidget(groupbox);
        partie_lancement->addLayout(partie_lancement_2);


        partie_commande->addLayout(partie_lancement);
        partie_commande->addStretch(30);
        partie_commande->addWidget(button_run);


    QTextEdit *matrice_text = new QTextEdit("Matrice");
    matrice_text->setLineWrapMode(QTextEdit::NoWrap);
    matrice_text->setReadOnly(true);
    matrice_text->setFont(QFont("Courrier"));

    QTextEdit *affichage_programme = new QTextEdit("Affichage du programme");
    affichage_programme->setReadOnly(true);

    grid->addWidget(matrice_text,0,0);
    grid->addLayout(partie_commande,0,1);
    grid->addWidget(affichage_programme,1,0,1,2);

    grid->setColumnMinimumWidth(0,1000);
    grid->setColumnMinimumWidth(1,200);
    grid->setRowMinimumHeight(0,500);
    grid->setRowMinimumHeight(1,200);

    QProcess *main = new QProcess();
    main->setReadChannel(QProcess::StandardOutput);

    connecteur_programme *ui = new connecteur_programme(progress,caracteristique_graphe,pourcentage,file_name,affichage_programme,matrice_text,iteratif,main);

    QObject::connect(main,SIGNAL(readyReadStandardOutput()),ui,SLOT(affiche()));
    QObject::connect(button_run,SIGNAL(clicked()),ui,SLOT(run()));
    QObject::connect(button_choisir_graphe,SIGNAL(clicked()),ui,SLOT(choisir_graphe()));


    w.setMinimumSize(1350,700);
    w.show();

    return app.exec();
}
