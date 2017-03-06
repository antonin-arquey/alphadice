#include "window.h"
#include "renderer.h"
#include "arbitre.h"

int main(int argc, char* argv[]){
	if(verifArguments(argc, argv)){
		return 1;
	}
	SDL_Window* window = createWindow();
	SDL_Renderer* renderer = createRenderer(window);
	SDL_RenderPresent(renderer);
	createHexagone(renderer, 0, 0);
	createHexagone(renderer, 20, 0);
	createHexagone(renderer, 40, 0);
	createHexagone(renderer, 60, 0);
	SDL_RenderPresent(renderer);
	while(windowIsNotClosed()){
		
	}
	destroyWindow(window, renderer);
	return 0;
}
