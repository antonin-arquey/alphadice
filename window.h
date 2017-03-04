//Using SDL and standard IO
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Window* createWindow();
void destroyWindow(SDL_Window* window, SDL_Renderer* renderer);
int windowIsNotClosed();