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

bool graphe::isComplete(vector< vector<int> > &mymat)
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
			if(countRow(n)!=(n.size()-1))
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

cout << "ssdfsdf" << endl;
