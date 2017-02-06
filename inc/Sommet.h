/**
 *
 * Author : J. Michel-Villaz
 *
 * File   : Succ.h 
 *
 * Date   : 19/10/06
 *
 * par defition, on a G=(X,E) ou:
 		-G est un graphe
		-X tous les sommets de G
		-E tous les arcs de G
*/

#include<vector>
#include"Succ.h"

#ifndef __SOMMET_H__
#define __SOMMET_H__

class Sommet
{
   private :
	int num;
	int dist;
	Sommet* pred;
	std::vector<Succ> Suc;
	
   public :
	Sommet(int numSom);
	Sommet(int numSom,int d,std::vector<Succ> S);
	~Sommet(){};
	//operateurs	
	Succ& operator[](int i);
	Sommet& operator=(Sommet& S);
	//accesseurs
	int getNumSom();
	int getDist();
	void setDist(int d);
	Succ getSucc(int i);
	void setSucc(Succ& S);
	void remSucc(Succ& S);
	Sommet& getPred();
	void setPred(Sommet& Pred);
	//fonctions membres
	std::vector<Succ> getSuc();
	int size();
	void resize();
};


#endif
	

    
