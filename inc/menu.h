#include "Graphe.h"
#include "couleur.h"

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<ctime>

using namespace std;

void subMenu(Graphe &G,string ficSrc)
{
	int choix4=0;
	for( ; ; )
	{
		cout << PBLEU;
		cout << "\t*************** GRAPHE " << ficSrc << "       ***************\n"
			 <<"\t********************************************************\n\n" << PNOIR
			 << "\t\t==> "<< PBLEU << "1" << PNOIR << " - Afficher le graphe\n"
			 << "\t\t==> "<< PBLEU << "2" << PNOIR << " - Trouver un plus court chemin\n"
			 << "\t\t==> "<< PBLEU << "3" << PNOIR << " - Stocker un plus court chemin\n"
			 << "\t\t==> "<< PBLEU << "4" << PNOIR << " - Sortir\n"<< PBLEU
			 << "\t********************************************************\n\n"
			 << PNOIR << endl;
		cout << "Entrer votre choix : ";
		cin >> choix4;
		if (choix4 == 1)
		{
			cout << CLEAR;
			cout << "\n+++ " << PROUGE << "Affichage du graphe "
				<< PNOIR << " +++\n" << endl;
			G.affiche();
		}
		else if (choix4 == 2) 
		{
			int targetSom=0;
			cout << "Entrer le sommet a atteindre : ";
			cin >> targetSom;
			cout << CLEAR;
			cout << "\n+++ " << PROUGE << "Affichage du PPC de "  
				 <<  targetSom << PNOIR << " +++\n\n\t\t";
			cout << G.getShorterPath(targetSom) << endl;
		}
		else if (choix4 == 3) 
		{
			int targetSom=0;
			cout << "Entrer le sommet a atteindre : ";
			cin >> targetSom;
			cout << CLEAR;
			//stockage dans le fichier "pcc.txt"
			istringstream is (G.getShorterPath(targetSom).c_str());
			ofstream pcc ("pcc.txt");
			char buf;
			for ( ; !is.eof(); is>>buf )
				pcc << buf << ' ';
			pcc.close();
			cout << "\n+++ " << PROUGE << "Le PPC de "  
				<<  targetSom  << " est stocke dans \"pcc.txt\""
				<< PNOIR << " +++\n\n\t\t";
		}
		else if (choix4 == 4) break;
	}
}
