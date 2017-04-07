#ifndef PLAYER_H
#define PLAYER_H
#include "interface.h"
#include "window.h"
#include "renderer.h"

//Structure stockant les coordonnées d'un clic
typedef struct{
  int x;
  int y;
} Coord;

//Fonction attendant le clic de l'utilisateur pour enregistrer a position du clic
Coord waitMouseEvent();

//permet au joueur humain de joueur au jeu
int PlayerTurn(int idPlayer,SMap *map, int mat_map[WIN_WIDTH][WIN_HEIGHT], STurn *turn, SDL_Texture *diceTextures[],  SDL_Texture *scoreTextures[], SDL_Renderer* renderer, int tab_pays[][2]);
#endif
