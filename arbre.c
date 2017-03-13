#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"


struct Noeud{
	Data Value;
	Noeud *Fils;
	int nbFils;
};

struct SArbre{
	Noeud *Head;
};

SArbre* CreateArbre(int taille){
	SArbre *arbre = malloc(sizeof(Noeud));
	Noeud *newCell = malloc(sizeof(Noeud));

	Noeud listeFils[taille];

	newCell->nbFils = taille;
	newCell->Fils = listeFils;
	newCell->Value = 12;

	arbre->Head = newCell;
	return arbre;
}

Noeud* headOfArbre(SArbre *arbre){
	return arbre->Head;
}

Noeud* getFils(Noeud *cell, int numero){
	return (cell->Fils) + numero;
}

void DeleteArbre(SArbre *arbre){
	free(arbre);
}

<<<<<<< HEAD
void AddElement(Noeud *cell, Data *elem, int nbElement){
	Noeud *newCells = malloc(sizeof(Noeud)*nbElement);
=======
void AddElement(SCell *cell, Data *elem, int nbElement){
	int i = 0;
	SCell *newCells = malloc(sizeof(SCell)*nbElement);
>>>>>>> ee5d7ba6ea5a9a318b1350486c9782bb805c80db
	cell->Fils = newCells;
	cell->nbFils = nbElement;

	for(; i < nbElement; i++){
		newCells->Value = *elem;
		newCells++;
		elem++;
	}
}

<<<<<<< HEAD
int sub(Noeud *cell, int niv, int tab[],int taille){
=======
int sub(SCell *cell, int niv, int tab[],int taille){
	int i = 0;
>>>>>>> ee5d7ba6ea5a9a318b1350486c9782bb805c80db
	//printf("%d\n",niv);
	if (niv == 0){
		return 0;
	}
	niv--;
<<<<<<< HEAD
	Noeud *fils;
	for(int i = 0; i < taille; i++){
=======
	SCell *fils;
	for(; i < taille; i++){
>>>>>>> ee5d7ba6ea5a9a318b1350486c9782bb805c80db
		fils = getFils(cell,i);
		AddElement(fils,tab,taille);
		sub(fils,niv,tab,taille);
	}
	return 1;
}

void creation(SArbre *arbre, int niveau){
	int tab[10] = {45,2};
	Noeud *head = headOfArbre(arbre);
	AddElement(head,tab,2);
	sub(head,--niveau,tab,2);
}
/*
Noeud* AddElementEnd(SArbre *arbre,Data elem){
	Noeud *newCell = malloc(sizeof(elem));

	newCell->Value = elem;
	newCell->suivant = NULL;

	if(arbre == NULL){
		arbre->Head = newCell;
		return newCell;
	}
	Noeud *temp = arbre->Head;
	while(temp->suivant != NULL){
		temp = temp->suivant;
	}
	temp->suivant = newCell;
	return newCell;
}

Noeud* AddElementAfter(SArbre *arbre,Noeud *cell,Data elem){
	Noeud *newCell = malloc(sizeof(elem));

	newCell->Value = elem;
	if(arbre->Head == NULL){
		arbre->Head = newCell;
		newCell->suivant = NULL;
		newCell->precedent = NULL;
		return newCell;
	}

	newCell->precedent = cell;
	newCell->suivant = cell->suivant;
	cell->suivant = newCell;

	return newCell;
}

void DeleteCell(SArbre *arbre,Noeud *cell){
	if(arbre->Head == NULL){
		return;
	}
	Noeud *temp = arbre->Head;
	Noeud *last;
	while(temp != cell && temp->suivant != NULL){
		last = temp;
		temp = temp->suivant;
	}
	temp->suivant->precedent = last;
	last->suivant = temp->suivant;
	free(cell);
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

Noeud* GetPrevElement(Noeud *cell){
	return cell->precedent;
}

Noeud* GetNextElement(Noeud *cell){
	return cell->suivant;
}
*/
Data getData(Noeud *cell){
	if(cell != NULL){
		return cell->Value;
	}
	return NULL;
}
