#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

/*
SArbre* createArbre(SMap *map){
	SArbre *arbre = malloc(sizeof(SArbre));
	Noeud *newNoeud = malloc(sizeof(Noeud));

	Noeud listeFils[20];

	newNoeud->nbFils = 0;
	newNoeud->fils = NULL;
	newNoeud->map = map;
	newNoeud->turn = NULL;
	newNoeud->proba = 0;

	arbre->head = newNoeud;
	return arbre;
}

Noeud* getFils(Noeud *noeud, int numero){
	return (noeud->fils) + numero;
}

void deleteArbre(SArbre *arbre){
	free(arbre);
}

void addElement(Noeud *noeud, SMap **map, STurn **turn, double tabProba[], int nbElement){
	Noeud *newNoeuds = malloc(sizeof(Noeud)*nbElement);
	noeud->fils = newNoeuds;
	noeud->nbFils = nbElement;

	for(int i = 0; i < nbElement; i++){
		newNoeuds[i].map = map[i];
		newNoeuds[i].turn = turn[i];
		newNoeuds[i].proba = tabProba[i];
	}
}
*/
/*int sub(Noeud *noeud, int niv, SMap **map, int taille){
	//printf("%d\n",niv);
	if (niv == 0){
		return 0;
	}
	niv--;
	Noeud *fils;
	for(int i = 0; i < taille; i++){
		fils = getFils(noeud,i);
		AddElement(fils,map,taille);
		sub(fils,niv,map,taille);
	}
	return 1;
}

void creation(SArbre *arbre, int niveau){
	SMap **map = malloc(sizeof(SMap) * 2);
	Noeud *head = arbre->head;
	AddElement(head,map,2);
	sub(head,--niveau,map,2);
}*/
/*
Noeud* AddElementEnd(SArbre *arbre,Data elem){
	Noeud *newNoeud = malloc(sizeof(elem));

	newNoeud->Value = elem;
	newNoeud->suivant = NULL;

	if(arbre == NULL){
		arbre->Head = newNoeud;
		return newNoeud;
	}
	Noeud *temp = arbre->Head;
	while(temp->suivant != NULL){
		temp = temp->suivant;
	}
	temp->suivant = newNoeud;
	return newNoeud;
}

Noeud* AddElementAfter(SArbre *arbre,Noeud *noeud,Data elem){
	Noeud *newNoeud = malloc(sizeof(elem));

	newNoeud->Value = elem;
	if(arbre->Head == NULL){
		arbre->Head = newNoeud;
		newNoeud->suivant = NULL;
		newNoeud->precedent = NULL;
		return newNoeud;
	}

	newNoeud->precedent = noeud;
	newNoeud->suivant = noeud->suivant;
	noeud->suivant = newNoeud;

	return newNoeud;
}

void DeleteNoeud(SArbre *arbre,Noeud *noeud){
	if(arbre->Head == NULL){
		return;
	}
	Noeud *temp = arbre->Head;
	Noeud *last;
	while(temp != noeud && temp->suivant != NULL){
		last = temp;
		temp = temp->suivant;
	}
	temp->suivant->precedent = last;
	last->suivant = temp->suivant;
	free(noeud);
}

Noeud* GetFirstElement(SArbre *arbre){
	if(arbre == NULL){
		return NULL;
	}
	return arbre->Head;
}

Noeud* GetLastElement(SArbre *arbre){
	if(arbre == NULL){
		return NULL;
	}
	return arbre->Head->precedent;
}

Noeud* GetPrevElement(Noeud *noeud){
	return noeud->precedent;
}

Noeud* GetNextElement(Noeud *noeud){
	return noeud->suivant;
}
*/
