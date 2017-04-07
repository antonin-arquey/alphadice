#include "interface.h"
#include "gameIA.h"
#include "../log.h"
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
	char str[10];
	Log("###\n");
	sprintf(str, "%d\n", idWinner);
	Log(str);
	Log("###\n");
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
	printf("------------ nouvelle requete de turn ---------------\n");
	arbre->head->map = deepCopy(map, nbrPlayer);
    turnIA(id, id, arbre->head, map, turn, 0);
	if(turn->cellTo != 0 && turn->cellFrom != 0){
		printf("PlayTurn cellFrom %d -> cellTo %d\n", turn->cellFrom, turn->cellTo);
		freeMap(arbre->head->map);
		return 1;
	}
	printf("--- je ne veux pas joueur ---\n");
	freeMap(arbre->head->map);
	return 0;
}

int getNbPlayer(){
	return nbrPlayer;
}
