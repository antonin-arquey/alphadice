//Using SDL and standard IO
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Renderer* createRenderer(SDL_Window* window);
void applyRenderer(SDL_Renderer* renderer);
void createHexagone(int x, int y);