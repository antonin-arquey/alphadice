#include "gameIA.h"
#include "arbre.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>


/*tableau des probabilités resultantes après un match de dés */
						/*1v1,		1v2,	  1v3, ...
						  2v1, ...
						  ...
						  																		8v8		*/
double tabProba[9][9] = {{0,				0,				0,				0,				0,				0,				0,				0				},
												 {0.416652, 0.092621, 0.011578, 0.000773, 0.000021, 0, 		  	0, 				0				},
												 {0.837916, 0.443657, 0.151995, 0.035888, 0.006106, 0.000768, 0.000071, 0.000005},
												 {0.973014, 0.778527, 0.453603, 0.191730, 0.060704, 0.014884, 0.002892, 0.000453},
												 {0.997304, 0.939230, 0.742871, 0.459467, 0.220467, 0.083447, 0.025436, 0.006385},
												 {0.999849, 0.987950, 0.909316, 0.718028, 0.463621, 0.242442, 0.103601, 0.036745},
												 {0.999996, 0.998215, 0.975288, 0.883991, 0.699587, 0.466700, 0.260018, 0.121535},
												 {1,				0.999801, 0.994674, 0.961525, 0.862370, 0.685111, 0.469154, 0.274377},
												 {1,				0.999984, 0.999072, 0.989525, 0.947766, 0.843873, 0.673508, 0.471108}};

int turnIA(int idPlayer, const SMap *map, STurn *turn){
	int compteur = -1;
	SArbre *arbre = malloc(sizeof(SArbre));
	arbre->head = malloc(sizeof(Noeud));
	arbre->head->map = deepCopy(map);
	SMap *mapCopy;
	ChanceNode nodes[100];

	for(int i = 0; i< map->nbCells; i++){
		if(map->cells[i].owner == idPlayer && map->cells[i].nbDices > 1){
			for(int j = 0; j < map->cells[i].nbNeighbors; j++){
				if(map->cells[i].neighbors[j]->owner != idPlayer){
					compteur += 1;

					nodes[compteur].turn = malloc(sizeof(STurn));//peut etre modifier et plus utiliser les STurn
					nodes[compteur].turn->cellFrom = map->cells[i].id;
					nodes[compteur].turn->cellTo = map->cells[i].neighbors[j]->id;
					nodes[compteur].probaDroite = tabProba[map->cells[i].nbDices][map->cells[i].neighbors[j]->nbDices];

					nodes[compteur].filsDroit = malloc(sizeof(Noeud));
					nodes[compteur].filsGauche = malloc(sizeof(Noeud));
					mapCopy = deepCopy(map);
					moveTurnWin(mapCopy,nodes[compteur].turn);
					nodes[compteur].filsDroit->map = mapCopy;
					mapCopy = deepCopy(map);
					moveTurnFail(deepCopy(map),nodes[compteur].turn);
					nodes[compteur].filsGauche->map = mapCopy;
				}
			}
		}
	}
	printf("valeur compteur : %d\n", compteur);
	if(compteur > -1){
		ChanceNode filsNodes[compteur]; //pas sur que tout soit pris
		arbre->head->fils = filsNodes;
		for(int x = 0; x <= compteur; x++){//a cause du <=
			arbre->head->fils[x] = nodes[x];
		}
		arbre->head->nbFils = compteur;
	}
	return 0;
}

/*
int bestMove(int idPlayer, SArbre *arbre, STurn *turn){
	int bouge = 0;
	double valHead = mapEvaluation(idPlayer, arbre->head->map);
	double valMax = valHead;
	double val;
	for(int i = 0; i < arbre->head->nbFils; i++){
		val = arbre->head->fils[i].proba * mapEvaluation(idPlayer, arbre->head->fils[i].map) + arbre->head->fils[i+1].proba * mapEvaluation(idPlayer, arbre->head->fils[i+1].map);
		if (val > valMax){
			valMax = val;
			turn = arbre->head->fils[i].turn;
			bouge = 1;
		}
	}
	return bouge;
}

int mapEvaluation(int idPlayer, SMap *map){
	int alpha = 1; int beta = 1;
	int value = alpha * getAmountOfDices(idPlayer, map) + beta * getDicesToDistribute(idPlayer, map);

	return value;
}

int getAmountOfDices(int idPlayer, SMap *map){
	int nbDices = 0;
	for(int i = 0; i < map->nbCells; i++){
		if(map->cells[i].owner == idPlayer){
			nbDices += map->cells[i].nbDices;
		}
	}
	return nbDices;
}

int getDicesToDistribute(int idPlayer, SMap *map){
	int nbDices = 0;
	for(int i = 0; i < map->nbCells; i++){
		if(map->cells[i].owner == idPlayer){
			nbDices += 1;
		}
	}
	return nbDices;
}
*/
void moveTurnFail(SMap *map, STurn *turn){
	map->cells[turn->cellFrom].nbDices = 1;
}

void moveTurnWin(SMap *map, STurn *turn){
	SCell *cellAttacker = &map->cells[turn->cellFrom];
	SCell *cellDefender = &map->cells[turn->cellTo];
	cellDefender->owner = cellAttacker->owner;
	cellDefender->nbDices = cellAttacker->nbDices - 1;
	cellAttacker->nbDices = 1;
}

SMap* deepCopy(const SMap *map){
	SMap* mapCopy = malloc(sizeof(SMap));

	if(mapCopy == NULL)
		exit(-1);

	mapCopy->nbCells = map->nbCells;
	mapCopy->cells = malloc(mapCopy->nbCells * sizeof(SCell));

	if(mapCopy->cells == NULL)
		exit(-1);

	for(int i=0 ; i < mapCopy->nbCells; i++){
		mapCopy->cells[i].id = map->cells[i].id;
		mapCopy->cells[i].owner = map->cells[i].owner;
		mapCopy->cells[i].nbDices = map->cells[i].nbDices;
		mapCopy->cells[i].nbNeighbors = map->cells[i].nbNeighbors;
		mapCopy->cells[i].neighbors = malloc(mapCopy->cells[i].nbNeighbors * sizeof(SCell*));

		if(mapCopy->cells[i].neighbors == NULL)
			exit(-1);
	}

	for(int i=0 ; i < mapCopy->nbCells; i++){
		for(int j=0 ; j  < mapCopy->cells[i].nbNeighbors; j++){
			int idToAdd = map->cells[i].neighbors[j]->id;
			mapCopy->cells[i].neighbors[j] = &(mapCopy->cells[idToAdd]);
		}
	}
	return mapCopy;
}
