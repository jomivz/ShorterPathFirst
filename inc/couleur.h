#ifndef COULEURS
#define COULEURS
#include <stdio.h>

// affection d'une couleur dans le flux
/*   param devant êe un const char *, vide (identique à0") ou formé    d'une
*   oùsieurs valeurs séré par des ; parmi
	0  reinitialisation 		1  haute intensite des  caracteres
	5  clignotement			7  video inversee       30, 31,
	32, 33, 34, 35, 36, 37 couleur des caractès
	40, 41, 42, 43, 44, 45, 46, 47 couleur du fond
	les couleurs, suivant la logique RGB sont respectivement
	noir, rouge, vert, jaune,bleu, magenta, cyan et	blanc */

#define PVERT 	"\033[32m"
#define PJAUNE 	"\033[33m"
#define PBLEU 	"\033[34m"
#define PMAGEN 	"\033[35m"
#define PCYAN 	"\033[36m"
#define PBLANC 	"\033[37m"
#define PROUGE 	"\033[38m"
#define PNOIR 	"\033[39m"

#define BNOIR 	"\033[40m"
#define BROUGE 	"\033[41m"
#define BVERT 	"\033[42m"
#define BJAUNE 	"\033[43m"
#define BBLEU 	"\033[44m"
#define BMAGEN 	"\033[45m"
#define BCYAN 	"\033[46m"
#define BBLANC 	"\033[47m"

// Efface l'ecran et place le curseur en haut a gauche
#define CLEAR "\033[H\033[2J"
// Pour reinitialiser le flux
#define INIT  "\033[0m"
#endif 
