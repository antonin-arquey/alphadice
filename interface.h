#pragma once

// Structure d�finissant l'identification de la strat�gie
typedef struct
{
	char name[30];	// Nom de la strat�gie
	char members[6][50];	// Noms des personnes participant au projet.
} SPlayerInfo;

// Structure d�finissant les caract�ristiques d'une cellule
typedef struct SCell
{
	int id;	// Id de la cellule
	int owner;	// Id du joueur qui la poss�de
	int nbDices;	// Nombre de d�s

	struct SCell **neighbors;	// Tableau de poiteur vers des cellules voisines
	int nbNeighbors;	// Nombre de cellules voisines
} SCell;

// Structure d�finissant la carte globale du jeu
typedef struct
{
  SCell *cells;	// Tableau des cellules
  int nbCells;	// Nombre de cellules
  unsigned int *stack;	// Nombre de d�s en r�serve par joueur -tableau dim nb joueur)
} SMap;

// Structure d�finissant les param�tres d'un coup jou�
typedef struct
{
	unsigned int cellFrom;
	unsigned int cellTo;
} STurn;

// Fonction � appeler au d�but de chaque partie
// La strat�gie doit compl�ter la structure SPlayerInfo
void InitGame(unsigned int id, unsigned int nbPlayer, SPlayerInfo *info);

// Fonction � appeler � chaque tour sur la strat�gie et tant que le retour de fonction est vrai et qu'il n'y a pas d'erreur.
//	* Ne pas oublier pour l'arbitre de dupliquer toute la structure map pour chaque appel !
//	* En cas d'erreur, r�tablir la carte dans l'�tat initial avant le premier tour du joueur.
// valeur de retour : bool�en : 0 coups termin�s, 1 structure turn compl�t�e avec un nouveau coup � jouer.
int PlayTurn(int idPlayer, const SMap *map, STurn *turn);

// Fonction � appeler � la fin de chaque partie
void EndGame(unsigned int idWinner);
