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

//Fonction créant un point sur le renderer.
void createPoint(SDL_Renderer* renderer, int x, int y){
	SDL_RenderDrawPoint(renderer,x,y);
}
