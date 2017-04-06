#include "player.h"
#include "interface.h"
#include "map.h"
#include "arbitre.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

//Fonction attendant le clic de l'utilisateur pour enregistrer a position du clic
Coord waitMouseEvent(){
  while(1){
    SDL_Event event;
    if(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
        exit(0);
      }
      if(event.type == SDL_MOUSEBUTTONDOWN){
        Coord c;
        int x;
        int y;
        SDL_GetMouseState( &x, &y );
        c.x = x;
        c.y = y;
        return c;
      }
    }
  }
}

//
int PlayerTurn(int idPlayer,SMap *map, int mat_map[WIN_WIDTH][WIN_HEIGHT], STurn *turn, SDL_Texture *diceTextures[],  SDL_Texture *scoreTextures[], SDL_Renderer* renderer, int tab_pays[][2]){
  Coord c;
  turn->cellFrom = -1;
  turn->cellTo = -1;

  displayMap(renderer,map,mat_map,turn, tab_pays, diceTextures, scoreTextures, idPlayer);
	SDL_RenderPresent(renderer);

  do {
    c = waitMouseEvent();
    if(c.x <= 315+170 && c.x >= 315 && c.y <= 629+59 && c.y >= 629){
      return 0;
    }
    if(c.y <= WIN_HEIGHT){
      turn->cellFrom = mat_map[c.x][c.y];
    }
  } while(turn->cellFrom == -1 || map->cells[turn->cellFrom].owner != idPlayer);

  displayMap(renderer,map,mat_map,turn, tab_pays, diceTextures, scoreTextures, idPlayer);
  SDL_RenderPresent(renderer);

  do{
    c = waitMouseEvent();
    //Si le joueur clique sur le bouton
    if(c.x <= 315+170 && c.x >= 315 && c.y <= 629+59 && c.y >= 629){
      return 0;
    }
    if(c.y <= WIN_HEIGHT){
      turn->cellTo = mat_map[c.x][c.y];
      if(turn->cellTo != turn->cellFrom && map->cells[turn->cellTo].owner == idPlayer){
        turn->cellFrom = turn->cellTo;
        turn->cellTo = -1;
        displayMap(renderer,map,mat_map,turn, tab_pays, diceTextures, scoreTextures, idPlayer);
      	SDL_RenderPresent(renderer);
      }
    }


  } while(!verifyTurn(idPlayer, map, turn) && !(turn->cellTo == turn->cellFrom));


  displayMap(renderer,map,mat_map,turn, tab_pays, diceTextures, scoreTextures, idPlayer);
	SDL_RenderPresent(renderer);

  if(map->cells[turn->cellTo].owner == idPlayer)
    return 0;
  return 1;
}
