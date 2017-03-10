#pragma once

// Structure définissant l'identification de la stratégie
typedef struct
{
	char name[30];	// Nom de la stratégie
	char members[6][50];	// Noms des personnes participant au projet.
} SPlayerInfo;

// Structure définissant les caractéristiques d'une cellule
typedef struct SCell
{
	int id;	// Id de la cellule
	int owner;	// Id du joueur qui la possède
	int nbDices;	// Nombre de dés

	SCell **neighbors;	// Tableau de poiteur vers des cellules voisines
	int nbNeighbors;	// Nombre de cellules voisines
} SCell;

// Structure définissant la carte globale du jeu
typedef struct
{
  SCell *cells;	// Tableau des cellules
  int nbCells;	// Nombre de cellules
} SMap;

// Structure définissant les paramètres d'un coup joué
typedef struct
{
	unsigned int cellFrom;
	unsigned int cellTo;
} STurn;

// Fonction à appeler au début de chaque partie
// La stratégie doit compléter la structure SPlayerInfo
void InitGame(unsigned int id, unsigned int nbPlayer, SPlayerInfo *info);

// Fonction à appeler à chaque tour sur la stratégie et tant que le retour de fonction est vrai et qu'il n'y a pas d'erreur.
//	* Ne pas oublier pour l'arbitre de dupliquer toute la structure map pour chaque appel !
//	* En cas d'erreur, rétablir la carte dans l'état initial avant le premier tour du joueur.
// valeur de retour : booléen : 0 coups terminés, 1 structure turn complétée avec un nouveau coup à jouer.
int PlayTurn(const SMap *map, STurn *turn);

// Fonction à appeler à la fin de chaque partie
void EndGame(unsigned int idWinner);
