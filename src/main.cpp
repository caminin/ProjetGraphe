#include "../include/graphe.hpp"
#include <cstdio>
#include <stdio.h>
#include <string.h>

using namespace std;

pair<int,string> parseCommandLine(int argc, char* argv[])
{
	int int_return;
	string file_name="";
	if(argc<2)
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

void runProgramme(int pourcentage,string file_name)
{
	graphe g;
	g.readFile(file_name);
	g.affichageMatrice();
	pourcentage++;//pour éviter le warning qui dit que pourncetage n'est pas utilisé'
}


int main(int argc, char* argv[])
{
	
	pair<int,string> resParceCommand=parseCommandLine(argc,argv);
	
	if(resParceCommand.first!=-1)
	{
		runProgramme(resParceCommand.first,resParceCommand.second);
	}
	
	return 0;
}
