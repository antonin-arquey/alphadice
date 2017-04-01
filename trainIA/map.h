#ifndef MAP_H
  #define MAP_H
#include "interface.h"


// Fonction initialisant la carte et l'affichant sur le renderer
SMap* createMap(int nbPlayer, int nb_pays, int tab_owner[], int tab_de[], int mat_map[800][600], int tabPays[][2]);
double getDistance(int x1, int y1, int x2, int y2);

void addVoisin(SMap *map, int t1, int t2);
int isVoisin(SMap *map, int t1, int t2);

#endif
