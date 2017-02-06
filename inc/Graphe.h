/**
 *
 * Author : J. Michel-Villaz
 *
 * File   : Graphe.h 
 *
 * Date   : 05/10/06
 *
 * par defition, on a G=(X,E) ou:
 		-G est un graphe
		-X tous les sommets de G
		-E tous les arcs de G
 */
#include<vector>
#include<string>
#include"Sommet.h"

#ifndef __GRAPHE_H__
#define __GRAPHE_H__


class Graphe{
   private :
	int nbSom;
	int nbArc;

	std::vector<Sommet> X;
	
   public :
   //constructeurs
	Graphe(std::string path);
	Graphe(const int nbS, const int nbA);
	~Graphe(){};
	//operateurs
	Sommet& operator[](int i);
	//accesseurs
	int  getNbSom();
	Sommet getSom(int i);
	int  getNbArc();
	//fonctions membres
	bool isConnexe();
	void affiche();
	std::string getShorterPath(int Som);
};
#endif
	

    
