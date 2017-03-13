#include "window.h"

SDL_Window* createWindow()
{
	//The window we'll be rendering to
	SDL_Window* window = SDL_CreateWindow( "AlphaDice", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );

	if(window == NULL) //Si il y une erreur lors de la création de la fenêtre
  {
    fprintf(stderr, "Error, could not create the window: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
	
	return window;
}

void destroyWindow(SDL_Window* window, SDL_Renderer* renderer){
	//Destroy window
	SDL_DestroyRenderer(renderer);

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();
}

int windowIsNotClosed(){
	SDL_Event event;
	if(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
				return 0;
			}
	}
	return 1;
}
