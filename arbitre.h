#include "cell.h"
#include <stdio.h>

void chgOwnerCell(Cell* cell, int idNewOwner);

Cell* declareAttack(Cell* attackingCell, Cell* defendingCell);

int verifArguments(int argc, char* argv[]);

void rappelSyntaxe(char* affichage);
