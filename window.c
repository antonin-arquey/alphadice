#include "window.h"

// Fonction créant un fenêtre 800x600 et la retourne
SDL_Window* createWindow()
{
	//The window we'll be rendering to
	SDL_Window* window = SDL_CreateWindow( "AlphaDice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT+100, SDL_WINDOW_SHOWN );

	if(window == NULL) //Si il y une erreur lors de la création de la fenêtre
  {
    fprintf(stderr, "Error, could not create the window: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

	return window;
}

//Detruit la fenêtre et le renderer (à utiliser à la fin du programme lorsque l'on quitte le jeu)
void destroyWindow(SDL_Window* window, SDL_Renderer* renderer){
	//Destroy window
	SDL_DestroyRenderer(renderer);

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();
}

// Fonction vérifiant si l'utilisateur a fermé la fenêtre ou pas.
int windowIsNotClosed(){
	SDL_Event event;
	if(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
				return 0;
			}
	}
	return 1;
}
