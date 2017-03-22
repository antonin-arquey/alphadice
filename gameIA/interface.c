#include "interface.h"
#include "gameIA.h"
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

int PlayTurn(int idPlayer, const SMap *map, STurn *turn){
  return turnIA(idPlayer, map, turn);
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
					//compteur += 1;
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

int PlayTurnFirst(int idPlayer, const SMap *map, STurn *turn){
	int nbPays = map->nbCells;
	int nbMaxDices = 0;
	SCell *territoires = map->cells;
	int modif = 0;

	for(int i = 0; i < nbPays; i ++){
		if (territoires[i].owner == idPlayer && territoires[i].nbDices > nbMaxDices && territoires[i].nbDices > 1){
			nbMaxDices = territoires[i].nbDices;
			turn->cellFrom = territoires[i].id;
			modif = 1;
		}
	}
	if(modif == 0){
		printf("Le joueur a perdu\n");
		return 0;
	}
	modif = 0;
	SCell **voisins = map->cells[turn->cellFrom].neighbors;
	int nbVoisins = map->cells[turn->cellFrom].nbNeighbors;
	int nbMinDices = 10;
	int amoi = 0;
	for(int i = 0; i < nbVoisins; i++){
		if (voisins[i]->owner != idPlayer && voisins[i]->nbDices < nbMinDices){
			nbMinDices = voisins[i]->nbDices;
			turn->cellTo = voisins[i]->id;
			modif = 1;
		}
		if(voisins[i]->owner == idPlayer){
			amoi++;
		} else if(modif == 0){
			printf("%d\n", voisins[i]->nbDices);
		}
	}
	if(modif == 0){
		printf("nbVoisins : %d/%d\n", amoi, nbVoisins);
		return 0;
	}
	return 1;
}

int combienDeDices(int idPlayer, const SMap *map){
	int nbDices = 0;
	for(int i = 0; i < map->nbCells; i++){
		if(map->cells[i].owner == idPlayer){
			nbDices += map->cells[i].nbDices;
		}
	}
	return nbDices;
}

int combienDeTerritoires(int idPlayer, const SMap *map){
	int nbTerritoires = 0;
	for(int i = 0; i < map->nbCells; i++){
		if(map->cells[i].owner == idPlayer){
			nbTerritoires += 1;
		}
	}
	return nbTerritoires;
}

int combienDeReserves(int idPlayer, const SMap *map){
	return map->stack[idPlayer];
}
