#include "../include/graphe.hpp"
#include <cstdio>
#include <stdio.h>
#include <string.h>

using namespace std;

pair<int,string> parseCommandLine(int argc, char* argv[])
{
	int int_return;
	string file_name="";
	if(argc<3)
	{
	  std::cout << "Donnez un nombre entre 0 et 100, --help pour plus d'info" << std::endl;
	  int_return=-1;
	}
	else if(strcmp(argv[1],"--help")==0)
	{
	  std::ifstream fichier("help.txt");
	  if(!fichier) 
	  {
		   std::cerr << "Le fichier help n'existe pas" << std::endl;
	  }
	  else
	  {
		   std::string line;
		   while(std::getline(fichier,line))
		   {
		       std::cout << line << std::endl;
		   }
	  }
	  int_return=-1;
	}
	else if(strcmp(argv[1],"affichage")==0)
	{
		for(unsigned int i=0;i<strlen(argv[2]);i++)
		{
			file_name+=argv[2][i];
		}
		int_return =-2;
	}
	else
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
		   
	return make_pair(int_return,file_name);
}


void runAffichage(string file_name)
{
	graphe g;
	g.readFile(file_name);
	g.affichage();
}


void runProgramme(int pourcentage, string file_name)
{
	graphe g;
	g.readFile(file_name);
	 // A changer en fonction de la manière dont on veux rechercher la clique
	 
	g.runRechercheCliqueRecursive(pourcentage);
	//g.runRechercheCliqueIteratif(pourcentage);

}


int main(int argc, char* argv[])
{
	
	pair<int,string> resParceCommand=parseCommandLine(argc,argv);
	
	if(resParceCommand.first>=0)
	{
		runProgramme(resParceCommand.first, resParceCommand.second);
	}
	else if(resParceCommand.first==-2)
	{
		runAffichage(resParceCommand.second);
	}
	
	return 0;
}
