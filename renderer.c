#include "renderer.h"

SDL_Renderer* createRenderer(SDL_Window* window){
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer,255,0,0,255);
	return renderer;
}

void createHexagone(SDL_Renderer* renderer, int x, int y){
	SDL_RenderDrawLine(renderer, x+10, y, x+20, y+5);
	SDL_RenderDrawLine(renderer, x+20, y+5, x+20, y+15);
	SDL_RenderDrawLine(renderer, x+20, y+15, x+10, y+20);
	SDL_RenderDrawLine(renderer, x+10, y+20, x, y+15);
	SDL_RenderDrawLine(renderer, x, y+15, x, y+5);
	SDL_RenderDrawLine(renderer, x, y+5, x+10, y);
}