#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "libLoader.h"
#include "interface.h"

void** loadLib(int nbLib, char *lib1, char *lib2, initG initTab[], playT playTab[])
{
  if(nbLib < 1 || nbLib > 2)
  {
    fprintf(stderr, "Erreur de chargement des libraries dynamiques : Trop ou pas assez de libraries\n");
    exit(-1);
  }

  void **libs = malloc(nbLib * sizeof(void*));

  if(lib1 == NULL || (libs[0] = dlopen(lib1, RTLD_LAZY))==NULL)
  {
  	fprintf(stderr, "Erreur d'ouverture de la librairie %s\n", lib1);
  	fprintf(stderr, "%s\n", dlerror());
  	exit(-1);
  }

  if(nbLib > 1)
  {
    if(lib1 == NULL || (libs[1] = dlopen(lib2, RTLD_LAZY))==NULL)
    {
    	fprintf(stderr, "Erreur d'ouverture de la librairie %s\n", lib2);
    	fprintf(stderr, "%s\n", dlerror());
    	exit(-1);
    }
  }

  for(int i = 0 ; i < nbLib ; i++)
  {
    if((initTab[i] = (initG) dlsym(libs[i], "InitGame")) == NULL)
    {
      fprintf(stderr, "Erreur de chargement de la fonction InitGame\n");
      fprintf(stderr, "%s\n", dlerror());
      exit(-1);
    }

    if((playTab[i] = (playT) dlsym(libs[i], "PlayTurn")) == NULL)
  	{
  		fprintf(stderr, "Erreur de chargement de la fonction PlayTurn\n");
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
