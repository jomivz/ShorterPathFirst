/**
 *
 * Author : J. Michel-Villaz
 *
 * File   : Succ.h 
 *
 * Date   : 19/11/06
 *
*/

#include<vector>
#include "Sommet.h"

#ifndef __TAS_H__
#define __TAS_H__

class Tas 
{
	private :
		int tailleMax;
		int taille;
		int* tasDist;
		int* tasSom;
	public :
	//constructeurs
		Tas(int tailleTas);
		~Tas();
	//fonctions membres
	void remonte(int i);
	void descendre(int i);
	//fonction pour dijkstra
	int getPrem();
	void ajouter(Sommet S);
	void monter (Sommet S);
	void affiche();
};
#endif
	

    
