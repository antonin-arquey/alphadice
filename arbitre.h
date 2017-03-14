#include "interface.h"

// Fonction modifiant le propriétaire d'un territoire (cell)
void chgOwnerCell(SCell* cell, int idNewOwner);

// Verifie les paramètres mis par l'utilisateur au lancement du
// programme.
int verifArguments(int argc, char* argv[]);

// Affichage des régles en cas de problème de paramètre au lancement
void rappelSyntaxe(char* affichage);

int lancerDe(int nbDe);

int endTurn(STurn *turn, SMap *map);
