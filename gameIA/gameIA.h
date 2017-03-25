#include "interface.h"
#include "arbre.h"


int turnIA(int idPlayer, const SMap *map, STurn *turn);
void freeMap(SMap *map);
void moveTurnWin(SMap *map, STurn *turn);
void moveTurnFail(SMap *map, STurn *turn);
int getDicesToDistribute(int idPlayer, SMap *map);
int getAmountOfDices(int idPlayer, SMap *map);
double mapEvaluation(int idPlayer, SMap *map);
int bestMove(int idPlayer, SArbre *arbre, STurn *turn);
SMap* deepCopy(const SMap *map);
void endTurn(int idPlayer, SMap *map);
int aleatoire(int a, int b);
int explorer(SMap *map, int idPlayer, int marque[], int *lenMarque, int idCell);
int inTab(int id, int tab[], int lenTab);
