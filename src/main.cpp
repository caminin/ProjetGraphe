#include "../include/graphe.hpp"
#include <cstdio>
#include <stdio.h>
#include <string.h>

using namespace std;

int parseCommandLine(int argc, char* argv[])
{
	int int_return;
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
	
	}
		   
	return int_return;
}

void runProgramme(int pourcentage)
{
	graphe g;
	g.readFile();
	g.affichageMatrice();
	int i=0,j=0;
	for(auto n:g.mat[53])
	{
		if(n==1)
			i++;
		else j++;
	}
	cout << "jai trouvé : " << i << " 1 et "<< j << " 0"<<endl;
	
	vector<int> same;
	g.getSameElement(0,1,same);
	for(auto n:same)
	{
		cout << n << "|";
	}
	cout <<endl<<pourcentage << endl;
	
}


int main(int argc, char* argv[])
{
	
	int pourcentage=parseCommandLine(argc,argv);
	
	if(pourcentage!=-1)
	{
		runProgramme(pourcentage);
	}
	
	return 0;
}
