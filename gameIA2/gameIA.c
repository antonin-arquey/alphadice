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

int evalArbre(int idPlayer, Noeud *head, STurn *turn, int profondeur){
	//return bestMove(idPlayer, head, turn);
}

void turnIA(int idPlayer, Noeud *head, const SMap *map, STurn *turn, int profondeur){
	int compteur = 0; int compteurBis = 0;
	SMap *mapCopy;
	ChanceNode nodes[100];
	STurn turns[100];
	Noeud fils[200];

	for(int i = 0; i < map->nbCells; i++){
		if(map->cells[i].owner == idPlayer && map->cells[i].nbDices > 1){
			for(int j = 0; j < map->cells[i].nbNeighbors; j++){
				if(map->cells[i].neighbors[j]->owner != idPlayer){
					nodes[compteur].turn = &turns[compteur];//malloc(sizeof(STurn));//peut etre modifier et plus utiliser les STurn
					nodes[compteur].turn->cellFrom = map->cells[i].id;
					nodes[compteur].turn->cellTo = map->cells[i].neighbors[j]->id;
					nodes[compteur].probaDroite = tabProba[map->cells[i].nbDices][map->cells[i].neighbors[j]->nbDices];

					nodes[compteur].filsDroit = &fils[compteurBis];//malloc(sizeof(Noeud));
					compteurBis += 1;
					nodes[compteur].filsGauche = &fils[compteurBis];//malloc(sizeof(Noeud));
					//freeMap(mapCopy);
					mapCopy = deepCopy(map);
					moveTurnWin(mapCopy,nodes[compteur].turn);
					nodes[compteur].filsDroit->map = mapCopy;
					//freeMap(mapCopy);
					mapCopy = deepCopy(map);
					moveTurnFail(mapCopy,nodes[compteur].turn);
					nodes[compteur].filsGauche->map = mapCopy;

					compteur += 1; compteurBis += 1;
				}
			}
		}
	}
	head->nbFils = compteur;
	if(compteur > 0){
		ChanceNode filsNodes[compteur];
		head->fils = filsNodes;
		for(int x = 0; x < compteur; x++){//a cause du <=
			if(profondeur > 0){
				turnIA(idPlayer, nodes[x].filsDroit, nodes[x].filsDroit->map, turn, profondeur - 1);
				turnIA(idPlayer, nodes[x].filsGauche, nodes[x].filsGauche->map, turn, profondeur - 1);
			}
			head->fils[x] = nodes[x];
		}

		EndTurnNode endTurnNode[1];// = malloc(sizeof(EndTurnNode));
		endTurnNode->nbFils = 5;
		Noeud nodeAlea[5];
		for(int i = 0; i < endTurnNode->nbFils; i++){
			mapCopy = deepCopy(map);
			endTurn(idPlayer, mapCopy);
			nodeAlea[i].map = mapCopy;
			if(profondeur > 0)
				turnIA(idPlayer, &nodeAlea[i], nodeAlea[i].map, turn, profondeur - 1);
		}
		endTurnNode->filsAlea = nodeAlea;

		head->mapAlea = endTurnNode;

		if(profondeur == 0){
			bestMove(idPlayer, head);
			turn->cellFrom = head->bestTurn->cellFrom;
			turn->cellTo = head->bestTurn->cellTo;
		}else
			bestMove2(idPlayer, head);
			//printf("mov2 cellFrom %d -> cellTo %d\n", head->bestTurn->cellFrom, head->bestTurn->cellTo);
	}
	printf("fin turnIA cellFrom %d -> cellTo %d\n", head->bestTurn->cellFrom, head->bestTurn->cellTo);
	printf("fin turnIA 2 cellFrom %d -> cellTo %d\n", turn->cellFrom, turn->cellTo);
}

void bestMove2(int idPlayer, Noeud *head){
	head->maxQ = mapEvaluation(idPlayer, head->map);//voir s'il faut pas regarder les fils alea
	STurn bestTurn[1];
	head->bestTurn = bestTurn;
	head->bestTurn->cellFrom = -1;
	head->bestTurn->cellTo = -1;
	double val;
	for(int i = 0; i < head->nbFils; i++){
		val = head->fils[i].probaDroite * head->fils[i].filsDroit->maxQ + (1 - head->fils[i].probaDroite) * head->fils[i].filsGauche->maxQ;
		if (val > head->maxQ){
			head->maxQ = val;
			//printf("move2 cellFrom %d -> cellTo %d\n", head->bestTurn->cellFrom, head->bestTurn->cellTo);
			head->bestTurn->cellFrom = head->fils[i].turn->cellFrom;
			head->bestTurn->cellTo = head->fils[i].turn->cellTo;
		}
	}
}

void bestMove(int idPlayer, Noeud *head){
	head->maxQ = mapEvaluation(idPlayer, head->map);
	STurn bestTurn[1];
	head->bestTurn = bestTurn;
	head->bestTurn->cellFrom = -1;
	head->bestTurn->cellTo = -1;
	double val;
	for(int i = 0; i < head->nbFils; i++){
		val = head->fils[i].probaDroite * mapEvaluation(idPlayer, head->fils[i].filsDroit->map) + (1 - head->fils[i].probaDroite) * mapEvaluation(idPlayer, head->fils[i].filsGauche->map);
		if (val > head->maxQ){
			head->maxQ = val;
			head->bestTurn->cellFrom = head->fils[i].turn->cellFrom;
			head->bestTurn->cellTo = head->fils[i].turn->cellTo;
			printf("move cellFrom %d -> cellTo %d\n", head->bestTurn->cellFrom, head->bestTurn->cellTo);
		}
	}
}

double mapEvaluation(int idPlayer, SMap *map){
	if(map == NULL)
		exit(-1);
	double alpha = 0; double beta = 1;
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

	int nbDiceDistributed = getDicesToDistribute(idPlayer, map); // + map->stack[idPlayer];
	int random;
	//On prend un sommet aléatoire qu'il possède et on ajoute un dé
	/*for(int i = 1 ; i <= nbDiceDistributed ; i++){
		random = aleatoire(0, nbPlayerCell-1);
		if(map->cells[playerCell[random]].nbDices < 8){
			map->cells[playerCell[random]].nbDices++;
		}
		else{
			if(allCellsFull(idPlayer, map)){
				map->stack[idPlayer] += nbDiceDistributed - i + 1;
				break;
			}
			else{
				i--;
			}
		}
	}*/
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
