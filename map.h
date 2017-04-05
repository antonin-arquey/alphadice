#ifndef MAP_H
  #define MAP_H
#include "interface.h"
#include "window.h"
#include "renderer.h"


// Fonction initialisant la carte et l'affichant sur le renderer
SMap* createMap(int nbPlayer, SDL_Renderer* renderer, int mat_map[WIN_WIDTH][WIN_HEIGHT], int tabPays[][2]);
int aleatoire(int a, int b);
int plusdeTerritoires(int b, int nbTerritoiresOwne[], int nbPlayer);

// Fonction affichant la carte sur le renderer
// Actuellement en test afin d'afficher juste
// des hexagones sur la taille de la map
void displayMap(SDL_Renderer* renderer, SMap *map, int mat_map[WIN_WIDTH][WIN_HEIGHT], STurn* turn, int tabPays[][2], SDL_Texture *diceTextures[], int idPlayer);
double getDistance(int x1, int y1, int x2, int y2);
int isVoisin(SMap *map, int t1, int t2);
void addVoisin(SMap *map,int tl, int t2);

//Fonction pour load les textures des chiffres et les free
void loadDiceTextures(SDL_Renderer* renderer, SDL_Texture *diceTextures[]);
void loadScoreTextures(SDL_Renderer* renderer, SDL_Texture *scoreTextures[]);
void freeDiceTextures(SDL_Texture *diceTextures[]);
void freeScoreTextures(SDL_Texture *scoreTextures[]);

#endif
