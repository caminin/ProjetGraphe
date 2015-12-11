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
	int nb_sommets;//nombre de sommets du graphe
	int nb_arcs;//nombre d'arc du graphe
	vector< vector<char> > mat;// matrice d'adjacence du graphe
	
	int Split(vector<string>& vecteur, string chaine, char separateur); 
	//Prend une chaine de caractère et la sépare en plusieurs chaines en fonction du séparateur
	
	void affichage();
	//Affiche la matrice représentant le graphe dans l'ui
	
	unsigned int countRow(vector<char> &row);
	//Compte le nombre de 1 sur la ligne de la matrice passé en paramètre
	
	bool isComplete(vector< pair< int, vector<char> > > &mymat);
	//Renvoi vrai ou faux selon si le sous graphe passé en paramètre est complet ou non
	
	vector< pair<int, int> > getElementSortedByArcCount();
	//Retourne la liste des sommets du graphe triés de manière décroissante en fonction du nombre d'arcs que chaque sommet possède.
	
	void readFile(string file_name);	
	//Lit un fichier de graphe et le rentre dans la matrice
	
	vector<int> getLinkElement(int element);
	//Retourne la liste des éléments ayant un arc avec l'élement choisis
	
	int getMaxArcCountElement(vector< pair< int, vector<char> > >& sous_graphe);
	//Retourne l'élément possédant le plus d'arc dans un sous graphe passé en paramètre
	
	vector< pair< int, vector<char> > > sousGraphe(int element);
	//Lit la matrice et retourne une matrice plus petite, limitée aux sommets ayant un arc avec l'élement choisis
	
	vector< pair< int, vector<char> > > sousGraphe2(int element, vector< pair< int, vector<char> > > &sous_graphe);
	//Lit un sous-graphe et retourne une matrice plus petite, limitée aux sommets ayant un arc avec l'élement choisis
	
	void rechercheCliqueRecursive(vector<int> &clique_en_cours, vector< pair< int, vector<char> > > &sous_graphe, int taille_clique_maximale);
	//Recherche une clique de manière récursive dans la matrice et la stocke dans clique_en_cours
	
	vector<int> rechercheCliqueIteratif(int sommet, int taille_clique_maximale);
	//Recherche une clique de manière itérative et la renvoi en ne prenant en compte que le sous-graphe lié au sommet passé en paramètre
	
	void runRechercheCliqueRecursive(int pourcentage);
	//Execute la fonction récursive de recherche de clique en ne prenant en compte qu'un pourcentage des sommets ayant le plus d'arcs	
	
	void runRechercheCliqueIteratif(int pourcentage);
	//Execute la fonction itérative de recherche de clique en ne prenant en compte qu'un pourcentage des sommets ayant le plus d'arcs
	
	void isCliqueMaximale(vector <int> &clique);
	//Cherche si la clique est maximale et affiche les éléments importants pour l'interface graphique. Utilise isClique, et ajoute un élément si la clique
	//n'est pas maximale
	
	bool isClique(vector<int> &sous_graphe);
	//Retourne si le sous-graphe est une clique
	
};

bool sortVectorPair(pair<int,int> p1, pair<int,int> p2);

#endif
