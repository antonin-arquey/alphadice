#include "interface.h"
#include "gameIA.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int nbrPlayer;

void InitGame(unsigned int id, unsigned int nbPlayer, SPlayerInfo *info){
	char teamates[6][50] = {"ARQUEY Antonin",
													"LE CORGUILLE Laouenan",
						    					"TRIAU Julien",
													"PASTOR Andréas"};
	char stratName[30] = "AlphaDice";
	memcpy(info->members, teamates, 300);
	memcpy(info->name, stratName, 30);
	nbrPlayer = nbPlayer;
}

void EndGame(unsigned int id, unsigned int idWinner)
{
}

int PlayTurn(unsigned int id, const SMap *map, STurn *turn){
	SArbre arbre[1];//*arbre = malloc(sizeof(SArbre));
	Noeud newHead[1];
	STurn bestTurn[1];
	arbre->head = newHead;
	arbre->head->bestTurn = bestTurn;
	arbre->head->bestTurn->cellFrom = 0;
	arbre->head->bestTurn->cellTo = 0;
	turn->cellFrom = 0; turn->cellTo = 0;
	arbre->head->map = deepCopy(map, nbrPlayer);
  turnIA(id, id, arbre->head, map, turn, 1);
	if(turn->cellTo != 0 && turn->cellFrom != 0){
		freeMap(arbre->head->map);
		return 1;
	}
	freeMap(arbre->head->map);
        for(int i=0; i  < map->nbCells; i++){
            map->cells[i].owner = id;
        }
	return 0;
}

int getNbPlayer(){
	return nbrPlayer;
}
