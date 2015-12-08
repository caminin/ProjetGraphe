#include "../include/graphe.hpp"
using namespace std;




int graphe::Split(vector<string>& vecteur, string chaine, char separateur)
{
	vecteur.clear();

	string::size_type stTemp = chaine.find(separateur);
	
	while(stTemp != string::npos)
	{
		vecteur.push_back(chaine.substr(0, stTemp));
		chaine = chaine.substr(stTemp + 1);
		stTemp = chaine.find(separateur);
	}
	vecteur.push_back(chaine);
	
	return vecteur.size();
}

void graphe::affichage()
{
	for(vector<int> vec:mat)
	{
		cout << "|";
		for (int nb:vec)
		{
			cout << nb;
		}
		
		cout << "|" << endl;
	}
	cout << "J'ai chargé une matrice de taille " << nb_sommets << endl;
	cout << "~______________" << endl;
	cout << "~Il a : " << nb_arcs << " Arcs" << endl;
	cout << "~Il a : " << nb_sommets << " Sommets" << endl;
	vector < pair<int,int> > sorted=getElementSortedByArcCount();
	cout << "~Le noeud : " << sorted[0].first << " a " << sorted[0].second << " sommets" <<  endl;
}

unsigned int graphe::countRow(vector<int> &row)
{
	unsigned int i=0;
	for(auto e:row)
	{
		if(e==1)
			i++;
	}
	return i;
}

vector<int>& graphe::getSameElement(unsigned int element1,unsigned int element2,vector<int> &same)
{
	same.clear();
	for(unsigned int i=0;i<mat.size();i++)
	{
		if((mat[element1][i]==1)&&(mat[element2][i]==1)&&element1!=i&&element2!=i)
		{
			same.push_back(i);
		}
	}
	return same;
}

bool graphe::isComplete(vector< pair< int, vector<int> > > &mymat)
{
	bool res=true;
	if (mymat.size()<2)
	{
		res=true;
	}
	else
	{
		for (auto n:mymat)
		{
			if(countRow(n.second)!=(n.second.size()-1))
			{
				res=false;
				return res;			
			}
		}
	}
	
	return res;
}

bool sortVectorPair(pair<int,int> p1, pair<int,int> p2)
{
	return (p1.second > p2.second);
}


vector< pair<int,int> > graphe::getElementSortedByArcCount()
{
	vector< pair<int,int> > list_node;
	for(unsigned int i=0;i<mat.size();i++)
	{
		list_node.push_back(make_pair(i,countRow(mat[i])));
	}
	
	std::sort(list_node.begin(),list_node.end(),sortVectorPair);
	
	//for(auto n:list_node)
	//	cout << (n.second) << "," << (n.first) << endl;
		
	return list_node;
}



void graphe::readFile(string file_name)
{
	ifstream fichier(file_name.c_str());
	if(!fichier) 
	{
		cerr << "Le fichier help n'existe pas" << endl;
	}
	else
	{
		string line;
		while(getline(fichier,line))
		{
		    if(line[0]=='p')
		    {
			    vector<string> nb_string;
			    Split(nb_string,line,' ');
			    
			    
			    istringstream iss(nb_string[2]);
			    iss>>nb_sommets;

			    istringstream iss2(nb_string[3]);
			    iss2>>nb_arcs;
			    
			    
			    
			    
			    mat.resize(nb_sommets,vector<int>(nb_sommets,0));
			    
		    }
		    else if (line[0]=='e')
		    {
			    int col_1;
			    int col_2;
			    vector<string> nb_string;
			    Split(nb_string,line,' ');
			    istringstream iss(nb_string[1]);
			    iss>>col_1;

			    istringstream iss2(nb_string[2]);
			    iss2>>col_2;
			    
			    mat[col_1-1][col_2-1]=1;
			    mat[col_2-1][col_1-1]=1;
			    
		    }
		}
		
	}
}


vector<int> graphe::getLinkElement(int element) {
	vector<int> result;
	/*
	 * On parcours la ligne de la matrice correspondant à l'élément, et dès qu'on trouve un arc
	 * qui le relie avec un autre sommet on rajoute ce sommet dans un vecteur
	 */
	for (int i = 0; i < nb_sommets; ++i) {
		if (mat[element][i] == 1) result.push_back(i);
	}
	return result;
}


int graphe::getMaxArcCountElement(vector< pair< int, vector<int> > > &sous_graphe) {
	int nb_arc = -1;
	int res;
	/*
	 * On parcours la matrice pour trouver le sommet qui possède le plus d'arcs avec d'autres sommets
	 * et on renvoi ce sommet
	 */
	for (unsigned int i = 0; i < sous_graphe.size(); ++i) {
		int tmp = countRow(sous_graphe[i].second);
		if (tmp > nb_arc) {
			 nb_arc = tmp;
			 res = sous_graphe[i].first;
		 }
	}
	return res;
}



