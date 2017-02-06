/**
 *
 * Author : J. Michel-Villaz
 *
 * File   : Succ.cxx
 *
 * Date   : 19/10/06
 *
 * par defition, on a G=(X,E) ou:
 		-G est un graphe
		-X tous les sommets de G
		-E tous les arcs de G
 */

#include "../inc/Succ.h"

#ifndef __SUCC_CXX__
#define __SUCC_CXX__

Succ::Succ(int numSom,int ponde)
	:num(numSom),pond(ponde){}
	
int Succ::getNumSom()
{ return num;}

int Succ::getPond()
{ return pond;}

#endif
