#include "window.h"

SDL_Window* createWindow(){	
	//The window we'll be rendering to
	SDL_Window* window = SDL_CreateWindow( "AlphaWars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
	
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