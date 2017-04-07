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


//fonction recursive pour prendre analyser les solutions qui s'offre à l'ia
void turnIA(int id, int idPlayer, Noeud *head, const SMap *map, STurn *turn, int profondeur){
	//initialisation des différentes variables necessaires
	int compteur = 0; int compteurBis = 0;
	SMap **mapCopys = malloc(200 * sizeof(*map));
	ChanceNode nodes[100];
	STurn turns[100];
	Noeud fils[200];

	//on classe l'ensemble des coups possible à la position courante du jeu
	for(int i = 0; i < map->nbCells; i++){//itération sur l'ensemble des territoires
		if(map->cells[i].owner == idPlayer && map->cells[i].nbDices > 1){//si le territoires est a nous et que l'on a assez de dés pour attaquer ...
			for(int j = 0; j < map->cells[i].nbNeighbors; j++){//on regarde tous les voisins ...
				if(map->cells[i].neighbors[j]->owner != idPlayer){//et si l'un de ces voisins est un adversaire on le prend en compte dans notre arbre
					//ajout des éléments pour le calcul qui va suivre
					nodes[compteur].turn = &turns[compteur];
					nodes[compteur].turn->cellFrom = map->cells[i].id;
					nodes[compteur].turn->cellTo = map->cells[i].neighbors[j]->id;
					//probabilité de gangner le match de dés qui va suivre
					nodes[compteur].probaDroite = tabProba[map->cells[i].nbDices][map->cells[i].neighbors[j]->nbDices];

					nodes[compteur].filsDroit = &fils[compteurBis];
					mapCopys[compteurBis] = deepCopy(map, getNbPlayer());
					//cas ou l'on gagnerait à l'attaque du territoire
					moveTurnWin(mapCopys[compteurBis],nodes[compteur].turn);
					nodes[compteur].filsDroit->map = mapCopys[compteurBis];
					compteurBis += 1;
					nodes[compteur].filsGauche = &fils[compteurBis];
					mapCopys[compteurBis] = deepCopy(map, getNbPlayer());
					//cas où l'on perdrait à l'attaque du territoire
					moveTurnFail(mapCopys[compteurBis],nodes[compteur].turn);
					nodes[compteur].filsGauche->map = mapCopys[compteurBis];

					compteur += 1; compteurBis += 1;
				}
			}
		}
	}
	//nombre de coup possible qui s'offre à nous
	head->nbFils = compteur;
	if(compteur > 0){
		
		ChanceNode filsNodes[compteur];
		head->fils = filsNodes;
		for(int x = 0; x < compteur; x++){
			if(profondeur > 0){//si la profondeur est plus grande que zero on continue de chercher plus profond
				turnIA(id, idPlayer, nodes[x].filsDroit, nodes[x].filsDroit->map, turn, profondeur - 1);
				turnIA(id, idPlayer, nodes[x].filsGauche, nodes[x].filsGauche->map, turn, profondeur - 1);
			}
			head->fils[x] = nodes[x];
		}

		//on ajoute des coup de endTurn où l'on refuse de joueur pour voir ce que ca nous rapporte
		EndTurnNode endTurnNode[1];
		endTurnNode->nbFils = 3;
		Noeud nodeAlea[3];
		for(int i = 0; i < endTurnNode->nbFils; i++){
			mapCopys[compteurBis] = deepCopy(map, getNbPlayer());
			endTurn(idPlayer, mapCopys[compteurBis]);
			nodeAlea[i].map = mapCopys[compteurBis];
			compteurBis++;
			if(profondeur > 0){//si la profondeut est plus grande que zero on simule les tours des autres joueurs
				int copyID = (idPlayer + 1) % getNbPlayer();//id du joueur suivant
				turnIA(id, copyID, &nodeAlea[i], nodeAlea[i].map, turn, profondeur - 1);
			}
		}
		endTurnNode->filsAlea = nodeAlea;
		head->mapAlea = endTurnNode;
		head->bestTurn = malloc(sizeof(STurn));
		//on evalue la position dans laquelle on est 
		if(profondeur == 0)
			bestMove(id, head); // si la profondeur est zero on evalue la map
		else{
			bestMove2(idPlayer, head); // si la profondeur est plus grande que zero on evalue a partir des evaluations plus profondes
		}
		turn->cellFrom = head->bestTurn->cellFrom;//stockage des turns finaux
		turn->cellTo = head->bestTurn->cellTo;
		free(head->bestTurn);
	}

	for(int z = 0 ; z < compteurBis; z++){//on free les elements
		freeMap(mapCopys[z]);
	}
	free(mapCopys);

}

//fonction d'évaluation pour les positions qui ne sont pas dans les feuilles de l'arbre
void bestMove2(int idPlayer, Noeud *head){
	for (int i = 0; i < getNbPlayer(); i++) {
		head->maxQ[i] = inactionTurn2(idPlayer, head);//on regarde la valeur si l'on fait rien pour ts les joueurs
	}
	double val;
	double valmax = head->maxQ[idPlayer];
	int compteur = 0;
	for(int i = 0; i < head->nbFils; i++){//on regarde la valeur de chaque attaque par rapport au probabilités de succès
		val = head->fils[i].probaDroite * head->fils[i].filsDroit->maxQ[idPlayer] + (1 - head->fils[i].probaDroite) * head->fils[i].filsGauche->maxQ[idPlayer];
		if (val > valmax){//on garde la meilleur attaque
			valmax = val;
			compteur = i;
		}
	}
	if(compteur == 0){// pas de meilleur attaque que rien faire
		head->bestTurn->cellFrom = 0;
		head->bestTurn->cellTo = 0;
		return;
	}
	for (int i = 0; i < getNbPlayer(); i++){//on met a jour les valeurs pour la meilleure attaque si elle est différente de l'inaction
		head->maxQ[i] = head->fils[compteur].probaDroite * head->fils[compteur].filsDroit->maxQ[i] + (1 - head->fils[compteur].probaDroite) * head->fils[compteur].filsGauche->maxQ[i];
	}
	//on stocke la meilleure attaque à jouer
	head->bestTurn->cellFrom = head->fils[compteur].turn->cellFrom;
	head->bestTurn->cellTo = head->fils[compteur].turn->cellTo;

}

