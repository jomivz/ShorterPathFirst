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

#include "../inc/Sommet.h"
#include <iostream>

#ifndef __SOMMET_CXX__
#define __SOMMET_CXX__

Sommet::Sommet(int numSom)
	:num(numSom),dist(0),pred(NULL){}
	
Sommet::Sommet(int numSom,int d,std::vector<Succ> S)
	:num(numSom),dist(d),pred(NULL)
{for (int i=0;i<S.size();++i) Suc.push_back(S[i]);}

int Sommet::getNumSom()
{ return num;}

int Sommet::getDist()
{ return dist;}

Succ Sommet::getSucc(int i)
{ return Suc[i];}

std::vector<Succ> Sommet::getSuc()
{ return Suc;}

int Sommet::size()
{ return Suc.size();}

void Sommet::setSucc(Succ& S)
{ Suc.push_back(S);}

void Sommet::remSucc(Succ& S)
{
	for(int i=0; i<size();++i)
		if( Suc[i].getNumSom() == S.getNumSom())
		{
			Suc[i] = Suc[size()-1];
			Suc.pop_back();
		}
}

void Sommet::setDist(int d)
{ dist=d;}
Sommet& Sommet::getPred()
{ return *pred;}
void Sommet::setPred(Sommet& S)
{ pred = &S;}

Succ& Sommet::operator[](int i)
{ return Suc[i];}

Sommet& Sommet::operator=(Sommet& S)
{ 
	num  = S.getNumSom();
	pred = S.pred;
	for(int i=Suc.size(); i>0 ; --i)
		Suc.pop_back();
	for(int pos=0;pos<S.size();++pos)
		Suc.push_back(S[pos]);
	return *this;
}
#endif
