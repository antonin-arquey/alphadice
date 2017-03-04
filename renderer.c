#include "renderer.h"

SDL_Renderer* createRenderer(SDL_Window* window){
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
		
	return renderer;
}

void applyRenderer(SDL_Renderer* renderer){
	//Clear screen
	SDL_RenderClear(renderer);
	
	//Show what is draw
	SDL_RenderPresent(renderer);
}

void createHexagone(int x, int y){
	
}