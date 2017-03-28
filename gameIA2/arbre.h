#include "interface.h"
#pragma once

typedef struct Noeud{
	SMap *map;
	struct ChanceNode *fils;
	struct EndTurnNode *mapAlea;
	int nbFils;
	double maxQ;
	STurn *bestTurn;
}Noeud;

typedef struct ChanceNode {
	double probaDroite;
	//int probaGauche; 1 - probaDroite
	STurn *turn;
	Noeud *filsDroit;
	Noeud *filsGauche;
}ChanceNode;

typedef struct EndTurnNode {
	Noeud *filsAlea;
	int nbFils;
} EndTurnNode;

typedef struct{
	Noeud *head;
}SArbre;

SArbre *createArbre(SMap *map);
void deleteArbre(SArbre *arbre);
void addElement(Noeud *noeud, SMap **map, STurn **turn, double proba[], int nbElement);

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
