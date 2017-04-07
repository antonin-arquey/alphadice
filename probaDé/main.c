#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* l'ensemble du code qui suit à parmis d'estimer la probabilité de gagner à x dés vs n dés
   par exemple quelle est la proba en ayant 5 et que l'adversaire en à 3 de le battre
   Ce code n'a pas besoin de run encore mais est toujours là pour illustrer notre demarche 
 */
int aleatoire(int a, int b){
	return rand() % (b-a+1) + a;
}

//fonction qui simule un lancé de dé
int lancerDe(int nbDe){
	int s = 0;
	for(int i=0 ; i < nbDe ; i++){
		s += aleatoire(1, 6);
	}
	return s;
}

int main(int argc, char const *argv[]){
	srand(time(NULL));
	double count = 200000000;
	double res = 0; 
	double compteur = 0;

	clock_t start = clock();

	for(int x = 1; x < 9; x++){//itération entre 1 - 8
		for(int y = 1; y < 9; y++){//itération entre 1 - 8
			compteur = 0;
			for (int i = 0; i < count; ++i){
				if(lancerDe(x) > lancerDe(y)){
					compteur += 1;
				}
			}
			res = compteur/count;
			printf("%d vs %d : %9.0f/%9.0f = %f\n", x, y, compteur, count, res);
		}
	}

	clock_t end = clock();
    double total = (double) (end - start) / CLOCKS_PER_SEC;
    printf("Temps ecoule : %f \n", total);
	return 0;
}