#include "interface.h"
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
	printf("Stratégie : %s\n", info->name);
	printf("Noms : \n");

	for(int i=0 ; i < 4 ; i++)	{
		printf("%s\n", info->members[i]);
	}
}

int PlayTurn(const SMap *map, STurn *turn){
	int nbPays = map->nbCells;
	int nbMaxDices = 0;
	SCell *territoires = map->cells;

	for(int i = 0; i < nbPays; i ++){
		if (territoires[i].owner == 1 && territoires[i].nbDices > nbMaxDices){
			nbMaxDices = territoires[i].nbDices;
			turn->cellFrom = territoires[i].id;
		}
	}
	SCell **voisins = map->cells[turn->cellFrom].neighbors;
	int nbVoisins = map->cells[turn->cellFrom].nbNeighbors;
	int nbMinDices = 10;
	for(int i = 0; i < nbVoisins; i++){
		if (voisins[i]->owner != 1 && voisins[i]->nbDices < nbMinDices){
			nbMinDices = voisins[i]->nbDices;
			turn->cellTo = territoires[i].id;
		}
	}
	return 1;
}
