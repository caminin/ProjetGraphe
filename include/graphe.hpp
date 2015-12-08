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
#include <set>
#include "chrono.hpp"

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
	
	bool isComplete(vector< pair< int, vector<int> > > &mymat);
	//retourne si l'arbre est complet
	
	vector< pair<int,int> > getElementSortedByArcCount();
	//retourne une liste d'élément triés par avec le plus d'arc partants. Le premier est le nombre d'arcs, le deuxième le numéro du noeud
	
	void readFile(string file_name);	
	//lit un fichier et le rentre dans l'arbre
	
	vector<int> getLinkElement(int element);
	//Retourne la liste des éléments ayant un arc avec l'élement choisis
	
	int getMaxArcCountElement(vector< pair< int, vector<int> > > &sous_graphe);
	//Retourne l'élément possédant le plus d'arc dans un sous graphe
	
	vector< pair< int, vector<int> > > sousGraphe(int element);
	//Lit la matrice et retourne une matrice plus petite, limitée aux sommets ayant un arc avec l'élement choisis
	
	vector< pair< int, vector<int> > > sousGraphe2(int element, vector< pair< int, vector<int> > > &sous_graphe);
	//Lit un sous-graphe et retourne une matrice plus petite, limitée aux sommets ayant un arc avec l'élement choisis
	
	void rechercheCliqueRecursive(vector<int> &clique_en_cours, vector< pair< int, vector<int> > > &sous_graphe);
	//Recherche récursivement une clique dans la matrice et la stocke dans clique_en_cours
	
	vector<int> rechercheCliqueIteratif(int sommet);
	//Recherche une clique de manière itérative et la renvoi en ne prenant en compte que le sous-graphe lié au sommet passé en paramètre
	
	void runRechercheCliqueRecursive(int pourcentage);
	//Execute la fonction récursive de recherche de clique en ne prenant en compte qu'un pourcentage des sommets ayant le plus d'arcs	
	
	void runRechercheCliqueIteratif(int pourcentage);
	//Execute la fonction itérative de recherche de clique
	
	void verifClique(vector <int> &clique);
	
	bool isClique(vector<int> &clique);
	
};

bool sortVectorPair(pair<int,int> p1, pair<int,int> p2);

#endif
