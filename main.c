#include "window.h"
#include "renderer.h"

int main(int argc, char* args[]){
	SDL_Window* window = createWindow();
	SDL_Renderer* renderer = createRenderer(window);
	while(windowIsNotClosed()){
		applyRenderer(renderer);
	}
	destroyWindow(window, renderer);
	return 0;
}
