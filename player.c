#include "player.h"
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
