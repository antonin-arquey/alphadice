//Using SDL and standard IO
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// Fonction créant un fenêtre 800x600 et la retourne
SDL_Window* createWindow();

//Detruit la fenêtre et le renderer (à utiliser à la fin du programme lorsque l'on quitte le jeu)
void destroyWindow(SDL_Window* window, SDL_Renderer* renderer);

// Fonction vérifiant si l'utilisateur a fermé la fenêtre ou pas.
int windowIsNotClosed();