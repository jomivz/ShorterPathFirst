#include "../inc/Graphe.h"
#include "../inc/Sommet.h"
#include "../inc/Tas.h"
#include "../inc/couleur.h"

#include<iostream>
#include<fstream>
#include<sstream>
#include<sys/types.h>// readdir(), opendir()
#include<sys/time.h>//getitimer() setitimer() 
#include<dirent.h> //struct dirent
#include<iomanip> //setw()
#include<string>
#include<vector>
#include<ctime>

using namespace std;

void DijkstraTas(Graphe& G,int src)
{
	vector<Sommet> VSom;
	vector<Sommet> VSomParcouru;
	Tas T(G.getNbSom()+1);
	
	int posCur=0;
	for(int i=0;i<G.getNbSom();++i)
		if(G[i].getNumSom()==src)
		{
			VSom.push_back(G[i]);
			posCur=i;
			break;
		}
			
	while(VSomParcouru.size() < G.getNbSom())
	{
		//pour tous les successeurs d'un sommet
		for(int i=0;i < G[posCur].size();++i)
		{
			//on recupere le sommet G[posNext] correspond au successeur de G[posCur]
			int posNext=0;
			for(int j=0; j < G.getNbSom(); ++j)
				if(G[j].getNumSom()==G[posCur][i].getNumSom()) 
				{ posNext=j;	break;}

			//cherche le sommet G[posNext] dans VSom
			bool isSeen = false;
			int pos=0;
			for( ;pos<VSom.size();++pos)
			{
				if (G[posNext].getNumSom() == VSom[pos].getNumSom())
					{isSeen = true; break;}
			}
			int d = G[posCur].getDist()+G[posCur][i].getPond();
			if(!isSeen)
			{
				G[posNext].setDist(d); 
				G[posNext].setPred(G[posCur]);
				VSom.push_back(G[posNext]);
			}
			else if(VSom[pos].getDist()>d)
			{
				G[posNext].setDist(d);
				G[posNext].setPred(G[posCur]);
				VSom[pos].setDist(d); 
			}
		}	
		//Sommet St parcouru (ajout dans le vecteur des sommets parcouru)
		VSomParcouru.push_back(G[posCur]);
		//calcul du Tas
		T.construire(VSom,VSomParcouru);
		cout << T.getPrem() << endl;
		for (int k=0; k<G.getNbSom();++k)
			if (G[k].getNumSom()== T.getPrem())
			{
				posCur = k;
				break;
			}
		cout << "sommet courant : " << G[posCur].getNumSom() << endl;
	}//while
	//T.~Tas();
}//Dijkstra tas

int main(int argc, char **argv)
{
	const char* ficSrc = "g1.txt";
	Graphe G(ficSrc);
	cout << "\n+++ " << PROUGE << "Graphe genere a partir de \"" 
		 << ficSrc  << "\" " << PNOIR << "+++" << endl; 
	DijkstraTas(G,1);
	cout << G.getShorterPath(7) << endl;

	return 0;
}
