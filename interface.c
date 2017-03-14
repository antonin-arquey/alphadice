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

int PlayTurn(const SMap *map, Sturn *turn){
	int nbPays = map->nbCells;
	int nbMaxDices = 0;
	Scell *territoires = map->cells;

	for(i = 0; i < nbPays; i ++){
		If (territoires[i].owner == 1 && territoires[i].nbDices > nbMaxDices){
			nbMaxDices = territoires[i].nbDices;
			turn->cellFrom = territoires[i].id;
		}
	}
	Scell *voisins = turn->cellFrom->neighbors;
	nbVoisins = turn->cellFrom->nbNeighbors;
	nbMinDices = 10;
	for(i = 0; i < nbVoisins; i++){
		If (voisins[i].owner != 1 && voisins[i].nbDices < nbMinDices){
			nbMinDices = voisins[i].nbDices;
			turn->cellTo = territoires[i].id;
		}
	}
	return 1;
}
