#ifndef CONNECTEUR_PROGRAMME
#define CONNECTEUR_PROGRAMME

#include <QtGui>
#include <QTextEdit>
#include <QLineEdit>
#include <QObject>
#include <QSpinBox>
#include <QApplication>
#include <QHBoxLayout>
#include <QSplitter>
#include <QTextCodec>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QRadioButton>
#include <QProgressBar>
#include <cstdio>
#include <iostream>
using namespace std;

class connecteur_programme : public QObject
{
Q_OBJECT
private slots:
    void affiche();
    void run();
    void choisir_graphe();

public:
    connecteur_programme(QProgressBar * ,QTextEdit *,QLineEdit *,QTextEdit *,QTextEdit *, QTextEdit *,QRadioButton *,QProcess *);
    ~connecteur_programme();

private:
    QProgressBar * progress;
    QTextEdit * caracteristique_graphe;
    QLineEdit *pourcentage;
    QTextEdit *file_url;

    QRadioButton *iteratif;
    QProcess *proc;
    QTextEdit *matrice_text;    
    QTextEdit *affichage_programme;

};


#endif // CONNECTEUR_PROGRAMME

