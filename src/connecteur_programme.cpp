#include "connecteur_programme.h"

connecteur_programme::connecteur_programme(QProgressBar * pr,QTextEdit * car_graphe,QLineEdit *pourc,QTextEdit *file,QTextEdit *aff, QTextEdit *mat,QRadioButton *it, QProcess *p):progress(pr),caracteristique_graphe(car_graphe),pourcentage(pourc),file_url(file),iteratif(it),proc(p),matrice_text(mat),affichage_programme(aff)
{

}

connecteur_programme::~connecteur_programme()
{
}

void connecteur_programme::run()
{
    if(file_url->toPlainText()=="")
    {
        QString s1="Erreur de lancement de programme";
        QString s2="Le fichier n'est pas reconnu, veuillez en choisir un";
        QMessageBox::warning(matrice_text,s1,s2);
    }
    else
    {
        QString algo;
        if(iteratif->isChecked())
        {
            algo="iteratif";
        }
        else
        {
            algo="récursif";
        }
        QString nomProg = "./bin/prog.exe ";
        QString s=pourcentage->text() ;
        nomProg=nomProg+s+" "+file_url->toPlainText()+" "+algo;
        affichage_programme->clear();
        affichage_programme->setText("Lancement du Programme avec comme pourcentage : "+s+" en "+algo);
        proc->start(nomProg);
    }

}

void connecteur_programme::affiche()
{

    QString s(proc->readAllStandardOutput().data());
    QStringList lignes(s.split("\n"));

    for (int i = 0; i < lignes.size(); ++i)
    {
        if (lignes[i].startsWith("|"))
            matrice_text->append(lignes[i]);
        else if(lignes[i].startsWith("~"))
        {
            caracteristique_graphe->append(lignes[i].remove(0,1));
        }
        else if(lignes[i].startsWith("_"))
        {
            QString s=lignes[i].remove(0,1);
            int nombre=s.toInt();
            progress->setValue(nombre);
        }
        else{
            if(lignes[i]!="")
                affichage_programme->append(lignes[i]);
        }
    }
}

void connecteur_programme::choisir_graphe()
{
    QUrl url_file = QFileDialog::getOpenFileUrl(0,"Selectionner un graphe");
    file_url->setText(url_file.path());

    affichage_programme->setText("");
    matrice_text->setText("");
    QString nomProg = "./bin/prog.exe affichage ";

    affichage_programme->clear();
    caracteristique_graphe->setText("Caractéristiques du graphe");
    matrice_text->clear();
    proc->start(nomProg+file_url->toPlainText());

    affiche();

}
