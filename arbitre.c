#include "map.h"
#include "arbitre.h"
#include <stdlib.h>
#include <stdio.h>

/*
Fonction vérifiant un tour rendu
Renvoie 1 si le tour est bon, -1 si il est pas valide
*/
int verifyTurn(unsigned int idPlayer, SMap *map, STurn *turn)
{
	//Verifiez que la cellule de départ est bien au joueur
	if(map->cells[turn->cellFrom].owner != idPlayer)
	{
		return -1;
	}

	//Verifier que la cellule de départ et d'arrivée sont adjacentes
	for(int i = 0; i < map->cells[turn->cellFrom].nbNeighbors; i++){
		if(map->cells[turn->cellFrom].neighbors[i]->id == turn->cellTo){
			return 1;
		}
	}
	return -1;
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

void moveTurn(SMap *map, STurn *turn)
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

/*
Trouve le plus grand nombre de territoire connexe appartenant au joueur passé en paramètre
*/
int getDiceToDistribute(int idPlayer, SMap *map){
	/*colorier x avec i
	pour tout sommet y successeur de x
	  si y n'est pas colorié faire CC_sommet(G,y,i)*/

	int nbDices = 0;
	for(int i = 0; i < map->nbCells; i++){
		if(map->cells[i].owner == idPlayer){
			nbDices += 1;
		}
	}
	return nbDices;
}

/*
Fonction qui répartit les dés a la fin d'un tour d'un joueur
*/
void endTurn(int idPlayer, SMap *map)
{
	int playerCell[60];
	int nbPlayerCell = 0;

	//On génére un tableau contenant les position des cellules dans map->cells
	for(int i = 0 ; i < map->nbCells ; i++){
		if(map->cells[i].owner == idPlayer){
			playerCell[nbPlayerCell] = i;
			nbPlayerCell++;
		}
	}

	int nbDiceDistributed = getDiceToDistribute(idPlayer, map);
	int rand;

	//On prend un sommet aléatoire qu'il possède et on ajoute un dé
	for(int i = 1 ; i <= nbDiceDistributed ; i++){
		rand = aleatoire(0, nbPlayerCell-1);
		if(map->cells[i].nbDices < 8){
			map->cells[i].nbDices++;
		}
	}
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
