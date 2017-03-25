#include "map.h"
#include "arbitre.h"
#include "log.h"
#include <stdlib.h>
#include <stdio.h>

/*
Fonction vérifiant un tour rendu
Renvoie 1 si le tour est bon, -1 si il est pas valide
*/
void verify(unsigned int i, SMap *map,STurn *turn){
	if(verifyTurn(i, map, turn)){
		moveTurn(map, turn);
	}
}

int verifyTurn(unsigned int idPlayer, SMap *map, STurn *turn){
	//Verifiez que la cellule de départ est bien au joueur
	if(map->cells[turn->cellFrom].owner != idPlayer){
		return 0;
	}

	if(map->cells[turn->cellFrom].nbDices <= 1){
		return 0;
	}

	//Verifier que la cellule de départ et d'arrivée sont adjacentes
	for(int i = 0; i < map->cells[turn->cellFrom].nbNeighbors; i++){
		if(map->cells[turn->cellFrom].neighbors[i]->id == turn->cellTo){
			return 1;
		}
	}
	return 0;
}

/*
Simule le nombre de lancers de dé passé en paramètres et renvoie la somme des lancers
*/
int lancerDe(int nbDe){
	int s = 0;
	for(int i=0 ; i < nbDe ; i++)
	{
		s += aleatoire(1, 6);
	}
	return s;
}

/* Fonction qui jour le tour et modifie la map en conséquent */

void moveTurn(SMap *map, STurn *turn){
	SCell *cellAttacker = &map->cells[turn->cellFrom];
	SCell *cellDefender = &map->cells[turn->cellTo];
	int sommeAttacker = lancerDe(cellAttacker->nbDices);
	int sommeDefender = lancerDe(cellDefender->nbDices);
	//printf("%d vs %d\n", sommeAttacker, sommeDefender);
	if(sommeAttacker > sommeDefender){
		cellDefender->owner = cellAttacker->owner;
		cellDefender->nbDices = cellAttacker->nbDices - 1;
	}
	//printf("nb dés : %d\n", map->cells[turn->cellFrom].nbDices);
	cellAttacker->nbDices = 1;
	//printf("nb dés : %d\n", map->cells[turn->cellFrom].nbDices);

	char str2[1000];
	sprintf(str2, "%d,%d,%d,%d,%d\n",  cellAttacker->owner, turn->cellFrom, turn->cellTo, sommeAttacker, sommeDefender);
	Log(str2);
}

/*
Trouve le plus grand nombre de territoire connexe appartenant au joueur passé en paramètre
*/
int getDiceToDistribute(int idPlayer, SMap *map){

	int marque[60];
	int lenMarque = 0;
	int playerCell[60];
	int nbPlayerCell = 0;
	int max = 0;

	//On génére un tableau contenant les position des cellules dans map->cells
	for(int i = 0 ; i < map->nbCells ; i++)
	{
		if(map->cells[i].owner == idPlayer)
		{
			playerCell[nbPlayerCell] = i;
			nbPlayerCell++;
		}
	}

	for(int i = 0; i < nbPlayerCell ; i++)
	{
		int calcul = 0;
		if(!(inTab(playerCell[i], marque, lenMarque)))
		{
			calcul += explorer(map, idPlayer, marque, &lenMarque, playerCell[i]);
		}
		if(calcul > max)
		{
			max = calcul;
		}
	}
	return max;
}


//Fonction récursive réalisant l'exploration en profondeur pour chercher le total de cellule adjacentes
int explorer(SMap *map, int idPlayer, int marque[], int* lenMarque, int idCell)
{
	int calcul = 1; //Cellule adjacentes plus un
	marque[*lenMarque] = idCell; //Marquage de la cellule pour ne pas la recompter
	(*lenMarque)++; //Incrementation de la valeur du pointeur

	for(int j = 0 ; j < map->cells[idCell].nbNeighbors ; j++)
	{
		//Si un des voisins est a nous et n'est pas deja marqué
		if(map->cells[idCell].neighbors[j]->owner == idPlayer && !(inTab(map->cells[idCell].neighbors[j]->id, marque, *lenMarque)))
		{
			//On l'explore
			calcul += explorer(map, idPlayer, marque, lenMarque, map->cells[idCell].neighbors[j]->id);
		}
	}
	return calcul;
}

