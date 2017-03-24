#include "player.h"
#include "interface.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

Coord waitMouseEvent()
{
  while(1)
  {
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
      if(event.type == SDL_MOUSEBUTTONDOWN)
      {
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

int PlayerTurn(int idPlayer,SMap *map, int mat_map[800][600], STurn *turn, SDL_Texture *diceTextures[], SDL_Renderer* renderer, int tab_pays[][2]){
  Coord c;
  turn->cellFrom = -1;
  turn->cellTo = -1;

  displayMap(renderer,map,mat_map,turn, tab_pays, diceTextures);
	SDL_RenderPresent(renderer);

  do {
    c = waitMouseEvent();
    turn->cellFrom = mat_map[c.x][c.y];
    printf("il y a %d dés.\n", map->cells[turn->cellFrom].nbDices);
    printf("essaye encore %d %d\n", turn->cellFrom, map->cells[turn->cellFrom].owner);
  } while(map->cells[turn->cellFrom].owner != idPlayer);

  displayMap(renderer,map,mat_map,turn, tab_pays, diceTextures);
	SDL_RenderPresent(renderer);

  c = waitMouseEvent();
  turn->cellTo = mat_map[c.x][c.y];

  displayMap(renderer,map,mat_map,turn, tab_pays, diceTextures);
	SDL_RenderPresent(renderer);

  if(map->cells[turn->cellTo].owner == idPlayer){
    printf("passe\n");
    return 0;
  }
  printf("joue\n");
  return 1;
}
