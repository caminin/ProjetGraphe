#include "../include/graphe.hpp"
#include <cstdio>
#include <stdio.h>
#include <string.h>

using namespace std;

/*
*	Permet de parser les arguments en ligne de commande.
*	Renvoie les éléments nécessaires au lancement du programme 
*	pair<int,string> = pair du pourcentage entré et du choix de l'algo("it ou rec")'
*
*/
pair<int,string> parseCommandLine(int argc, char* argv[])
{
	int int_return;
	string file_name="";
	if(argc<3)//si le nombre d'arguments n'est pas suffisant
	{
	  std::cout << "Donnez un nombre entre 0 et 100" << std::endl;
	  int_return=-1;
	}
	else if(strcmp(argv[1],"affichage")==0)//si on est en mode affichage
	{
		for(unsigned int i=0;i<strlen(argv[2]);i++)
		{
			file_name+=argv[2][i];
		}
		int_return =-2;
	}
	else 
	{
		if(argc<4)//s'il manque des arguments pour le mode calcul
		{
			cout << "Il manque des arguments, la forme est 'prog pourcentage nom_fichier algo'" << endl;
		}
		else//récupère le pourcentage et le type d'algo'
		{
			float puissance=1;
			float nombre=0;
			for(int j=strlen(argv[1])-1;j>=0;j--)
			{
				nombre=nombre+(argv[1][j]-48)*puissance;
				puissance*=10;
			}
			if(nombre>=0 && nombre<=100)
			{
				int_return=nombre;
			}
			else
			{
				cout << "Le nombre doit être compris entre 0 et 100" << endl;
				int_return=-1;
			}
		
			for(unsigned int i=0;i<strlen(argv[2]);i++)
			{
				file_name+=argv[2][i];
			}
		}
	
	}
		   
	return make_pair(int_return,file_name);
}


void runAffichage(string file_name)//lance l'affichage'
{
	graphe g;
	g.readFile(file_name);
	g.affichage();
}


void runProgramme(int pourcentage, string file_name, bool isIteratif)//lance le calcul
{
	graphe g;
	g.readFile(file_name);

	if(isIteratif)
	{
		g.runRechercheCliqueIteratif(pourcentage);
	}
	else
	{
		g.runRechercheCliqueRecursive(pourcentage);
	}		
}


int main(int argc, char* argv[])
{
	
	pair<int,string> resParceCommand=parseCommandLine(argc,argv);
	
	if(resParceCommand.first>=0)//si le retour est un nombre équivalent à un pourcentage
	{
		runProgramme(resParceCommand.first, resParceCommand.second, (strcmp(argv[3], "iteratif")==0));
	}
	else if(resParceCommand.first==-2)//si le retour est le nombre correspondant à affichage
	{
		runAffichage(resParceCommand.second);
	}
	
	return 0;
}
