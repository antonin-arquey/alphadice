//Using SDL and standard IO
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// Fonction créant le renderer avec un fond noir et des coloris rouge.
SDL_Renderer* createRenderer(SDL_Window* window);

//Fonction créant un point sur le renderer.
void createPoint(SDL_Renderer* renderer, int x, int y);
