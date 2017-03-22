#ifndef ARBITRE_H
  #define ARBITRE_H

#include "interface.h"


// Verifie les paramètres mis par l'utilisateur au lancement du
// programme.
int verifArguments(int argc, char* argv[], int *nbLib);

// Affichage des régles en cas de problème de paramètre au lancement
void rappelSyntaxe(char* affichage);

int lancerDe(int nbDe);

void moveTurn(SMap *map, STurn *turn);

int verifyTurn(unsigned int idPlayer, SMap *map, STurn *turn);

void endTurn(int idPlayer, SMap *map);

int getDiceToDistribute(int idPlayer, SMap *map);

int recurGetDiceToDistribute(Scell* tabCellOwner, Scell*  tabVoisins);

int victoire(unsigned int idPlayer, SMap *map);

void freeMap(SMap *map);

SMap* deepCopy(SMap *map);

#endif
