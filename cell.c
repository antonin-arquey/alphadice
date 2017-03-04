#include "cell.h"

struct Cell{
  int id;        // ID de la cellule
  int owner;     // ID du joueur
  int n_dices;   // nombre de dés
 
  Cell **neighbors; // Tableau de poiteur vers des cellules voisines
  int n_neighbors;  // Nombre de cellules voisines
};