#include "gameIA.h"
#include "arbre.h"
#include "interface.h"
#include "arbitre.h"//pour utiliser les fonction que Antonin à deja codées
#include <stdlib.h>
#include <stdio.h>


/*tableau des probabilités resultantes après un match de dés */
						/*1v1,		1v2,	  1v3, ...
						  2v1, ...
						  ...
						  																		8v8		*/
double tabProba[8][8] = {{0.416652, 0.092621, 0.011578, 0.000773, 0.000021, 0, 		  	0, 				0				},
												 {0.837916, 0.443657, 0.151995, 0.035888, 0.006106, 0.000768, 0.000071, 0.000005},
												 {0.973014, 0.778527, 0.453603, 0.191730, 0.060704, 0.014884, 0.002892, 0.000453},
												 {0.997304, 0.939230, 0.742871, 0.459467, 0.220467, 0.083447, 0.025436, 0.006385},
												 {0.999849, 0.987950, 0.909316, 0.718028, 0.463621, 0.242442, 0.103601, 0.036745},
												 {0.999996, 0.998215, 0.975288, 0.883991, 0.699587, 0.466700, 0.260018, 0.121535},
												 {1,				0.999801, 0.994674, 0.961525, 0.862370, 0.685111, 0.469154, 0.274377},
												 {1,				0.999984, 0.999072, 0.989525, 0.947766, 0.843873, 0.673508, 0.471108}};

int turnAI(int idPlayer, SMap *map, STurn *turn){
	int compteur = 0;
	STurn **turns = malloc(sizeof(STurn) * 200);
	SMap **maps = malloc(sizeof(SMap) * 200);
	double proba[200];

	for(int i = 0; i < map->nbCells; i++){
		if(map->cells[i].owner = idPlayer){
			for(int y = 0; y < map->cells[i].nbNeighbors; y++){
				if(map->cells[i].neighbors[y]->owner != idPlayer){
					turns[compteur]->cellFrom = map->cells[i].id;
					turns[compteur]->cellTo = map->cells[i].neighbors[y]->id;
					proba[compteur] = tabProba[map->cells[i].nbDices][map->cells[i].neighbors[y]->nbDices];
					maps[compteur] = deepCopy(map);
					moveTurnFail(maps[compteur], turns[compteur]);
					++compteur;
					proba[compteur] = 1 - proba[compteur - 1];
					maps[compteur] = deepCopy(map);
					moveTurnWin(maps[compteur], turns[compteur]);
					++compteur;
				}
			}
		}
	}
	compteur--;
	SArbre *arbre;
	arbre = createArbre(map, compteur);
	addElement(arbre->head, maps, turns, proba, compteur);
	free(arbre);
	free(turns);
	free(maps);
	return 1;
}


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
