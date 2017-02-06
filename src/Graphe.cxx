/**
 *
 * Author : J. Michel-Villaz
 *
 * File   : Graphe.cxx
 *
 * Date   : 05/10/06
 *
 */

#include "../inc/Graphe.h"
#include "../inc/Sommet.h"
#include <iostream>
#include <iomanip> //rand
#include <fstream>
#include <sstream> //ostringstream()
#include <vector>

#ifndef __GRAPHE_CXX__
#define __GRAPHE_CXX__

//#define GRAPHE Graphe<S>

Graphe::Graphe(const int nbS, const int nbA)
	:nbSom(nbS),nbArc(0)
{
	int minEdge = nbS-1;
	int maxEdge = nbS*(nbS-1)/2;
	srand((int)time(NULL));

	if(nbA>maxEdge || nbA<minEdge)
	{
		std::cerr << "\t--- arc number entered must be between " 
		     << minEdge << " and " << maxEdge << " ---" << std::endl;
		exit(0);
	}

	for (int i=0;i<nbSom;++i)
		X.push_back(Sommet(i+1));
	
	// generation du graphe complet
	for(int i=1;i<(nbSom+1);++i)
		for(int j=1,k=0;k<nbSom;++j,++k)
			if (i!=j) 
			{
				Succ S(j,(rand()%11)+1);
				X[i-1].setSucc(S);
				++nbArc;
			}
	// elimination des arcs doubles aleatoirement
	for(int i=0; i<getNbSom(); ++i)
		for(int j=0;j<X[i].size();++j)
			//pour chaque successeur de i, je regarde si dans ses successeurs il y a le sommet i
			//alors je supprime aléatoirement 1 des 2 arcs doubles
			for(int	k=0;k<getNbSom();++k)
				if(X[i][j].getNumSom()==X[k].getNumSom())
					for(int l=0;l<X[k].size();++l)
						if(X[k][l].getNumSom()==X[i].getNumSom())
							if(rand()%2)
							{
								X[i].remSucc(X[i][j]);
								--nbArc;
							}
							else
							{
								X[k].remSucc(X[k][l]);
								--nbArc;
							}
	// suppression des arcs pour obtenir le nombre voulu nbA
	while(nbArc >= nbA)
	{		
		int som = rand()%nbSom;
		int suc = rand()%(X[som].size());
		std::cout << som << ' ' << suc;
		X[som].remSucc(X[som][suc]);
		--nbArc;
		Graphe Complet(*this);
		if(!Complet.isConnexe())
		{
			std::cout << " isthme" << std::endl;
			X[som].setSucc(X[som][suc]);
			++nbArc;
		}
		else std::cout << std::endl;
	}
	std::cout << "nb som : "<< nbSom << std::endl;
	std::cout << "nb arc : "<< nbArc << std::endl;
}
Graphe::Graphe(std::string ficSrc)
{
	std::ifstream fic;
	fic.open(ficSrc.c_str());

	typedef std::vector<int> CVSom_t;//contient tous les sommets 1x
	CVSom_t VSom;

	// comptage des sommets du graphe
	for(int som=0, k=1; fic >> som; ++k)
	{
		if (fic.eof()) break;
		if (k%3) //un sommet
		{
			bool isSom = false;//verifie si le sommet esti connu
			for (int i=0;i<VSom.size();	++i)
			if	(som==VSom[i])
			{
				isSom=true;
				break;
			}
			if(!isSom) VSom.push_back(som);
		}
	}
	fic.close();
	this->nbSom	=VSom.size();

	// construction d'un graphe a partir d'un fichier
	char c;
	int nbArcs=0;
	int som1=0,som2=0,pond=0;

	//construction de la liste d'adjacence
	for (int i=0; i<nbSom; ++i)
			X.push_back(Sommet(VSom[i]));
			
	// comptage des sommets du graphe
	fic.open(ficSrc.c_str());
	
	for(;;)
	{
		fic >> som1 >> som2 >> pond;
		Succ S(som2,pond);
		if (fic.eof()) break;
		for (int i=0;i<nbSom;++i)
			if (X[i].getNumSom()==som1) X[i].setSucc(S);
		++nbArcs; 	//comptage des arcs
	}
	this->nbArc = nbArcs;
	fic.close();
}
int Graphe::getNbSom()
{
	return this->nbSom;
}
int Graphe::getNbArc()
{
	return this->nbArc;
}
void Graphe::affiche()
{
	for(int i=0; i<nbSom;++i)
	{
		std::cout << '\t' << std::setw(3) << X[i].getNumSom();
		for(int j=0; j<X[i].size();++j)
			std::cout << std::setw(3) << X[i][j].getNumSom();
		std::cout << std::endl;
	}		
	std::cout << std::endl;
}
bool Graphe::isConnexe()
{
	std::vector<int> VSom;
	std::vector<int> VSomParcouru;

	VSom.push_back(X[0].getNumSom());
	VSomParcouru.push_back(X[0].getNumSom());

	while(VSom.size()>0)
	{	
		std::vector<int>::iterator iter=VSom.begin();
	    for(int i=0; i<nbSom;++i)	
			if (X[i].getNumSom() == *iter)
			{
				for(int j=0;j<X[i].size();++j)
				{
					bool isSeen=false;
					for(int k=0;k<VSomParcouru.size();++k)
						if (X[i][j].getNumSom()==VSomParcouru[k]) 
						{
							isSeen=true;
							break;
						}
					if(!isSeen)
					{
						VSomParcouru.push_back(X[i][j].getNumSom());
						VSom.push_back(X[i][j].getNumSom());
					}
				}
			}
		VSom.erase(VSom.begin());
	}//while
	if(VSomParcouru.size()==nbSom) return true;
	else return false;
}
std::string Graphe::getShorterPath(int Som)
{
	std::ostringstream os;
	std::vector<int> VSom;
	for(int i=0;i<getNbSom();++i)
		if(X[i].getNumSom()==Som)
		{
			Sommet SomCur(0);
			SomCur = X[i];
			VSom.push_back(SomCur.getNumSom());
			for(;;)
			{
				if(&(SomCur.getPred())==NULL) break;
				SomCur = SomCur.getPred();
				VSom.push_back(SomCur.getNumSom());
			}
		}	
	for(int i=VSom.size(); i>0; --i)
		os << " " << VSom[i-1];
	return os.str();
}
Sommet& Graphe::operator[](int i)
{ return X[i];}

Sommet Graphe::getSom(int i)
{ return X[i];}
#endif


