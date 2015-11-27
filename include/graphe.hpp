#ifndef GRAPHE
#define GRAPHE

#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <ctime>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <map>

using namespace std;


class graphe
{
	public:
	int nb_sommets;//nombre de sommets de l'arbre
	int nb_arcs;//nombre d'arc de l'arbre
	vector< vector<int> > mat;// matrice d'adjacence de l'arbre
	
	int Split(vector<string>& vecteur, string chaine, char separateur); 
	//Prend une chaine de caractère et la sépare en plusieurs chaines en fonction du séparateur
	
	void affichageMatrice();
	//Affiche une matrice d'adjacence
	
	unsigned int countRow(vector<int> &row);
	//Compte le nombre de 1 sur la ligne
	
	vector<int>& getSameElement(unsigned int element1,unsigned int element2,vector<int> &same);
	//Redonne tous les éléments que element1 et element 2 ont en commun, sauf element1 et element2 et les stockent dans same
	
	bool isComplete(vector< vector<int> > &mymat);
	//retourne si l'arbre est complet
	
	vector < pair<int,int> > getElementWithMaxArc();
	//retourne l'élément avec le plus d'arc partant
	
	void readFile();	
	//lit un fichier et le rentre dans l'arbre
};


#endif
