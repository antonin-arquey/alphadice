#ifndef PLAYER_H
   #define PLAYER_H
   #include "interface.h"
   #include "renderer.h"

   typedef struct{
     int x;
     int y;
   } Coord;

   Coord waitMouseEvent();
   int PlayerTurn(int idPlayer,SMap *map, int mat_map[800][600], STurn *turn, SDL_Texture *diceTextures[], SDL_Renderer* renderer, int tab_pays[][2]);
#endif
