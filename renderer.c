#include "renderer.h"

// Fonction créant le renderer avec un fond noir et des coloris rouge.
SDL_Renderer* createRenderer(SDL_Window* window)
{
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(renderer == NULL)
	{
		fprintf(stderr, "Error, could not create the renderer: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	// Fond Noir
	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	SDL_RenderClear(renderer);

	//Les futurs ajout sur le render seront rouge
	SDL_SetRenderDrawColor(renderer,255,0,0,255);
	return renderer;
}

// Fonction créant un hexagone partant de x,y.
void createHexagone(SDL_Renderer* renderer, int x, int y)
{
	SDL_RenderDrawLine(renderer, x+10, y, x+20, y+5);
	SDL_RenderDrawLine(renderer, x+20, y+5, x+20, y+15);
	SDL_RenderDrawLine(renderer, x+20, y+15, x+10, y+20);
	SDL_RenderDrawLine(renderer, x+10, y+20, x, y+15);
	SDL_RenderDrawLine(renderer, x, y+15, x, y+5);
	SDL_RenderDrawLine(renderer, x, y+5, x+10, y);
}

void createPoint(SDL_Renderer* renderer, int x, int y){
	SDL_RenderDrawPoint(renderer,x,y);
}
