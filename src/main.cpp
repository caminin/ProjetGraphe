#include "../include/graphe.hpp"


int main()
{
	graphe g;
	g.readFile();
	g.affichageMatrice();
	pair<int,int> p=g.maxElement();
	cout << (get<0>(p)) << "|" << (get<1>(p)) << endl;
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
	cout << endl;
	return 0;
}
