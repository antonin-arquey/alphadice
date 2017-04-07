#include "interface.h"
#include "arbre.h"


void turnIA(int id, int idPlayer, Noeud *head, const SMap *map, STurn *turn, int profondeur);//fonction qui fait tourner l'ia

SMap* deepCopy(const SMap *map, int nbPlayer);//copie profonde de la map
void freeMap(SMap *map);//free les éléments de la map
int getNbPlayer();//obtient le nombre de joeur dans la partie

void moveTurnWin(SMap *map, STurn *turn);//simule le victoire d'une attaque
void moveTurnFail(SMap *map, STurn *turn);//simule la défaite d'une attaque

int getDicesToDistribute(int idPlayer, SMap *map);//pour obtenir le nombre de dés à distribuer
int getAmountOfDices(int idPlayer, SMap *map);//pour avoir la quantité de dés possédés par le joueur
int getnbTerritoires(int idPlayer, SMap *map);//pour avoir le nombre de territoires du joueur

double mapEvaluation(int idPlayer, SMap *map);//pour évaluer la map
void bestMove(int idPlayer, Noeud *head);//pour avoir la meilleure attaque pas une feuille de l'arbre
void bestMove2(int idPlayer, Noeud *head);//poura voir la meilleure attque dans le reste de l'arbre
double inactionTurn(int idPlayer, Noeud *head);//pour simuler une inaction de l'ia au niveau d'une feuille
double inactionTurn2(int idPlayer, Noeud *head);//pour simuler une inaction de l'ia dans l'arbre

void endTurn(int idPlayer, SMap *map);//pour la fin du tour
int aleatoire(int a, int b);//pour avoir un nombre aléatoire
int explorer(SMap *map, int idPlayer, int marque[], int *lenMarque, int idCell);
int inTab(int id, int tab[], int lenTab);
int allCellsFull(int idPlayer, SMap *map);