int inTab(int id, int tab[], int lenTab)
{
	for(int i = 0 ; i  < lenTab ; i++)
	{
		if(tab[i] == id)
			return 1;
	}
	return 0;
}

/*
Fonction qui répartit les dés a la fin d'un tour d'un joueur
*/
void endTurn(int idPlayer, SMap *map)
{
	int playerCell[60];
	int nbPlayerCell = 0;

	//On génére un tableau contenant les position des cellules dans map->cells
	for(int i = 0 ; i < map->nbCells ; i++){
		if(map->cells[i].owner == idPlayer){
			playerCell[nbPlayerCell] = i;
			nbPlayerCell++;
		}
	}

	int nbDiceDistributed = getDiceToDistribute(idPlayer, map) + map->stack[idPlayer];
	printf("Je distribue %d dés !! \n", nbDiceDistributed);
	int random;
	Log("///\n");
	//On prend un sommet aléatoire qu'il possède et on ajoute un dé
	for(int i = 1 ; i <= nbDiceDistributed ; i++){
		random = aleatoire(0, nbPlayerCell-1);
		if(map->cells[playerCell[random]].nbDices < 8){
			map->cells[playerCell[random]].nbDices++;
			char str[100];
			sprintf(str, "%d\n", map->cells[playerCell[random]].id);
			Log(str);
		}
		else{
			if(allCellsFull(idPlayer, map)){
				map->stack[idPlayer] += nbDiceDistributed - i + 1;
				printf("je stack %d dé\n", map->stack[idPlayer]);
				break;
			}
			else{
				i--;
			}
		}
	}
	Log("///\n");
}

//Vérifie si toutes les cellules du joueurs sont pleines
int allCellsFull(int idPlayer, SMap *map)
{
	for(int i=0 ; i  < map->nbCells ; i++)
	{
		if(map->cells[i].owner == idPlayer && map->cells[i].nbDices < 8)
			return 0;
	}
	return 1;
}


// Verifie les paramètres mis par l'utilisateur au lancement du
// programme. Modifie la valeur du pointeur nbLib passé en parametre pour matcher le nombre de lib
int verifArguments(int argc, char* argv[], int *nbLib){

	if(argc<3 || argc>5){
		rappelSyntaxe("Mauvais nombre d'arguments\n");
		return 1;
	}

	int nbPlayer = (atoi(argv[2]));
	int nbGames = (atoi(argv[1]));

	if(((nbGames<1)||(nbGames>9))||((nbPlayer<2)||(nbPlayer>8))){
		rappelSyntaxe("Mauvais paramètres\n");
		return 1;
	}

	*nbLib = argc - 3;
	return 0;
}

/* Renvoie 1 si le joueur correspondant a l'id passé en parametres a gagné
	0 sinon
*/

int victoire(unsigned int idPlayer, SMap *map){
	for(int i = 0; i < map->nbCells; i++)	{
		if(map->cells[i].owner != idPlayer){
			return 0;
		}
	}
	return 1;
}

/*
	Fonction permettant de renvoyer une copie profonde de la map
*/
SMap* deepCopy(SMap *map){
	SMap* mapCopy = malloc(sizeof(SMap));

	if(mapCopy == NULL)
		exit(-1);

	mapCopy->nbCells = map->nbCells;
	mapCopy->cells = malloc(mapCopy->nbCells * sizeof(SCell));

	if(mapCopy->cells == NULL)
		exit(-1);

	mapCopy->stack = NULL;

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
	Libere proprement la mémoire occupé par la map
*/
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

// Affichage des régles en cas de problème de paramètre au lancement
void rappelSyntaxe(char* affichage){
	printf("%s",affichage);
	printf("Parametre 1 : Nombre de parties souhaitees (max 9)\n");
	printf("Parametre 2 : Nombre de joueurs souhaites (max 8)\n");
	printf("Parametre 3 et + : Fichiers d'IA a utiliser (max 2)\n");
	printf("Exemple : ./AlphaDice 2 6\n");
}
