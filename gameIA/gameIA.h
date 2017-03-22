#include "interface.h"
#include "arbre.h"


int turnIA(int idPlayer, const SMap *map, STurn *turn);
void moveTurnWin(SMap *map, STurn *turn);
void moveTurnFail(SMap *map, STurn *turn);
int getDicesToDistribute(int idPlayer, SMap *map);
int getAmountOfDices(int idPlayer, SMap *map);
int mapEvaluation(int idPlayer, SMap *map);
int bestMove(int idPlayer, SArbre *arbre, STurn *turn);
SMap* deepCopy(const SMap *map);
