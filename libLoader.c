#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "libLoader.h"
#include "interface.h"

void** loadLib(int nbLib, char *argv[], initG initTab[], playT playTab[], endG endTab[]){
  if(nbLib < 1 || nbLib > 8) {
    fprintf(stderr, "Erreur de chargement des libraries dynamiques : Trop ou pas assez de libraries\n");
    exit(-1);
  }

  void **libs = malloc(nbLib * sizeof(void*));

  for(int k=0 ; k < nbLib ; k++){
    if((libs[k] = dlopen(argv[k+3], RTLD_LAZY)) == NULL){
      fprintf(stderr, "Erreur d'ouverture de la librairie %s\n", argv[k+3]);
    	fprintf(stderr, "%s\n", dlerror());
    	exit(-1);
    }
    printf("JE CHARGE la lib %s DANS lib[%d]\n", argv[k+3], k);
  }

  for(int i = 0 ; i < nbLib ; i++) {
    if((initTab[i] = (initG) dlsym(libs[i], "InitGame")) == NULL) {
      fprintf(stderr, "Erreur de chargement de la fonction InitGame\n");
      fprintf(stderr, "%s\n", dlerror());
      exit(-1);
    }

    if((playTab[i] = (playT) dlsym(libs[i], "PlayTurn")) == NULL)	{
  		fprintf(stderr, "Erreur de chargement de la fonction PlayTurn\n");
  		fprintf(stderr, "%s\n", dlerror());
  		exit(-1);
  	}

    if((endTab[i] = (endG) dlsym(libs[i], "EndGame")) == NULL) {
      fprintf(stderr, "Erreur de chargement de la fonction EndGame\n");
  		fprintf(stderr, "%s\n", dlerror());
  		exit(-1);
    }
  }

  return libs;
}

void freeLib(void **libs, int nbLib)
{
  for(int i=0 ; i < nbLib ; i++)
  {
    dlclose(libs[i]);
  }
  free(libs);
}
