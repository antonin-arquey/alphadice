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

// Structure definissant la carte globale du jeu
typedef struct
{
  SCell *cells;	// Tableau des cellules
  int nbCells;	// Nombre de cellules
  unsigned int *stack;	// Nombre de des en reserve par joueur -tableau dim nb joueur)
} SMap;

// Structure definissant les parametres d'un coup joue
typedef struct
{
	unsigned int cellFrom;
	unsigned int cellTo;
} STurn;

// Fonction a appeler au debut de chaque partie
// La strategie doit completer la structure SPlayerInfo
void InitGame(unsigned int id, unsigned int nbPlayer, SPlayerInfo *info);

// Fonction a appeler a chaque tour sur la strategie et tant que le retour de fonction est vrai et qu'il n'y a pas d'erreur.
//	* Ne pas oublier pour l'arbitre de dupliquer toute la structure map pour chaque appel !
//	* En cas d'erreur, retablir la carte dans l'etat initial avant le premier tour du joueur.
// valeur de retour : booleen : 0 coups termines, 1 structure turn completee avec un nouveau coup a jouer.
int PlayTurn(int idPlayer, const SMap *map, STurn *turn);

// Fonction a appeler a la fin de chaque partie
void EndGame(unsigned int idWinner);
