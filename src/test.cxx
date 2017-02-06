#include "../inc/Graphe.h"
#include "../inc/GrapheGenerator.h"
#include "../inc/Sommet.h"
#include "../inc/menu.h"
#include "../inc/Timer.h"
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

void Dijkstra(Graphe& G,int src)
{
	vector<Sommet> VSom;
	vector<Sommet> VSomParcouru;
	
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
		//recherche le sommet de + petite distance non parcouru (dans VSom)
		int minDist=5000;
		for(int i=0;i<VSom.size(); ++i)
		{	
			bool parcouru=false;
			for(int j=0;j<VSomParcouru.size();++j)
				if (VSom[i].getNumSom()==VSomParcouru[j].getNumSom())
				{	
					parcouru = true;
					break;
				}
			if(!parcouru && minDist>VSom[i].getDist())
			{
				minDist=VSom[i].getDist();
				bool ok=true;
				for(int j=0;i<G.getNbSom() && ok;++j)
					if(G[j].getNumSom()==VSom[i].getNumSom())
						{posCur=j;ok=false;}
			}
		}
	}//while
}
void DijkstraTas(Graphe& G,int src)
{
	vector<Sommet> VSom;
	vector<Sommet> VSomParcouru;
	Tas T(G.getNbSom());
	
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
		for (int k=0; k<G.getNbSom();++k)
			if (G[k].getNumSom()== T.getPrem())
			{
				posCur = k;
				break;
			}
	}//while
}//Dijkstra tas
void FordBellman(Graphe& G,int src)
{
	vector<int> VSom;
	vector<int> VSomParcouru;

	int posCur=0;
	for(int k=0;k<G.getNbSom();++k)
		if(G[k].getNumSom()==src)
		{
			VSom.push_back(G[k].getNumSom());
			posCur=k;
			break;
		}
		
	while(VSom.size()>0)
	{
			vector<int>::iterator iter=VSom.begin();
			for(int i=0;i<G.getNbSom();++i)
				if(G[i].getNumSom() == *iter)
				{
					posCur=i;
					break;
				}
			for(int j=0;j<G[posCur].size();++j)
			{
				int posNext=0;
				for(int l=0;l<G.getNbSom();++l)
					if(G[l].getNumSom()==G[posCur][j].getNumSom())
					{
						posNext=l;
						bool parcouru = false;
						for(int p=0;p<VSomParcouru.size();++p)
							if (VSomParcouru[p]==G[posNext].getNumSom())
							{
								parcouru = true; 
								break;
							}
						int d = G[posCur].getDist()+G[posCur][j].getPond();
						if (!parcouru)
						{
							G[posNext].setDist(d); 
							G[posNext].setPred(G[posCur]);
							VSom.push_back(G[posNext].getNumSom());//ajout des Successeur dans VSom
						}
						else if(G[posNext].getDist()>d)
						{
							G[posNext].setDist(d);
							G[posNext].setPred(G[posCur]);
						}
					}
			}
			VSomParcouru.push_back(G[posCur].getNumSom());
			VSom.erase(VSom.begin());
	}//while
}//FordBellman()
int nbArete(int densite, int nbsom){
	return densite*(nbsom-1)*nbsom/200;
}


int main(int argc, char **argv)
{
	ofstream of("test.txt");
	Timer T;
	int nbSom=50;
	int nbAr=0;

	for (int dens=10 ; dens < 100 ; dens += 10)
	{
		of << nbSom << ' ' << dens << ' ';
		nbAr = nbArete(dens,nbSom);
		GrapheAlea(nbSom,nbAr);
		Graphe G("GrapheAlea.txt");

		T.start();
		FordBellman(G,1);
		T.stop();
		of << T.getTime() << ' ';

		T.start();
		Dijkstra(G,1);
		T.stop();
		of << T.getTime() << ' ';

		T.start();
		DijkstraTas(G,1);
		T.stop();
		of << T.getTime() << endl;
	}
	nbSom=200;
	for (int dens=10 ; dens < 100 ; dens += 10)
	{
		of << nbSom << ' ' << dens << ' ';
		nbAr = nbArete(dens,nbSom);
		GrapheAlea(nbSom,nbAr);
		Graphe G("GrapheAlea.txt");

		T.start();
		FordBellman(G,1);
		T.stop();
		of << T.getTime() << ' ';

		T.start();
		Dijkstra(G,1);
		T.stop();
		of << T.getTime() << ' ';

		T.start();
		DijkstraTas(G,1);
		T.stop();
		of << T.getTime() << endl;
	}
}
