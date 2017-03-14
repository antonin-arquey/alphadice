#include "map.h"
#include "arbitre.h"
#include <stdlib.h>
#include <stdio.h>

// Fonction modifiant le propriétaire d'un territoire (cell)
void chgOwnerCell(SCell* cell, int idNewOwner)
{
	cell->owner = idNewOwner;
}

/*
Fonction vérifiant un tour rendu
Renvoie 1 si le tour est bon, -1 si il est pas valide
*/
int verifyTurn(unsigned int idPlayer, STurn *turn, SMap *map)
{
	//Verifiez que la cellule de départ est bien au joueur
	if(map->cells[turn->cellFrom].owner != idPlayer)
	{
		return -1;
	}

	//Verifier que la cellule de départ et d'arrivée sont adjacentes
	int voisine = 0;

	for(int i = 0; i < map->cells[turn->cellFrom].nbNeighbors; i++)
	{
		if(map->cells[turn->cellFrom].neighbors[i]->id == turn->cellTo)
		{
			voisine = 1;
			break;
		}
	}

	if(!voisine)
	{
		return -1;
	}
}

/*
Simule le nombre de lancers de dé passé en paramètres et renvoie la somme des lancers
*/
int lancerDe(int nbDe){
	int s = 0;
	for(int i=0 ; i < nbDe ; i++)
	{
		s += aleatoire(1, 6);
	}
	return s;
}

/* Fonction qui jour le tour et modifie la map en conséquent */

int endTurn(STurn *turn, SMap *map)
{
	SCell *cellAttacker = &map->cells[turn->cellFrom];
	SCell *cellDefender = &map->cells[turn->cellTo];
	int sommeAttacker = lancerDe(cellAttacker->nbDices);
	int sommeDefender = lancerDe(cellDefender->nbDices);

	if(sommeAttacker > sommeDefender){
		cellDefender->owner = cellAttacker->owner;
		cellDefender->nbDices = cellAttacker->nbDices - 1;
	}

	cellAttacker->nbDices = 1;
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