vector< pair< int, vector<int> > > graphe::sousGraphe(int element) {
	vector< pair< int, vector<int> > > result;
	vector<int> sommets_a_traiter = getLinkElement(element);
	/*
	 * On parcours la matrice et on stocke dans une sous-matrice les éléments qui 
	 * sont liés au sommet choisis (ici element). Chaque pair contient en entier correspondant
	 * à l'identifiant du sommet dans la matrice principale, et un vecteur d'entiers (0 ou 1)
	 * correspondant à la présence ou l'absence d'arc entre ce sommet et les autres de la 
	 * sous-matrice.
	 */
	for (unsigned int i = 0; i < sommets_a_traiter.size(); ++i) {
		vector<int> tmp; 
		for (unsigned int j = 0; j < sommets_a_traiter.size(); ++j) {
			tmp.push_back(mat[sommets_a_traiter[i]][sommets_a_traiter[j]]);
		}
		result.push_back(make_pair(sommets_a_traiter[i], tmp));
	}
	return result;
}


vector< pair< int, vector<int> > > graphe::sousGraphe2(int element, vector< pair< int, vector<int> > > &sous_graphe) {
	vector< pair< int, vector<int> > > result;
	vector<int> sommets_a_traiter;
	
	/*
	 * On récupère dans un sous-graphe tout les sommets avec lequel element est relié.
	 */
	
	for (unsigned int i = 0; i < sous_graphe.size(); ++i) {
		if (sous_graphe[i].first == element) {
			for (unsigned int j = 0; j < sous_graphe[i].second.size(); ++j) {
				if (sous_graphe[i].second[j] == 1) sommets_a_traiter.push_back(sous_graphe[j].first);
			}
			break;
		}
	}
	
	/*
	 * On parcours ce sous-graphe, et comme pour la fonction sousGraphe on construit et
	 * on renvoi un autre sous-graphe composé exclusivement des sommets avec lequel element
	 * est relié. 
	 */
	 
	for (unsigned int i = 0; i < sommets_a_traiter.size(); ++i) {
		vector<int> tmp; 
		for (unsigned int j = 0; j < sommets_a_traiter.size(); ++j) {
			tmp.push_back(mat[sommets_a_traiter[i]][sommets_a_traiter[j]]);
		}
		result.push_back(make_pair(sommets_a_traiter[i], tmp));
	}
	return result;
}


void graphe::rechercheCliqueRecursive(vector<int> &clique_en_cours, vector< pair< int, vector<int> > > &sous_graphe) {
	/*
	 * On met comme cas d'arrêt de la fonction récursive que le sous_graphe en paramètre sois complet. 
	 * Dans ce cas on rajoute ses éléments dans clique_en_cours. 
	 */

	if (isComplete(sous_graphe)) {
		for (auto n:sous_graphe) 
			clique_en_cours.push_back(n.first);
	}
	
	/*
	 * Dans l'autres cas, c'est que clique_en_cours peut encore être agrandis. 
	 * sous_graphe devient le sous-graphe composé de tous les éléments étant présent
	 * dans sous_graphe, et étant lié à sommet.
	 * sommet devient le sommet possédant le plus d'arcs du nouveau sous-graphe
	 * Ce sommet est alors ajouté à clique_en_cours et on relance un appel à rechercheClique
	 */
	 
	else {
		int meilleur_sommet = getMaxArcCountElement(sous_graphe);
		clique_en_cours.push_back(meilleur_sommet);
		sous_graphe = sousGraphe2(meilleur_sommet, sous_graphe);
		rechercheCliqueRecursive(clique_en_cours, sous_graphe);
	}
}


vector<int> graphe::rechercheCliqueIteratif(int sommet) {
	vector <int> clique_en_cours;
	vector< pair <int, vector <int> > > sous_graphe;
	sous_graphe = sousGraphe(sommet);
	while (!isComplete(sous_graphe)) {
		int meilleur_sommet = getMaxArcCountElement(sous_graphe);
		clique_en_cours.push_back(meilleur_sommet);
		sous_graphe = sousGraphe2(meilleur_sommet, sous_graphe); 
	}
	for (auto n:sous_graphe) clique_en_cours.push_back(n.first);
	return clique_en_cours;
}

