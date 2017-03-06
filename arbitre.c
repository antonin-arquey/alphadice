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
		rappelSyntaxe();
		return 1;
	}
	return 0;
}

void rappelSyntaxe(){
	printf("Mauvais arguments !!!\n");
	printf("Parametre 1 : Nombre de parties souhaitees\n");
	printf("Parametre 2 : Nombre de joueurs souhaites\n");
	printf("Parametre 3 et + : Fichiers d'IA a utiliser (Optionnel)\n");
	printf("Exemple : ./AlphaDice 2 6\n");
}