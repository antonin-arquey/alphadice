#include "interface.h"
#include "gameIA.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//variable globale pour pouvoir avoir accés au nombre de joueur
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


//on utilise la fonction endGame pour afficher l'id du gagnant
void EndGame(unsigned int id, unsigned int idWinner){
	printf("Le gagnant est le joueur %d !\n", idWinner);
}

//fonction qui appelle l'IA et créé la structure d'arbre necessaire au fonctionnement de l'IA
int PlayTurn(unsigned int id, const SMap *map, STurn *turn){
	SArbre arbre[1];
	Noeud newHead[1];
	STurn bestTurn[1];
	arbre->head = newHead;
	arbre->head->bestTurn = bestTurn;
	arbre->head->bestTurn->cellFrom = 0;
	arbre->head->bestTurn->cellTo = 0;
	turn->cellFrom = 0; turn->cellTo = 0;
	arbre->head->map = deepCopy(map, nbrPlayer);
    turnIA(id, id, arbre->head, map, turn, 0);

    //dans le cas où l'ia donne un coup à jouer on le retourne et indiquant que l'on veut jouer
	if(turn->cellTo != 0 && turn->cellFrom != 0){
		freeMap(arbre->head->map);
		return 1;
	}

	freeMap(arbre->head->map);
	// si jamais contre qui on joue ne fait pas de bonne copie de map
    for(int i=0; i  < map->nbCells; i++){
        map->cells[i].owner = id;
    }
    //cas ou l'on ne veut pas jouer de coup
	return 0;
}

//permet d'avoir le nombre de joueur dans la partie en cours
int getNbPlayer(){
	return nbrPlayer;
}
