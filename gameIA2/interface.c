#include "interface.h"
#include "gameIA.h"
#include "../log.h"
#include <string.h>
#include <stdio.h>

void InitGame(unsigned int id, unsigned int nbPlayer, SPlayerInfo *info){
	char teamates[6][50] = {"ARQUEY Antonin",
													"LE CORGUILLE Laouenan",
						    					"TRIAU Julien",
													"PASTOR Andréas"};
	char stratName[30] = "AlphaDice";
	memcpy(info->members, teamates, 300);
	memcpy(info->name, stratName, 30);
}

void EndGame(unsigned int idWinner)
{
	char str[10];
	Log("---\n");
	sprintf(str, "%d\n", idWinner);
	Log(str);
	Log("---\n");
}

int PlayTurn(int idPlayer, const SMap *map, STurn *turn){
	SArbre arbre[1];//*arbre = malloc(sizeof(SArbre));
	Noeud newHead[1];
	STurn bestTurn[1];
	arbre->head = newHead;//malloc(sizeof(Noeud));
	arbre->head->bestTurn = bestTurn;
	arbre->head->bestTurn->cellFrom = -1;
	arbre->head->bestTurn->cellTo = -1;
	arbre->head->map = deepCopy(map); //mapCopy;
  turnIA(idPlayer, arbre->head, map, 0);//peut-etre pas besoin de passer la map en param
	if(arbre->head->bestTurn->cellFrom != -1 && arbre->head->bestTurn->cellTo != -1){//return evalArbre(idPlayer, arbre->head, turn, 2);
		turn->cellFrom = arbre->head->bestTurn->cellFrom;
		turn->cellTo = arbre->head->bestTurn->cellTo;
		printf("cellFrom %d -> cellTo %d\n", turn->cellFrom, turn->cellTo);
		return 1;
	}
	return 0;
}

int PlayTurnDeux(int idPlayer, const SMap *map, STurn *turn){
	int diff = 0;
	int compteur = 0;
	for(int i = 0; i< map->nbCells; i++){
		if(map->cells[i].owner == idPlayer && map->cells[i].nbDices > 1){
			for(int j = 0; j < map->cells[i].nbNeighbors; j++){
				if(map->cells[i].neighbors[j]->owner != idPlayer && (map->cells[i].nbDices - map->cells[i].neighbors[j]->nbDices) > diff){
					diff = map->cells[i].nbDices - map->cells[i].neighbors[j]->nbDices;
					turn->cellFrom = map->cells[i].id;
					turn->cellTo = map->cells[i].neighbors[j]->id;
					compteur += 1;
				} else if(map->cells[i].neighbors[j]->owner != idPlayer){
					compteur += 1;
				}
			}
		}
	}
	printf("il y a %d possibilitées\n", compteur);
	if(diff != 0){
		return 1;
	}
	return 0;
}
