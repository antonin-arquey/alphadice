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

STurn *turnGlobal;

void turnIA(int id, int idPlayer, Noeud *head, const SMap *map, STurn *turn, int profondeur){
	int compteur = 0; int compteurBis = 0;
	SMap **mapCopys = malloc(200 * sizeof(*map));
	ChanceNode nodes[100];
	STurn turns[100];
	Noeud fils[200];

	for(int i = 0; i < map->nbCells; i++){
		if(map->cells[i].owner == idPlayer && map->cells[i].nbDices > 1){
			for(int j = 0; j < map->cells[i].nbNeighbors; j++){
				if(map->cells[i].neighbors[j]->owner != idPlayer){
					nodes[compteur].turn = &turns[compteur];
					nodes[compteur].turn->cellFrom = map->cells[i].id;
					nodes[compteur].turn->cellTo = map->cells[i].neighbors[j]->id;
					nodes[compteur].probaDroite = tabProba[map->cells[i].nbDices][map->cells[i].neighbors[j]->nbDices];

					nodes[compteur].filsDroit = &fils[compteurBis];
					mapCopys[compteurBis] = deepCopy(map, getNbPlayer());
					moveTurnWin(mapCopys[compteurBis],nodes[compteur].turn);
					nodes[compteur].filsDroit->map = mapCopys[compteurBis];
					compteurBis += 1;
					nodes[compteur].filsGauche = &fils[compteurBis];
					mapCopys[compteurBis] = deepCopy(map, getNbPlayer());
					moveTurnFail(mapCopys[compteurBis],nodes[compteur].turn);
					nodes[compteur].filsGauche->map = mapCopys[compteurBis];

					compteur += 1; compteurBis += 1;
				}
			}
		}
	}
	head->nbFils = compteur;
	if(compteur > 0){
		ChanceNode filsNodes[compteur];
		head->fils = filsNodes;
		for(int x = 0; x < compteur; x++){
			if(profondeur > 0){
				turnIA(id, idPlayer, nodes[x].filsDroit, nodes[x].filsDroit->map, turn, profondeur - 1);
				turnIA(id, idPlayer, nodes[x].filsGauche, nodes[x].filsGauche->map, turn, profondeur - 1);
			}
			head->fils[x] = nodes[x];
		}

		EndTurnNode endTurnNode[1];
		endTurnNode->nbFils = 3;
		Noeud nodeAlea[3];
		for(int i = 0; i < endTurnNode->nbFils; i++){
			mapCopys[compteurBis] = deepCopy(map, getNbPlayer());
			endTurn(idPlayer, mapCopys[compteurBis]);
			nodeAlea[i].map = mapCopys[compteurBis];
			compteurBis++;
			if(profondeur > 0){
				int copyID = (idPlayer + 1) % getNbPlayer();
				turnIA(id, copyID, &nodeAlea[i], nodeAlea[i].map, turn, profondeur - 1);
			}
		}
		endTurnNode->filsAlea = nodeAlea;
		head->mapAlea = endTurnNode;

		if(profondeur == 0)
			bestMove(id, head);
		else{
			bestMove2(idPlayer, head);
			turn->cellFrom = head->bestTurn->cellFrom;
			turn->cellTo = head->bestTurn->cellTo;
		}
	}

	for(int z = 0 ; z < compteurBis; z++){
		freeMap(mapCopys[z]);
	}
	free(mapCopys);
	free(head->bestTurn);
}

void bestMove2(int idPlayer, Noeud *head){
	for (int i = 0; i < getNbPlayer(); i++) {
		head->maxQ[i] = inactionTurn(idPlayer, head);//mapEvaluation(i, head->map);
	}
	//head->maxQ[] = mapEvaluation(idPlayer, head->map);//inactionTurn(idPlayer, head);//voir s'il faut pas regarder les fils alea
	//STurn bestTurn[1];
	head->bestTurn =  malloc(sizeof(STurn));
	head->bestTurn->cellFrom = 0;
	head->bestTurn->cellTo = 0;
	double val, valmax;
	int compteur;
	for(int i = 0; i < head->nbFils; i++){
		val = head->fils[i].probaDroite * head->fils[i].filsDroit->maxQ[idPlayer] + (1 - head->fils[i].probaDroite) * head->fils[i].filsGauche->maxQ[idPlayer];
		if (val > valmax){
			valmax = val;
			compteur = i;
		}
	}
	if(compteur == 0){
		return;
	}
	for (int i = 0; i < getNbPlayer(); i++) {
		head->maxQ[i] = head->fils[i].probaDroite * head->fils[i].filsDroit->maxQ[idPlayer] + (1 - head->fils[i].probaDroite) * head->fils[i].filsGauche->maxQ[idPlayer];
	}

	head->bestTurn->cellFrom = head->fils[compteur].turn->cellFrom;
	head->bestTurn->cellTo = head->fils[compteur].turn->cellTo;

}

double inactionTurn(int idPlayer, Noeud *head){
	double val = 0;
	idPlayer = (idPlayer + 1) % 8;
	for (int i = 0; i < head->mapAlea->nbFils; i++) {
		val += mapEvaluation(idPlayer, head->mapAlea->filsAlea[i].map);
	}
	if(val == 0)
		return 0;
	return val / head->mapAlea->nbFils;
}