//évaluation pour évaluer l'inaction au niveau d'un noeud différent d'une feuille
double inactionTurn2(int idPlayer, Noeud *head){
	double val = 0;
	for (int i = 0; i < head->mapAlea->nbFils; i++) {
		val += head->mapAlea->filsAlea[i].maxQ[idPlayer];//on regarde la valeur de l'attaque du prochain joueur
	}
	return val / head->mapAlea->nbFils;//on fait une moyenne par rapport a différentes cartes après répartition des dés gangnés pendant le tour
}

//fonction d'évaluation au niveau des feuilles de l'arbre
void bestMove(int idPlayer, Noeud *head){
	for (int i = 0; i < getNbPlayer(); i++){
		head->maxQ[i] =  inactionTurn(i, head);
	}
	double val;
	double valmax = head->maxQ[idPlayer];
	int compteur = 0;
	for(int i = 0; i < head->nbFils; i++){// la différence se situe ici ou l'on évalue en fonction de la map et pas des prochains coups (car ces coups n'ont pas été simulés)
		val = head->fils[i].probaDroite * mapEvaluation(idPlayer, head->fils[i].filsDroit->map) + (1 - head->fils[i].probaDroite) * mapEvaluation(idPlayer, head->fils[i].filsGauche->map);
		if (val > valmax){
			valmax = val;
			compteur = i;
		}
	}
	if(compteur == 0){
		head->bestTurn->cellFrom = 0;
		head->bestTurn->cellTo = 0;
		return;
	}

	for(int i = 0; i < getNbPlayer(); i++){//recupération des valueurs de la meilleure attaque
		head->maxQ[i] = head->fils[compteur].probaDroite * mapEvaluation(i, head->fils[compteur].filsDroit->map) + (1 - head->fils[compteur].probaDroite) * mapEvaluation(i, head->fils[compteur].filsGauche->map);
	}
	head->bestTurn->cellFrom = head->fils[compteur].turn->cellFrom;
	head->bestTurn->cellTo = head->fils[compteur].turn->cellTo;
}

//evaluation pour les feulles de l'arbre quand l'on choisit de ne pas jouer
double inactionTurn(int idPlayer, Noeud *head){
	double val = 0;
	idPlayer = (idPlayer + 1) % 8;
	for (int i = 0; i < head->mapAlea->nbFils; i++) {
		val += mapEvaluation(idPlayer, head->mapAlea->filsAlea[i].map);//on évalue directement la map
	}
	if(val == 0)
		return 0;
	return val / head->mapAlea->nbFils;//on fait toujours une moyenne par rapport à différente issue de distribution de dés
}

//fonction qui évalue la map (elle évalue la proportion à gagner d'un joueur)
double mapEvaluation(int idPlayer, SMap *map){
	double alpha = 0.5; double beta = 0.5; double gamma = 2;
	double value = alpha * getAmountOfDices(idPlayer, map) + beta * getDicesToDistribute(idPlayer, map) + getnbTerritoires(idPlayer, map);
	return value;
}

//simule que l'attaque a échoué
void moveTurnFail(SMap *map, STurn *turn){
	map->cells[turn->cellFrom].nbDices = 1;
}

//simule que l'attaque a reussi
void moveTurnWin(SMap *map, STurn *turn){
	SCell *cellAttacker = &map->cells[turn->cellFrom];
	SCell *cellDefender = &map->cells[turn->cellTo];
	cellDefender->owner = cellAttacker->owner;
	cellDefender->nbDices = cellAttacker->nbDices - 1;
	cellAttacker->nbDices = 1;
}

//permet de faire une copy profonde de la map
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


//Fonction qui répartit les dés a la fin d'un tour d'un joueur
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

//fonction qui permet de free l'ensemble des éléments de la map
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

//permet de retourner le nombre de dés possédés par le joueur
int getAmountOfDices(int idPlayer, SMap *map){
	int nbDices = 0;
	for(int i = 0; i < map->nbCells; i++){
		if(map->cells[i].owner == idPlayer){
			nbDices += map->cells[i].nbDices;
		}
	}
	return nbDices;
}

//permet de retourne le nombre de territoires possédés par le joueur
int getnbTerritoires(int idPlayer, SMap *map){
	int nbTerritoires = 0;
	for(int i = 0; i < map->nbCells; i++){
		if(map->cells[i].owner == idPlayer){
			nbTerritoires += 1;
		}
	}
	return nbTerritoires;
}

//Trouve le plus grand nombre de territoire connexe appartenant au joueur passé en paramètre
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

//fonction qui regarde si un élément est dans le tableau
int inTab(int id, int tab[], int lenTab){
	for(int i = 0 ; i  < lenTab ; i++){
		if(tab[i] == id)
			return 1;
	}
	return 0;
}
