#include "arbitre.h"

void chgOwnerCell(Cell* cell, int idNewOwner){
	//cell->owner = idNewOwner; //Ne fonctionne pas donc en commentaire pour pas avoir d'erreur
}

Cell* declareAttack(Cell* attackingCell, Cell* defendingCell){
	Cell* winningCell = attackingCell; //Temporaire pour pas avoir d'erreur
	return winningCell;
}

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
			rappelSyntaxe("Trop de paramètre par rapport au nombre de joueurs\n");
		}
	}
	return 0;
}

void rappelSyntaxe(char* affichage){
	printf("%s",affichage);
	printf("Parametre 1 : Nombre de parties souhaitees (max 9)\n");
	printf("Parametre 2 : Nombre de joueurs souhaites (max 8)\n");
	printf("Parametre 3 et + : Fichiers d'IA a utiliser (Optionnel)\n");
	printf("Exemple : ./AlphaDice 2 6\n");
}