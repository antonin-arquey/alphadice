#include "arbitre.h"
#include <stdlib.h>
#include <stdio.h>

// Fonction modifiant le propriétaire d'un territoire (cell)
void chgOwnerCell(SCell* cell, int idNewOwner){
	cell->owner = idNewOwner;
}

// Verifie les paramètres mis par l'utilisateur au lancement du
// programme.
int verifArguments(int argc, char* argv[]){
	if(argc<3){
		rappelSyntaxe("Mauvais nombre d'arguments\n");
		return 1;
	}
	if(((*argv[1]<48)||(*argv[1]>57))||((*argv[2]<48)||(*argv[2]>57))){
		rappelSyntaxe("Mauvais paramètres\n");
		return 1;
	}
	if(argc>3){
		if(argc-3>atoi(argv[2])){
			rappelSyntaxe("Trop de paramètres par rapport au nombre de joueurs\n");
		}
	}
	return 0;
}

// Affichage des régles en cas de problème de paramètre au lancement
void rappelSyntaxe(char* affichage){
	printf("%s",affichage);
	printf("Parametre 1 : Nombre de parties souhaitees (max 9)\n");
	printf("Parametre 2 : Nombre de joueurs souhaites (max 8)\n");
	printf("Parametre 3 et + : Fichiers d'IA a utiliser (Optionnel)\n");
	printf("Exemple : ./AlphaDice 2 6\n");
}
