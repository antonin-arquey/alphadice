#include "interface.h"
#include "arbre.h"


void turnIA(int idPlayer, Noeud *head, const SMap *map, int profondeur);
int evalArbre(int idPlayer, Noeud *head, STurn *turn, int profondeur);
void freeMap(SMap *map);
void moveTurnWin(SMap *map, STurn *turn);
void moveTurnFail(SMap *map, STurn *turn);
int getDicesToDistribute(int idPlayer, SMap *map);
int getAmountOfDices(int idPlayer, SMap *map);
double mapEvaluation(int idPlayer, SMap *map);
void bestMove(int idPlayer, Noeud *head);
void bestMove2(int idPlayer, Noeud *head);
SMap* deepCopy(const SMap *map);
void endTurn(int idPlayer, SMap *map);
int aleatoire(int a, int b);
int explorer(SMap *map, int idPlayer, int marque[], int *lenMarque, int idCell);
int inTab(int id, int tab[], int lenTab);