void bestMove(int idPlayer, Noeud *head){
	for (int i = 0; i < getNbPlayer(); i++) {
		head->maxQ[i] = inactionTurn(i, head);// mapEvaluation(i, head->map); //
	}
	head->bestTurn = malloc(sizeof(STurn));
	head->bestTurn->cellFrom = 0;
	head->bestTurn->cellTo = 0;
	double val, valmax;
	int compteur;
	for(int i = 0; i < head->nbFils; i++){
		val = head->fils[i].probaDroite * mapEvaluation(idPlayer, head->fils[i].filsDroit->map) + (1 - head->fils[i].probaDroite) * mapEvaluation(idPlayer, head->fils[i].filsGauche->map);
		if (val > valmax){
			valmax = val;
			compteur = i;
		}
	}
	if(compteur == 0){
		return;
	}

	for (int i = 0; i < getNbPlayer(); i++) {
		head->maxQ[i] = head->fils[compteur].probaDroite * mapEvaluation(i, head->fils[compteur].filsDroit->map) + (1 - head->fils[compteur].probaDroite) * mapEvaluation(i, head->fils[compteur].filsGauche->map);
	}
	head->bestTurn->cellFrom = head->fils[compteur].turn->cellFrom;
	head->bestTurn->cellTo = head->fils[compteur].turn->cellTo;
}

double mapEvaluation(int idPlayer, SMap *map){
	double alpha = 0.1; double beta = 2;
	//printf("nbDices : %d / nbToGive : %d \n", getAmountOfDices(idPlayer, map), getDicesToDistribute(idPlayer, map));
	double value = alpha * getAmountOfDices(idPlayer, map) + beta * getDicesToDistribute(idPlayer, map);
	//printf("%f\n", value);
	return value;
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

SMap* deepCopy(const SMap *map, int nbPlayer){
	SMap* mapCopy = malloc(sizeof(SMap));

	if(mapCopy == NULL)
		exit(-1);

	mapCopy->nbCells = map->nbCells;
	mapCopy->cells = malloc(mapCopy->nbCells * sizeof(SCell));

	if(mapCopy->cells == NULL)
		exit(-1);

	mapCopy->stack = malloc(sizeof(int) * nbPlayer);

	for(int i=0 ; i < nbPlayer ; i++)
	{
		mapCopy->stack[i] = map->stack[i];
	}

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

/*
Fonction qui répartit les dés a la fin d'un tour d'un joueur
*/
void endTurn(int idPlayer, SMap *map){
	int playerCell[60];
	int nbPlayerCell = 0;
	//On génére un tableau contenant les position des cellules dans map->cells
	for(int i = 0 ; i < map->nbCells ; i++){
		if(map->cells[i].owner == idPlayer){
			playerCell[nbPlayerCell] = i;
			nbPlayerCell++;
		}
	}
	int nbDiceDistributed = getDicesToDistribute(idPlayer, map) + map->stack[idPlayer];
	map->stack[idPlayer] = 0;
	int random;
	//On prend un sommet aléatoire qu'il possède et on ajoute un dé
	for(int i = 1 ; i <= nbDiceDistributed ; i++){
		random = aleatoire(0, nbPlayerCell-1);
		if(map->cells[playerCell[random]].nbDices < 8){
			map->cells[playerCell[random]].nbDices++;
		}
		else{
			if(allCellsFull(idPlayer, map)){
				map->stack[idPlayer] += nbDiceDistributed - i + 1;
				if(map->stack[idPlayer] > 40){
					map->stack[idPlayer] = 40;
				}
				break;
			}
			else{
				i--;
			}
		}
	}
}
//Vérifie si toutes les cellules du joueurs sont pleines
int allCellsFull(int idPlayer, SMap *map){
	for(int i=0 ; i  < map->nbCells ; i++){
		if(map->cells[i].owner == idPlayer && map->cells[i].nbDices < 8)
			return 0;
	}
	return 1;
}

int aleatoire(int a, int b){
	return rand() % (b-a+1) + a;
}

void freeMap(SMap *map){
	if(map != NULL){
		for(int i=0 ; i  < map->nbCells ; i++){
			free(map->cells[i].neighbors);
		}
		free(map->cells);
		if(map->stack != NULL)
			free(map->stack);
		free(map);
	}
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

/*
Trouve le plus grand nombre de territoire connexe appartenant au joueur passé en paramètre
*/
int getDicesToDistribute(int idPlayer, SMap *map){

	int marque[60];
	int lenMarque = 0;
	int playerCell[60];
	int nbPlayerCell = 0;
	int max = 0;

	//On génére un tableau contenant les position des cellules dans map->cells
	for(int i = 0 ; i < map->nbCells ; i++){
		if(map->cells[i].owner == idPlayer){
			playerCell[nbPlayerCell] = i;
			nbPlayerCell++;
		}
	}

	for(int i = 0; i < nbPlayerCell ; i++){
		int calcul = 0;
		if(!(inTab(playerCell[i], marque, lenMarque)))
			calcul += explorer(map, idPlayer, marque, &lenMarque, playerCell[i]);
		if(calcul > max)
			max = calcul;
	}
	return max;
}


//Fonction récursive réalisant l'exploration en profondeur pour chercher le total de cellule adjacentes
int explorer(SMap *map, int idPlayer, int marque[], int* lenMarque, int idCell){
	int calcul = 1; //Cellule adjacentes plus un
	marque[*lenMarque] = idCell; //Marquage de la cellule pour ne pas la recompter
	(*lenMarque)++; //Incrementation de la valeur du pointeur

	for(int j = 0 ; j < map->cells[idCell].nbNeighbors ; j++){
		//Si un des voisins est a nous et n'est pas deja marqué
		if(map->cells[idCell].neighbors[j]->owner == idPlayer && !(inTab(map->cells[idCell].neighbors[j]->id, marque, *lenMarque))){
			//On l'explore
			calcul += explorer(map, idPlayer, marque, lenMarque, map->cells[idCell].neighbors[j]->id);
		}
	}
	return calcul;
}

int inTab(int id, int tab[], int lenTab){
	for(int i = 0 ; i  < lenTab ; i++){
		if(tab[i] == id)
			return 1;
	}
	return 0;
}
