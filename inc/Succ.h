
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

#ifndef __SUCC_H__
#define __SUCC_H__

class Succ {
   private :
	int num;
	int pond;	
   public :
	Succ(int numSom,int pond);
	~Succ(){};
	
	//accesseurs
	int getNumSom();
	int getPond();
};
#endif
	

    
