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

void graphe::affichageMatrice()
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



void graphe::readFile()
{
	ifstream fichier("graphe.txt");
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
			    
			    cout << "Arc : " << nb_arcs <<", Sommets : " << nb_sommets << endl;
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
	for (int i = 0; i < nb_sommets; ++i) {
		if (mat[element][i] == 1) result.push_back(i);
	}
	return result;
}


int graphe::getMaxArcCountElement(vector< pair< int, vector<int> > > sous_graphe) {
	int nb_arc = -1;
	int res;
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
	for (unsigned int i = 0; i < sommets_a_traiter.size(); ++i) {
		vector<int> tmp; 
		for (unsigned int j = 0; j < sommets_a_traiter.size(); ++j) {
			tmp.push_back(mat[sommets_a_traiter[i]][sommets_a_traiter[j]]);
		}
		result.push_back(make_pair(sommets_a_traiter[i], tmp));
	}
	return result;
}


vector< pair< int, vector<int> > > graphe::sousGraphe2(int element, vector< pair< int, vector<int> > > sous_graphe) {
	vector< pair< int, vector<int> > > result;
	vector<int> sommets_a_traiter;
	
	for (unsigned int i = 0; i < sous_graphe.size(); ++i) {
		if (sous_graphe[i].first == element) {
			for (unsigned int j = 0; j < sous_graphe[i].second.size(); ++j) {
				if (sous_graphe[i].second[j] == 1) sommets_a_traiter.push_back(sous_graphe[j].first);
			}
			break;
		}
	}
		
	for (unsigned int i = 0; i < sommets_a_traiter.size(); ++i) {
		vector<int> tmp; 
		for (unsigned int j = 0; j < sommets_a_traiter.size(); ++j) {
			tmp.push_back(mat[sommets_a_traiter[i]][sommets_a_traiter[j]]);
		}
		result.push_back(make_pair(sommets_a_traiter[i], tmp));
	}
	return result;
}


void graphe::rechercheClique(int sommet, vector<int> &clique_en_cours, vector< pair< int, vector<int> > > &sous_graphe) {
	if (isComplete(sous_graphe)) {
		for (auto n:sous_graphe) clique_en_cours.push_back(n.first);
	}
	else {
		sous_graphe = sousGraphe2(sommet, sous_graphe);
		int tmp = getMaxArcCountElement(sous_graphe);
		clique_en_cours.push_back(tmp);
		rechercheClique(tmp, clique_en_cours, sous_graphe);
	}
}

void graphe::runRechercheClique(int pourcentage) {
	vector<int> clique_maximale;
	vector< pair<int, int> > liste_element_ordonnee = getElementSortedByArcCount();
	int nb_sommets_a_traiter = (int)(nb_sommets * pourcentage)/100;
	for (int i = 0; i < nb_sommets_a_traiter; ++i) {
		vector < pair< int, vector<int> > > sous_graphe = sousGraphe(liste_element_ordonnee[i].first);
		vector<int> clique_en_cours;
		rechercheClique(getMaxArcCountElement(sous_graphe), clique_en_cours, sous_graphe);
		if (clique_en_cours.size() > clique_maximale.size()) {
			clique_maximale = clique_en_cours;
			cout << "Changement de clique maximale" << endl;
		}
	}
	cout << "Clique maximale trouvé jusqu'à maintenant (" << clique_maximale.size() << " éléments) : ";
	sort(clique_maximale.begin(), clique_maximale.end(), [](int a, int b){return a < b;});
	for (auto i:clique_maximale) cout << i << " ";
	cout << endl; 
}

