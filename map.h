#ifndef MAP_H
  #define MAP_H
#include "interface.h"
#include "window.h"
#include "renderer.h"


// Fonction initialisant la carte et l'affichant sur le renderer
SMap* createMap(int nbPlayer, SDL_Renderer* renderer, int mat_map[WIN_WIDTH][WIN_HEIGHT], int tabPays[][2]);

//Fonction générant un nombre aléatoire entre a et b.
int aleatoire(int a, int b);

//Fonction retournant 1 si le player b a plus de territoire qu'un autre joueur. 0 sinon.
int plusdeTerritoires(int b, int nbTerritoiresOwne[], int nbPlayer);

// Fonction affichant la carte sur le renderer
void displayMap(SDL_Renderer* renderer, SMap *map, int mat_map[WIN_WIDTH][WIN_HEIGHT], STurn* turn, int tabPays[][2], SDL_Texture *diceTextures[], SDL_Texture *scoreTextures[], int idPlayer);

//Fonction retournant la distance entre le point(x1,y1) et (x2,y2).
double getDistance(int x1, int y1, int x2, int y2);

//Fonction qui regarde si les cellules c1 et c2 sont déjà voisines. Renvoi 1 si oui, 0 sinon.
int isVoisin(SMap *map, int t1, int t2);

//
void addVoisin(SMap *map,int tl, int t2);

//Fonction pour load les textures des dés et les free
void loadDiceTextures(SDL_Renderer* renderer, SDL_Texture *diceTextures[]);

//Fonction pour load les textures des scores et les free
void loadScoreTextures(SDL_Renderer* renderer, SDL_Texture *scoreTextures[]);

//Libère la mémoire du tableau de texture des dés
void freeDiceTextures(SDL_Texture *diceTextures[]);

//Libère la mémoire du tableau de texture des scores
void freeScoreTextures(SDL_Texture *scoreTextures[]);

//
void setScore(int sd, int sc);


#endif
