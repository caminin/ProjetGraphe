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
	for(vector<char> vec:mat)
	{
		cout << "|";
		for (char nb:vec)
		{
			cout << static_cast<int>(nb);
		}
		
		cout << "|" << endl;
	}
	cout << "La matrice chargée est de taille " << nb_sommets << endl;
	cout << "~______________" << endl;
	cout << "~Il a : " << nb_arcs << " Arcs" << endl;
	cout << "~Il a : " << nb_sommets << " Sommets" << endl;
	cout << "~Il a une densité de  " << (int)((double)(nb_arcs)/((double)(nb_sommets)*(double)(nb_sommets)/2)*100.0) << " %" << endl;
}

unsigned int graphe::countRow(vector<char> &row)
{
	unsigned int i=0;
	for(auto e:row)
	{
		if(e==1)
			i++;
	}
	return i;
}

bool graphe::isComplete(vector< pair< int, vector<char> > > &mymat)
{
	bool res=true;
	if (mymat.size()<2)
	{
		res=true;
	}
	else
	{
		/*
		 * On parcours tout
		 */
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
		list_node.push_back(make_pair(i, countRow(mat[i])));
	}
	
	std::sort(list_node.begin(),list_node.end(),sortVectorPair);
		
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
		
		// On parcours toute les lignes du fichier du graphe
		while(getline(fichier,line))
		{
			/*
			 * Si la ligne commence par un 'p' on récupère les informations sur le nombre de sommets et d'arc du graphe,
			 * et on redimensionne la matrice avec les bonnes dimensions 
			 */
		    if(line[0]=='p')
		    {
			    vector<string> nb_string;
			    Split(nb_string,line,' ');
			    
			    if(nb_string[2]!="")
			    {
					 istringstream iss(nb_string[2]);
					 iss>>nb_sommets;
					 if(nb_string[2]!="")
					 {
						 istringstream iss2(nb_string[3]);
						 iss2>>nb_arcs;
						 mat.resize(nb_sommets,vector<char>(nb_sommets,0));
					 }
					 else
					 {
						 cout << "|Erreur lors du chargement, veuillez vérifier le fichier" << endl;
						 break;
					 }
			    }
			    else
			    {
				    cout << "|Erreur lors du chargement, veuillez vérifier le fichier" << endl;
				    break;
			    }
		    }
		    /*
		     * Pour toute les autres lignes commecant par un 'e' et représentant un arc du graphe, on ajoute cet arc à la matrice
		     */
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


int graphe::getMaxArcCountElement(vector< pair< int, vector<char> > > &sous_graphe) {
	int nb_arc = -1;
	int res;
	/*
	 * On parcours la matrice pour trouver le sommet qui possède le plus d'arcs le liant à d'autres sommets
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



vector< pair< int, vector<char> > > graphe::sousGraphe(int element) {
	vector< pair< int, vector<char> > > result;
	vector<int> sommets_a_traiter = getLinkElement(element);
	/*
	 * On parcours la matrice et on stocke dans une sous-matrice les éléments qui 
	 * sont liés au sommet choisis (ici element). Chaque pair contient en entier correspondant
	 * à l'identifiant du sommet dans la matrice principale, et un vecteur d'entiers (0 ou 1)
	 * correspondant à la présence ou l'absence d'arc entre ce sommet et les autres de la 
	 * sous-matrice.
	 */
	for (unsigned int i = 0; i < sommets_a_traiter.size(); ++i) {
		vector<char> tmp; 
		for (unsigned int j = 0; j < sommets_a_traiter.size(); ++j) {
			tmp.push_back(mat[sommets_a_traiter[i]][sommets_a_traiter[j]]);
		}
		result.push_back(make_pair(sommets_a_traiter[i], tmp));
	}
	return result;
}


vector< pair< int, vector<char> > > graphe::sousGraphe2(int element, vector< pair< int, vector<char> > > &sous_graphe) {
	vector< pair< int, vector<char> > > result;

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
		vector<char> tmp; 
		for (unsigned int j = 0; j < sommets_a_traiter.size(); ++j) {
			tmp.push_back(mat[sommets_a_traiter[i]][sommets_a_traiter[j]]);
		}
		result.push_back(make_pair(sommets_a_traiter[i], tmp));
	}
	return result;
}


void graphe::rechercheCliqueRecursive(vector<int> &clique_en_cours, vector< pair< int, vector<char> > > &sous_graphe, int taille_clique_maximale) {
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
	 
	else if (static_cast<int>(clique_en_cours.size() + sous_graphe.size()) > taille_clique_maximale) {
		int meilleur_sommet = getMaxArcCountElement(sous_graphe);
		clique_en_cours.push_back(meilleur_sommet);
		sous_graphe = sousGraphe2(meilleur_sommet, sous_graphe);
		rechercheCliqueRecursive(clique_en_cours, sous_graphe, taille_clique_maximale);
	}
}


vector<int> graphe::rechercheCliqueIteratif(int sommet, int taille_clique_maximale) {
	vector <int> clique_en_cours;
	vector< pair <int, vector <char> > > sous_graphe;
	sous_graphe = sousGraphe(sommet);
	clique_en_cours.push_back(sommet);
	
	while ((!isComplete(sous_graphe)) && (taille_clique_maximale <= static_cast<int>(clique_en_cours.size() + sous_graphe.size()) ) ) {
		int meilleur_sommet = getMaxArcCountElement(sous_graphe);
		clique_en_cours.push_back(meilleur_sommet);
		sous_graphe = sousGraphe2(meilleur_sommet, sous_graphe); 
	}
	for (auto n:sous_graphe) clique_en_cours.push_back(n.first);
	return clique_en_cours;
}

void graphe::runRechercheCliqueRecursive(int pourcentage) {
	vector<int> clique_maximale;
	/*
	 * On récupère la liste des sommets de la matrice, trié en fonction de celui possèdant le plus d'arcs, à celui en possédant le moins.
	 */
	vector< pair<int, int> > liste_element_ordonnee = getElementSortedByArcCount();
	
	/*
	 * On calcule en fonction du pourcentage indiqué, combien de sommets y a t-il à traiter
	 */
	int nb_sommets_a_traiter = (int)(nb_sommets * pourcentage)/100;
	Chrono mychrono(0,"milliseconds");
	mychrono.start();
	
	/*
	 * Pour chaque sommet du graphe, on applique la fonction récursive qui modifiera la variable clique_en_cours. 
	 * Ensuite, si la clique trouvé pour ce sommet est plus grande que la plus grande clique trouvé jusqu'à maintenant, 
	 * on remplace la clique maximale par cette clique. 
	 */
	for (int i = 0; i < nb_sommets_a_traiter; ++i) {
		
		vector < pair< int, vector<char> > > sous_graphe = sousGraphe(liste_element_ordonnee[i].first);
		vector<int> clique_en_cours;
		clique_en_cours.push_back(liste_element_ordonnee[i].first);
		rechercheCliqueRecursive(clique_en_cours, sous_graphe, clique_maximale.size());
		
		if (clique_en_cours.size() > clique_maximale.size()) {
			mychrono.stop();
			changementDeClique(mychrono,clique_maximale,clique_en_cours);
			mychrono.start();
		}
		mychrono.stop();
		cout << "_" +to_string(i*100/nb_sommets_a_traiter)<<endl;
		mychrono.start();
	}
	
	mychrono.stop();
	endAlgo(mychrono,clique_maximale);

}

void graphe::runRechercheCliqueIteratif(int pourcentage) {
	vector<int> clique_maximale;
	vector< pair<int, int> > liste_element_ordonnee = getElementSortedByArcCount();
	/*
	 * On calcule en fonction du pourcentage indiqué, combien de sommets y a t-il à traiter
	 */
	int nb_sommets_a_traiter = (int)(nb_sommets * pourcentage)/100;
	Chrono mychrono(0, "milliseconds");
	mychrono.start();
	
	/*
	 * Pour chaque sommet du graphe, on applique la fonction itérative qui nous renverra la clique maximale trouvée par ce sommet. 
	 * Ensuite, si la clique trouvé pour ce sommet est plus grande que la plus grande clique trouvé jusqu'à maintenant, 
	 * on remplace la clique maximale par cette clique. 
	 */
	for (int i = 0; i < nb_sommets_a_traiter; ++i) {
		vector<int> clique_en_cours = rechercheCliqueIteratif(liste_element_ordonnee[i].first, clique_maximale.size());
		if (clique_en_cours.size() > clique_maximale.size()) {
			mychrono.stop();
			changementDeClique(mychrono,clique_maximale,clique_en_cours);
			mychrono.start();
		}
		mychrono.stop();
		cout << "_" +to_string(i*100/nb_sommets_a_traiter)<<endl;
		mychrono.start();
	}
	
	mychrono.stop();
	endAlgo(mychrono,clique_maximale);
	
}

void graphe::endAlgo(Chrono &myChrono,vector<int> &clique_maximale)
{
	/*
	 * On affiche le temps de calcul requis ainsi que tous les éléments triés par ordre croissant présent dans la clique maximale trouvée. 
	 */
	cout << "_100" << endl;
	cout << "<";
	for(int j=0;j<256;j++)
	{
		cout << "-";
	}	
	cout << ">" << endl;
	cout << "Résultat : " << endl;
	isCliqueMaximale(clique_maximale);
	cout << "Le temps de calcul est de " << (myChrono.getDuration()/1000) <<" seconds" <<  endl;
	cout << "La clique maximale trouvée est de " << clique_maximale.size() << " éléments : ";
	sort(clique_maximale.begin(), clique_maximale.end(), [](int a, int b){return a < b;});
	for (auto i:clique_maximale) cout << i << " ";
	cout << endl; 
}

void graphe::changementDeClique(Chrono &myChrono,vector<int> &clique_maximale,vector<int> &clique_en_cours)
{
	cout << "Je change de clique actuelle. Je passe d'une clique de taille "<< clique_maximale.size()<<" : "<<endl;
	sort(clique_maximale.begin(), clique_maximale.end(), [](int a, int b){return a < b;});
	for(auto n:clique_maximale)
		cout << n << " ";
	cout << endl;
	myChrono.start();
	clique_maximale = clique_en_cours;
	myChrono.stop();
	cout << "À une clique de taille " << clique_maximale.size() << " : " << endl;
	for (auto i:clique_maximale) cout << i << " " ;
	cout << endl << "\t" << endl;
}


void graphe::isCliqueMaximale(vector <int> &clique)
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
		if(isClique(clique))
		{
			if(tmp.size()==0	)
				cout << "Le sous-graphe est une clique maximale" << endl;
			else
			{
				cout << "La sous-graphe trouvée n'est pas maximale" << endl;
			}
		}
		else
		{
			cout << "Le sous-graphe n'est pas une clique !"<<endl;
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
	}
}

bool graphe::isClique(vector <int> &sous_graphe)
{
	bool res=true;
	for(auto n:sous_graphe)
	{
		for (auto m:sous_graphe)
		{
			if(m!=n)
			{
				if(mat[m][n]==0)
				{
					res=false;
				}
			}
		}
	}
	
	return res;
}


