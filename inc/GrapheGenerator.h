#include <stdlib.h>
#include <set>
#include <map>
#include <fstream>
#include <iostream>

#ifndef __GRAPHEGENERATOR_H__
#define __GRAPHEGENERATOR_H__

using namespace std;

// AVEC CYCLES DE TAILLE 2 !!



// arguments pu programme : 'genrateurGraph nbSommet nbArc ponderationMin ponderationMax nomFichierSortie'

// graphe generer : graphe oriente avec une seule composante connexe (mais pas fortement connexe) et sans cycles de taille 2

// methode : on genere le graphe oriente complet de nbSommet sommets.
// puis on essaye de retire une arete (= 2 arcs), et on verifie que le nouveau graphe ne possede
// qu'une seule composante connexe (= le graphe non oriente correspondant est connexe). Si il ne l'est plus
// on remet l'arete enlevee (= les arcs enleves) et on essaye avec une autre arete (2 autres arcs)

// on commance par creer un graphe oriente ne possedent qu'une seule composante fortement connexe et
// dont chaque arc possede son arc retour, puis, pour chaque arc, soit on suprime cet arc, soit son
// arc retour. et enfin on place une ponderation sur les arcs

// retourne un nombre au aleatoire entre 0 et max non compris
int nbAleatoire(int max){
	return int( (rand()/double(RAND_MAX-1)) * (max) ); // jamais egal a max
}

int numSom(set<int> liste, int num){
	if(num < 0){
		cout << "BUG BUG BUG 2" << endl;
		exit(0);
	}
	
	set<int>::iterator it = liste.begin();
	
	for(int i = 1; i < num; i++){
		it++;
		if(it == liste.end())
			cout << "BUG BUG BUG" << endl;
	}
	
	return *it;
}

// stoque dans numDep et NumFin le numeros des sommets de l'arc numArc
int numerosArc(map<int,set<int> > &graphe, int numArc, int &numDep, int &numFin){
	int curs = 0;
	for(int i = 0; i < graphe.size(); i++){
		curs += graphe[i].size();
		if(curs > numArc){
			// on a trouver le sommet de depart de l'arc
			numDep = i;
			numFin = numSom(graphe[i], numArc - (curs - graphe[i].size()) );
			return 0;
		}
	}
	cout << "BUG BUG BUG 3 " << numArc << endl;
	return 1;
}

// parcours le graphe a partir du sommet num 
void parcourir(map<int, set<int> > &graphe, set<int> &somAtteints, int num){
	
	// si le sommet a deja ete traite
	if(somAtteints.find(num) != somAtteints.end())
		return;
	
	// insert le sommet traite dans la liste des sommets atteints
	somAtteints.insert(num);
	
	for(set<int>::iterator it = graphe[num].begin(); it != graphe[num].end(); it++)
		parcourir(graphe, somAtteints, *it);
}





void GrapheCompletAlea(int nbSom){
	
	// initialise le generateur de nombre aleatoire
	srand((int)time(NULL));
	
	int pondMin = 1;
	int pondMax = 50;
	
	ofstream of("./graph/GrapheCompletAlea.txt");
	
	for(int i = 0; i < nbSom; i++){
		for(int j = 0; j < i; j++)
			of << i << " " << j << " " << pondMin +
			nbAleatoire(pondMax-pondMin+1) << endl;
		for(int j = i+1; j < nbSom; j++)
			of << i << " " << j << " " << pondMin +
			nbAleatoire(pondMax-pondMin+1) << endl;
	}
}






void  GrapheAlea(int nbSom, int nbArcVoulus){
	
	// initialise le generateur de nombre aleatoire
	srand((int)time(NULL));
	
	int pondMin = 1;
	int pondMax = 50;
	string nomFichSortie = "./graph/GrapheAlea.txt";
	
	if(nbArcVoulus < nbSom - 1)
		cout << "Trop peu d'arc demandes" << endl;
	if(nbArcVoulus > (nbSom*(nbSom-1)/2))
		cout << "Trop d'arc demandes" << endl;
	
	int nbArcATestees;
	
	int nbEssais = 0;
	
	
	// map : int = numero du sommet, le set contient les sommets voisins de ce dernier
	map<int, set<int> > graphe;
	
	do {
		graphe.clear();
	// creation du graphe complet de nbSom sommets
	for(int i = 0; i < nbSom; i++){
		for(int j = 0; j < i; j++)
			graphe[i].insert(j);
		for(int j = i+1; j < nbSom; j++)
			graphe[i].insert(j);
	}
	
	// nombre d'arc dans le graphe courant
	int nbArc = nbSom * (nbSom-1);
	
	map<int, set<int> > arcATestees = graphe;
	nbArcATestees = nbArc;
	

	
	// Tant que le nombre d'arc du graphe est super au nombre voulue
	// ou que le nombre d'arc que l'on peut essaye de retirer est positif
	while(nbArc > nbArcVoulus && nbArcATestees > 0){
		// sommets atteints, utile pour le parcours de test de connexitee, le graph a une seule composante
		// connexe si tout les sommets sont dans somAtteints
		set<int> somAtteints;
		// numero de l'arc enleve
		int numArc;
		// numero du sommet de sommet de depart de l'arc enleve
		int numDep;
		// numero du sommet de sommet de fin de l'arc enleve
		int numFin;
	
		numArc = nbAleatoire(nbArcATestees);
		//cout << "num = " << numArc << ", nbArcATestees = " << nbArcATestees << endl;
		numerosArc(graphe, numArc, numDep, numFin);
		
		// retire l'arc numDep-numFin
		graphe[numDep].erase(numFin);
		graphe[numFin].erase(numDep);
		
		// retire l'arc numDep-numFin
		arcATestees[numDep].erase(numFin);
		arcATestees[numFin].erase(numDep);
		nbArcATestees -= 2;
		
		
		parcourir(graphe, somAtteints, 0);
		
		if(somAtteints.size() == nbSom){
			// on a atteints tous les sommets, le graphe possede une seule composante fortement connexe
			nbArc -= 2;
		// arc pouvant etre retire
			arcATestees = graphe;
			nbArcATestees = nbArc;

		} else {
			// le graphe n'est plus connexe, on remet les arc enleves
			graphe[numDep].insert(numFin);
			graphe[numFin].insert(numDep);
		}
	}

	nbEssais++;
	}
	while((nbArcATestees == 0) && (nbEssais < 10));
	
	if(nbArcATestees == 0)
		cout << "Plus d'arc supprimable !" << endl;
	
	ofstream of(nomFichSortie.c_str());
	
	for(int i = 0; i < nbSom; i++){
		for(set<int>::iterator it = graphe[i].begin(); it != graphe[i].end(); it++){
			of << i << " " << *it << " " << pondMin + nbAleatoire(pondMax-pondMin+1);
			of << endl;
		}
	}
}

#endif
