/**
 *
 * Author : J. Michel-Villaz
 *
 * File   : Tas.cxx 
 *
 * Date   : 19/11/06
 *
*/

#include<vector>
#include<iostream>
#include "../inc/Tas.h"

#ifndef __TAS_CXX__
#define __TAS_CXX__

Tas::Tas(int size)
{
	tailleMax = size+2;
	taille = 1;
	tasDist = new int[tailleMax];
	tasSom  = new int[tailleMax];
	for(int i=0;i<tailleMax;++i)
	{
		tasDist[i] = -1;
		tasSom [i] = -1;
	}
}

Tas::~Tas()
{
	delete tasDist;
	delete tasSom;
}

void Tas::ajouter(Sommet S)
{
	tasDist[taille] = S.getDist();
	tasSom [taille] = S.getNumSom();
	remonte(taille);
	if (taille >= tailleMax)
	std::cout << "error taille" << std::endl;
	++taille;
}

void Tas::monter(Sommet S)
{
	int pos=1;
	for( ; pos<taille; ++pos)
		if (tasSom[pos] == S.getNumSom()) 
		{
			remonte(pos);
			return;
		}
}
void Tas::remonte(int i)
{	
	if (i>1)
	{
		if (i%2==1)
		{
			if(tasDist[i]<tasDist[(i-1)/2])
			{
				//swap la distance
				int buf = tasDist[i];
				tasDist[i] = tasDist[(i-1)/2];
				tasDist[(i-1)/2] = buf;
				//swap le sommet
				buf = tasSom[i];
				tasSom[i] = tasSom[(i-1)/2];
				tasSom[(i-1)/2] = buf;
				//recursivite
				i=(i-1)/2;
				remonte(i);
			}
		}
		else if (tasDist[i]<tasDist[i/2])
		{
			//swap la distance
			int buf = tasDist[i];
			tasDist[i] = tasDist[i/2];
			tasDist[i/2] = buf;
			//swap le sommet
			buf = tasSom[i];
			tasSom[i] = tasSom[i/2];
			tasSom[i/2] = buf;
			//recursivite
			i=i/2;
			remonte(i);
		}
	}
}

void Tas::descendre(int i)
{	
	if (i<taille-1)
	{
			if((tasDist[2*i+1]!=-1)&&(tasDist[i]>tasDist[2*i+1]))
			{
				//swap la distance
				int buf = tasDist[i];
				tasDist[i] = tasDist[2*i+1];
				tasDist[2*i+1] = buf;
				//swap le sommet
				buf = tasSom[i];
				tasSom[i] = tasSom[2*i+1];
				tasSom[2*i+1] = buf;
				//recursivite
				i=2*i+1;
				descendre(i);
			}
			else if((tasDist[2*i]!=-1)&&(tasDist[i]>tasDist[2*i]))
			{
				//swap la distance
				int buf = tasDist[i];
				tasDist[i] = tasDist[2*i];
				tasDist[2*i] = buf;
				//swap le sommet
				buf = tasSom[i];
				tasSom[i] = tasSom[2*i];
				tasSom[2*i] = buf;
				//recursivite
				i=2*i;
				descendre(i);
			}
	}
}
int Tas::getPrem()
{ 
	int res = tasSom[1];
	tasSom [1] = tasSom [taille-1];
	tasDist[1] = tasDist[taille-1];
	tasSom [taille-1] = -1;
	tasDist[taille-1] = -1;
	--taille;
	descendre(1);
	return res;
}
void Tas::affiche()
{
	std::cout << std::endl;
	std::cout << "tas trie: ";
	for(int i=1; i<taille; ++i)
		std::cout << tasDist[i] << ' ';
	std::cout << std::endl;
	
	std::cout << "sommets tries : ";
	for(int i=1; i<taille; ++i)
		std::cout << tasSom[i] << ' ';
	std::cout << std::endl;
	std::cout << std::endl;
}
#endif
