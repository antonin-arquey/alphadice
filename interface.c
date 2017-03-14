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

	for(int i=0 ; i < 4 ; i++)
	{
		printf("%s\n", info->members[i]);
	}
}