void graphe::runRechercheCliqueRecursive(int pourcentage) {
	vector<int> clique_maximale;
	vector< pair<int, int> > liste_element_ordonnee = getElementSortedByArcCount();
	int nb_sommets_a_traiter = (int)(nb_sommets * pourcentage)/100;
	Chrono mychrono(0,"milliseconds"),mychrono2(0,"nanoseconds");
	mychrono.start();
	for (int i = 0; i < nb_sommets_a_traiter; ++i) {
		
		vector < pair< int, vector<int> > > sous_graphe = sousGraphe(liste_element_ordonnee[i].first);
		vector<int> clique_en_cours;
		rechercheCliqueRecursive(clique_en_cours, sous_graphe);
		
		if (clique_en_cours.size() > clique_maximale.size()) {
			mychrono.stop();
			cout << "Passage de : "<<endl;
			sort(clique_maximale.begin(), clique_maximale.end(), [](int a, int b){return a < b;});
			for(auto n:clique_maximale)
				cout << n << " ";
			cout << endl;
			mychrono.start();
			
			clique_maximale = clique_en_cours;
			mychrono.stop();
			cout << "Changement de clique maximale :" << endl;
			sort(clique_maximale.begin(), clique_maximale.end(), [](int a, int b){return a < b;});
			for (auto i:clique_maximale) cout << i << " " ;
			cout << endl;
			mychrono.start();
		}
		mychrono.stop();
		cout << "_" +to_string(i*100/nb_sommets_a_traiter)<<endl;
		mychrono.start();
	}
	mychrono2.start();
	verifClique(clique_maximale);
	mychrono.stop();
	mychrono2.stop();
	cout << "temps algo supp " << (mychrono2.getDuration()/1000.0) <<" microseconds" << endl;
	cout << "_100" << endl;
	cout << "Temps de calcul : " << (mychrono.getDuration()/1000.0) <<" seconds" <<  endl;
	cout << "Clique maximale trouvé jusqu'à maintenant (" << clique_maximale.size() << " éléments) : ";
	sort(clique_maximale.begin(), clique_maximale.end(), [](int a, int b){return a < b;});
	for (auto i:clique_maximale) cout << i << " ";
	cout << endl; 
}

void graphe::runRechercheCliqueIteratif(int pourcentage) {
	vector<int> clique_maximale;
	vector< pair<int, int> > liste_element_ordonnee = getElementSortedByArcCount();
	int nb_sommets_a_traiter = (int)(nb_sommets * pourcentage)/100;
	Chrono mychrono(0,"milliseconds");
	mychrono.start();
	for (int i = 0; i < nb_sommets_a_traiter; ++i) {
		vector<int> clique_en_cours = rechercheCliqueIteratif(liste_element_ordonnee[i].first);
		if (clique_en_cours.size() > clique_maximale.size()) {
			mychrono.stop();
			cout << "Passage de : "<<endl;
			sort(clique_maximale.begin(), clique_maximale.end(), [](int a, int b){return a < b;});
			for(auto n:clique_maximale)
				cout << n << " ";
			cout << endl;
			mychrono.start();
				
			clique_maximale = clique_en_cours;
			mychrono.stop();
			cout << "Changement de clique maximale :" << endl;
			for (auto i:clique_maximale) cout << i << " " ;
			cout << endl;
			mychrono.start();
		}
		mychrono.stop();
		cout << "_" +to_string(i*100/nb_sommets_a_traiter)<<endl;
		mychrono.start();
	}
	mychrono.stop();
	cout << "_100" << endl;
	cout << "Temps de calcul : " << (mychrono.getDuration()/1000) <<" seconds" <<  endl;
	cout << "Clique maximale trouvé jusqu'à maintenant (" << clique_maximale.size() << " éléments) : ";
	sort(clique_maximale.begin(), clique_maximale.end(), [](int a, int b){return a < b;});
	for (auto i:clique_maximale) cout << i << " ";
	cout << endl; 
}



void graphe::verifClique(vector <int> &clique)
{
	if(clique.size()>2)
	{
		vector<int> totale;
		for(unsigned int i=0;i<mat[0].size();i++)
		{
			totale.push_back(1);
		} 
		
		for(auto n:clique)
		{
			for(int i=0;(unsigned int)i<mat[n].size();i++)
			{
				if(mat[n][i]==0 && (i!=n))
				{
					totale[i]=0;
				}
			}
		}
		
		//on parcours la clique et on enlève les éléments à 0, donc ceux que l'élément du moment n'a pas
		vector<int> tmp;
		for(unsigned int i=0;i<totale.size();i++)
		{
			if(totale[i]==1)
			{
				if(find(clique.begin(),clique.end(),i)==clique.end())
				{
					tmp.push_back(i);
				}
				
			}
		}
		for(auto n:tmp)
		{
			clique.push_back(n);
			if(isClique(clique))
			{
				cout << "Je rajoute " << n << endl;
			}
			else
			{
				clique.erase(clique.begin()+clique.size()-1);
			}
			
		}
		if(isClique(clique))
		{
			cout << "La clique est bien complète" << endl;
		}
		else
		{
			cout << "La clique n'est pas complète !" << endl;
		}
		
		
		
	}
}

bool graphe::isClique(vector <int> &clique)
{
	bool res=true;
	for(auto n:clique)
	{
		for (auto m:clique)
		{
			if(m!=n)
			{
				if(mat[m][n]==0)
				{
					res=false;
					//cout << "coordonne " << m <<","<<n<< endl;
				}
			}
		}
	}
	
	return res;
}


