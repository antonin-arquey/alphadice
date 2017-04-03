#ifndef ARBITRE_H
  #define ARBITRE_H

#include "interface.h"

/*
Fonction vérifiant un tour rendu
Renvoie 1 si le tour est bon, -1 si il est pas valide
*/
int verify(unsigned int idPlayer, SMap *map, STurn *turn);

//Vérifie si les paramètres sont valident (Renvoi 0 si faux)
int verifyTurn(unsigned int idPlayer, SMap *map, STurn *turn);

//Vérifie si toutes les cellules du joueurs sont pleines
int allCellsFull(int idPlayer, SMap *map);

// Verifie les paramètres mis par l'utilisateur au lancement du programme.
int verifArguments(int argc, char* argv[], int *nbLib);

// Affichage des régles en cas de problème de paramètre au lancement
void rappelSyntaxe(char* affichage);

/* Simule le nombre de lancers de dé passé en paramètres et renvoie la somme des lancers */
int lancerDe(int nbDe);

/* Fonction qui jour le tour et modifie la map en conséquent */
void moveTurn(SMap *map, STurn *turn);

/* Fonction qui répartit les dés a la fin d'un tour d'un joueur */
void endTurn(int idPlayer, SMap *map);

/* Trouve le plus grand nombre de territoire connexe appartenant au joueur passé en paramètre */
int getDiceToDistribute(int idPlayer, SMap *map);

//Vérifie si un id se trouve dans un tableau
int inTab(int id, int tab[], int lenTab);

//Fonction récursive réalisant l'exploration en profondeur pour chercher le total de cellule adjacentes
int explorer(SMap *map, int idPlayer, int marque[], int *lenMarque, int idCell);

/* Renvoie 1 si le joueur correspondant a l'id passé en parametres a gagné 0 sinon */
int victoire(unsigned int idPlayer, SMap *map);

/* Libere proprement la mémoire occupé par la map */
void freeMap(SMap *map);

/* Fonction permettant de renvoyer une copie profonde de la map */
SMap* deepCopy(SMap *map, int nbPlayer);

#endif
