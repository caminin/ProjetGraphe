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
#include <algorithm> 
#include <utility>

using namespace std;


class graphe
{
	public:
	int nb_sommets;//nombre de sommets de l'arbre
	int nb_arcs;//nombre d'arc de l'arbre
	vector< vector<int> > mat;// matrice d'adjacence de l'arbre
	
	int Split(vector<string>& vecteur, string chaine, char separateur); 
	//Prend une chaine de caractère et la sépare en plusieurs chaines en fonction du séparateur
	
	void affichage();
	//Fonction pour afficher dans l'ui
	
	unsigned int countRow(vector<int> &row);
	//Compte le nombre de 1 sur la ligne
	
	vector<int>& getSameElement(unsigned int element1,unsigned int element2,vector<int> &same);
	//Redonne tous les éléments que element1 et element 2 ont en commun, sauf element1 et element2 et les stockent dans same
	
	bool isComplete(vector< vector<int> > &mymat);
	//retourne si l'arbre est complet
	
	vector< pair<int,int> > getElementSortedByArcCount();
	//retourne une liste d'élément triés par avec le plus d'arc partants. Le premier est le nombre d'arcs, le deuxième le numéro du noeud
	
	void readFile(string file_name);	
	//lit un fichier et le rentre dans l'arbre
	
};

bool sortVectorPair(pair<int,int> p1, pair<int,int> p2);

#endif
