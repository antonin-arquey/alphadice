#include "window.h"
#include "renderer.h"
#include "arbitre.h"
#include "map.h"

int main(int argc, char* argv[]){
	int nbPlayer, nbGame;
	if(verifArguments(argc, argv)){
		return 1;
	}
	nbPlayer = *argv[2];
	nbGame = *argv[1];
	SDL_Window* window = createWindow();
	SDL_Renderer* renderer = createRenderer(window);
	SDL_RenderPresent(renderer);
	displayMap(renderer);
	SDL_RenderPresent(renderer);
	while(windowIsNotClosed()){
		
	}
	destroyWindow(window, renderer);
	return 0;
}