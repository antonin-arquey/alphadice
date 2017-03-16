#include "interface.h"
#pragma once

typedef struct Noeud{
	SMap *map;
  STurn *turn;
	struct Noeud *fils;
	int nbFils;
}Noeud;

typedef struct{
	Noeud *head;
}SArbre;

SArbre *CreateArbre(int taille);
void DeleteArbre(SArbre *arbre);
void AddElement(Noeud *noeud, SMap **map, STurn **turn, int nbElement);

Noeud* getFils(Noeud *noeud, int numero);
void creation(SArbre *arbre, int niveau);



/*Noeud* AddElementBegin(SArbre *arbre,Data elem);
Noeud* AddElementEnd(SArbre *arbre,Data elem);
Noeud* AddElementAfter(SArbre *arbre,Noeud *noeud,Data elem);
void DeleteCell(SArbre *arbre,Noeud *noeud);

Noeud* GetFirstElement(SArbre *arbre);
Noeud* GetLastElement(SArbre *arbre);
Noeud* GetPrevElement(Noeud *noeud);
Noeud* GetNextElement(Noeud *noeud);*/
//Data getData(Noeud *noeud);
