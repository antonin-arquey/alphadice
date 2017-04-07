#include "interface.h"
#pragma once

typedef struct Noeud{
	SMap *map;
	struct ChanceNode *fils;
	struct EndTurnNode *mapAlea;
	int nbFils;//nombre d'attaque possible à partir de la position
	double maxQ[8];//valeur d'évaluation pour l'ensemble des joueur de la partie
	STurn *bestTurn;//meilleur coup à jouer
}Noeud;

typedef struct ChanceNode {//noeud pour simuler l'incertitude de la reussite d'une attauqe
	double probaDroite;//proba que l'action se realise
	STurn *turn;
	Noeud *filsDroit;//cas on l'on reussi l'attaque
	Noeud *filsGauche;//cas on ne reussi pas l'attaque
}ChanceNode;

typedef struct EndTurnNode {//noeud pour simuler la fin d'un tour
	Noeud *filsAlea;
	int nbFils;
} EndTurnNode;

typedef struct{
	Noeud *head;
}SArbre;

