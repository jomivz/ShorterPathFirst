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
#include<string.h> //strncmp()
#include<stdio.h> //strncmp()
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
	int SomCur;
	
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
				T.ajouter(G[posNext]);
			}
			else if(VSom[pos].getDist()>d)
			{
				G[posNext].setDist(d);
				G[posNext].setPred(G[posCur]);
				VSom[pos].setDist(d); 
				T.monter(G[posNext]);
			}
		}	
		//Sommet St parcouru (ajout dans le vecteur des sommets parcouru)
		VSomParcouru.push_back(G[posCur]);
		//calcul du Tas
		SomCur = T.getPrem();
		//T.affiche();
		for (int k=0; k<G.getNbSom();++k)
			if (G[k].getNumSom() == SomCur)
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

int main(int argc, char **argv)
{
	cout << CLEAR << PBLEU;
	cout << "\n\n\n\n\t******************************************************\n" 
	     << "\t*****    Bienvenue dans le monde des graphes   *******\n"
		 << "\t******************************************************\n\n" << endl;
	
	cout << "\t********************************************************\n"
		 << "\t*****************   MENU PRINCIPAL  ********************\n"
		 << "\t********************************************************\n\n"<<PNOIR
		 << "\t\t==> "<< PBLEU << "1" << PNOIR << " - Appliquer l'algo de Ford-Bellman\n"
		 << "\t\t==> "<< PBLEU << "2" << PNOIR << " - Appliquer l'algo de Dijkstra\n"
		 << "\t\t==> "<< PBLEU << "3" << PNOIR << " - Appliquer Dijkstra sur les tas\n"
		 << "\t\t==> "<< PBLEU << "4" << PNOIR << " - Sortir\n" << PBLEU
		 << "\t*********************************************************\n\n"
		 << PNOIR << endl;

	cout << "Entrer votre choix: ";
	int choix;
	cin >> choix;
	for( ; ; )
	{
	switch (choix)
	{
		case 1 :
			cout << CLEAR << PBLEU << endl;
			cout << "\t********************   FORD BELLMAN  *******************\n"
				 << "\t********************************************************\n\n"<<PNOIR
				 << "\t\t==> "<< PBLEU << "1" << PNOIR << " - Appliquer l'algo sur des graphes de test\n"
				 << "\t\t==> "<< PBLEU << "2" << PNOIR << " - Appliquer l'algo sur un graphe aleatoire\n"
				 << "\t\t==> "<< PBLEU << "3" << PNOIR << " - Appliquer l'algo un graphe complet\n"
				 << "\t\t==> "<< PBLEU << "4" << PNOIR << " - Sortir\n"<< PBLEU
				 << "\t********************************************************\n\n" 
				 << PNOIR << endl;
			int choixF;
			cout << "Entrer votre choix: ";
			cin >> choixF;
			if (choixF == 1)
			{
					char ficSrc[30];
					string path = "./graph/";
					cout << "Entrer le nom du fichier source : ";
					cin >> ficSrc;
					bool existingFic=false;
					struct dirent *entry;
					DIR *rep;
					rep = opendir(path.c_str());
					while ( (entry=readdir(rep))) 
					{
						if(!strncmp(entry->d_name,ficSrc,entry->d_reclen))
						{
							existingFic = true;	
							closedir(rep);
						}
					}
					if(!existingFic)
					{
						cout <<"\n+++ \"" << PROUGE 
							 << ficSrc << "\" non trouve " << PNOIR << "+++" << endl; 
						cout <<"le fichier doit etre dans le sous-repertoire ./graph" << endl;
					}
					else
					{
						path.append(ficSrc);
						Graphe G(path);
						cout << "\n+++ " << PROUGE << "Graphe genere a partir de \"" 
							 << ficSrc  << "\" " << PNOIR << "+++" << endl; 
						Timer T;
						T.start();
						FordBellman(G,1);
						T.stop();
						cout << "+++ " << PROUGE << "temps d'execution de l'algo : "
							 << T.getTime() << " ms " << PNOIR << " +++\n" << endl;
						subMenu(G,path);
					}//else (fichier existant)
			}//if (choixF == 1)
			else if (choixF == 2)
			{
					int nbSu=0, nbAr=0;
					cout << "Entrer le nombre de sommets : ";
					cin >> nbSu;
					cout << "Entrer le nombre d'arcs     : ";
					cin >> nbAr;
					GrapheAlea(nbSu,nbAr);
					Graphe G("./graph/GrapheAlea.txt");
					cout <<"\n\n+++ " << PROUGE 
						 << "graphe genere dans \"./graph/GrapheAlea.txt\" +++" << PNOIR << endl;
					Timer T;
					T.start();
					FordBellman(G,(int)1);
					T.stop();
					cout << "+++ " << PROUGE << "temps d'execution de l'algo : "
						 << T.getTime() << " ms " << PNOIR << " +++\n" << endl;
					subMenu(G,"./graph/GrapheAlea.txt");
			}
			else if (choixF == 3)
			{
					int nbSu=0, nbAr=0;
					cout << "Entrer le nombre de sommets : ";
					cin >> nbSu;
					GrapheCompletAlea(nbSu);
					Graphe G("./graph/GrapheCompletAlea.txt");
					cout <<"\n\n+++ " << PROUGE 
						 << "graphe genere dans \"./graph/GrapheCompletAlea.txt\" +++" << PNOIR << endl;
					Timer T;
					T.start();
					FordBellman(G,(int)1);
					T.stop();
					cout << "+++ " << PROUGE << "temps d'execution de l'algo : "
						 << T.getTime() << " ms " << PNOIR << " +++\n" << endl;
					subMenu(G,"./graph/GrapheCompletAlea.txt");
			}
			else if (choixF == 4) break;
			break;
		case 2 : 	
			cout << CLEAR << PBLEU << endl;
			cout << "\t********************     DIJKSTRA    *******************\n"
				 << "\t********************************************************\n\n"<<PNOIR
				 << "\t\t==> "<< PBLEU << "1" << PNOIR << " - Appliquer l'algo sur des graphes de test\n"
				 << "\t\t==> "<< PBLEU << "2" << PNOIR << " - Appliquer l'algo sur un graphe aleatoire\n"
				 << "\t\t==> "<< PBLEU << "3" << PNOIR << " - Appliquer l'algo sur un graphe complet\n"
				 << "\t\t==> "<< PBLEU << "4" << PNOIR << " - Sortir\n"<< PBLEU
				 << "\t********************************************************\n\n" 
				 << PNOIR << endl;
			int choixD;
			cout << "Entrer votre choix: ";
			cin >> choixD;
			if (choixD == 1)
			{
					char ficSrc[20];
					string path = "./graph/";
					cout << "Entrer le nom du fichier source : ";
					cin >> ficSrc;
					bool existingFic=false;
					struct dirent *entry;
					DIR *rep;
					rep = opendir(path.c_str());
					while ( (entry=readdir(rep))) 
					{
						if(!strncmp(entry->d_name,ficSrc,entry->d_reclen))
						{
							existingFic = true;	
							closedir(rep);
						}
					}
					if(!existingFic)
					{
						cout <<"\n+++ \"" << PROUGE 
							 << ficSrc << "\" non trouve " << PNOIR << "+++" << endl; 
						cout <<"le fichier doit etre dans le sous-repertoire ./graph" << endl;
					}
					else
					{
						path.append(ficSrc);
						Graphe G(path);
						cout << "\n+++ " << PROUGE << "Graphe genere a partir de \"" 
							 << ficSrc  << "\" " << PNOIR << "+++" << endl; 
						Timer T;
						T.start();
						Dijkstra(G,1);
						T.stop();
						cout << "+++ " << PROUGE << "temps d'execution de l'algo : "
							 << T.getTime() << " ms " << PNOIR << " +++\n" << endl;
						subMenu(G,path);
					}//else (fichier existant)
			}//if (choixD == 1)
			else if (choixD == 2)
			{
					int nbSu=0, nbAr=0;
					cout << "Entrer le nombre de sommets : ";
					cin >> nbSu;
					cout << "Entrer le nombre d'arcs     : ";
					cin >> nbAr;
					GrapheAlea(nbSu,nbAr);
					Graphe G("./graph/GrapheAlea.txt");
					cout <<"\n\n+++ " << PROUGE 
						 << "graphe genere dans \"./graph/GrapheAlea.txt\" +++" << PNOIR << endl;
					Timer T;
					T.start();
					Dijkstra(G,(int)1);
					T.stop();
					cout << "+++ " << PROUGE << "temps d'execution de l'algo : "
						 << T.getTime() << " ms " << PNOIR << " +++\n" << endl;
					subMenu(G,"./graph/GrapheAlea.txt");
			}
			else if (choixD == 3)
			{
					int nbSu=0, nbAr=0;
					cout << "Entrer le nombre de sommets : ";
					cin >> nbSu;
					GrapheCompletAlea(nbSu);
					Graphe G("./graph/GrapheCompletAlea.txt");
					cout <<"\n\n+++ " << PROUGE 
						 << "graphe genere dans \"./graph/GrapheCompletAlea.txt\" +++" << PNOIR << endl;
					Timer T;
					T.start();
					Dijkstra(G,(int)1);
					T.stop();
					cout << "+++ " << PROUGE << "temps d'execution de l'algo : "
						 << T.getTime() << " ms " << PNOIR << " +++\n" << endl;
					subMenu(G,"./graph/GrapheCompletAlea.txt");
			}
			else if (choixD == 4) break;
			break;
		case 3 : 	//Dijkstra + tas
			cout << CLEAR << PBLEU << endl;
			cout << "\t****************    DIJKSTRA AVEC TAS  *****************\n"
				 << "\t********************************************************\n\n"<<PNOIR
				 << "\t\t==> "<< PBLEU << "1" << PNOIR << " - Appliquer l'algo sur des graphes de test\n"
				 << "\t\t==> "<< PBLEU << "2" << PNOIR << " - Appliquer l'algo sur un graphe aleatoire\n"
				 << "\t\t==> "<< PBLEU << "3" << PNOIR << " - Appliquer l'algo sur un graphe complet\n"
				 << "\t\t==> "<< PBLEU << "4" << PNOIR << " - Sortir\n"<< PBLEU
				 << "\t********************************************************\n\n" 
				 << PNOIR << endl;
			int choixDT;
			cout << "Entrer votre choix: ";
			cin >> choixDT;
			if (choixDT == 1)
			{
					char ficSrc[20];
					string path = "./graph/";
					cout << "Entrer le nom du fichier source : ";
					cin >> ficSrc;
					bool existingFic=false;
					struct dirent *entry;
					DIR *rep;
					rep = opendir(path.c_str());
					while ( (entry=readdir(rep))) 
					{
						if(!strncmp(entry->d_name,ficSrc,entry->d_reclen))
						{
							existingFic = true;	
							closedir(rep);
						}
					}
					if(!existingFic)
					{
						cout <<"\n+++ \"" << PROUGE 
							 << ficSrc << "\" non trouve " << PNOIR << "+++" << endl; 
						cout <<"le fichier doit etre dans le sous-repertoire ./graph" << endl;
					}
					else
					{
						path.append(ficSrc);
						Graphe G(path);
						cout << "\n+++ " << PROUGE << "Graphe genere a partir de \"" 
							 << ficSrc  << "\" " << PNOIR << "+++" << endl; 
						Timer T;
						T.start();
						DijkstraTas(G,(int)1);
						T.stop();
						cout << "+++ " << PROUGE << "temps d'execution de l'algo : "
							 << T.getTime() << " ms " << PNOIR << " +++\n" << endl;
						subMenu(G,path);
					}//else (fichier existant)
			}//if (choixDT == 1)
			else if (choixDT == 2)
			{
					int nbSu=0, nbAr=0;
					cout << "Entrer le nombre de sommets : ";
					cin >> nbSu;
					cout << "Entrer le nombre d'arcs     : ";
					cin >> nbAr;
					GrapheAlea(nbSu,nbAr);
					Graphe G("./graph/GrapheAlea.txt");
					cout <<"\n\n+++ " << PROUGE 
						 << "graphe genere dans \"./graph/GrapheAlea.txt\" +++" << PNOIR << endl;
					Timer T;
					T.start();
					DijkstraTas(G,(int)1);
					T.stop();
					cout << "+++ " << PROUGE << "temps d'execution de l'algo : "
						 << T.getTime() << " ms " << PNOIR << " +++\n" << endl;
					subMenu(G,"./graph/GrapheAlea.txt");
			}
			else if (choixDT == 3)
			{
					int nbSu=0;
					cout << "Entrer le nombre de sommets : ";
					cin >> nbSu;
					GrapheCompletAlea(nbSu);
					Graphe G("./graph/GrapheCompletAlea.txt");
					cout <<"\n\n+++ " << PROUGE 
						 << "graphe genere dans \"./graph/GrapheCompletAlea.txt\" +++" << PNOIR << endl;
					Timer T;
					T.start();
					DijkstraTas(G,(int)1);
					T.stop();
					cout << "+++ " << PROUGE << "temps d'execution de l'algo : "
						 << T.getTime() << " ms " << PNOIR << " +++\n" << endl;
					subMenu(G,"./graph/GrapheCompletAlea.txt");
			}
			else if (choixDT == 4) break;
			break;
		case 4 :	
			cout << PNOIR << "\n\n" << endl;
			cout << " +++ " << PROUGE << "Vous quittez le monde des graphes" 
				 << PNOIR << " +++ " << endl;
			sleep(1);
			cout << " +++ " << PROUGE << "Au revoir ..." 
				 << PNOIR << " +++ \n" << endl;
			exit(0);
		default :
			cin >> choix;
			cout << PNOIR <<  "--- " 
				 << PROUGE << "choix non reconnu ---" << PNOIR << endl;;
			break;
	}//switch principal		 
	cout << CLEAR << PBLEU;
	cout << "\t********************************************************\n"
		 << "\t*****************   MENU PRINCIPAL  ********************\n"
		 << "\t********************************************************\n\n"<<PNOIR
		 << "\t\t==> "<< PBLEU << "1" << PNOIR << " - Appliquer l'algo de Ford-Bellman\n"
		 << "\t\t==> "<< PBLEU << "2" << PNOIR << " - Appliquer l'algo de Dijkstra\n"
		 << "\t\t==> "<< PBLEU << "3" << PNOIR << " - Appliquer Dijkstra sur les tas\n"
		 << "\t\t==> "<< PBLEU << "4" << PNOIR << " - Sortir\n" << PBLEU
		 << "\t*********************************************************\n\n";
	cout << PNOIR << "Entrer votre choix : ";
	cin >> choix;
	}
	//cout << INIT;
	return 0;
}
