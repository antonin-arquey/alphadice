#ifndef _ARBRE_H
#define _ARBRE_H

typedef int Data;
typedef struct Noeud Noeud;
typedef struct SArbre SArbre;

SArbre* CreateArbre(int taille);
void DeleteArbre(SArbre *arbre);
void AddElement(Noeud *cell, Data *elem, int nbElement);

Noeud* headOfArbre(SArbre *arbre);
Noeud* getFils(Noeud *cell, int numero);
void creation(SArbre *arbre, int niveau);
/*Noeud* AddElementBegin(SArbre *arbre,Data elem);
Noeud* AddElementEnd(SArbre *arbre,Data elem);
Noeud* AddElementAfter(SArbre *arbre,Noeud *cell,Data elem);
void DeleteCell(SArbre *arbre,Noeud *cell);

Noeud* GetFirstElement(SArbre *arbre);
Noeud* GetLastElement(SArbre *arbre);
Noeud* GetPrevElement(Noeud *cell);
Noeud* GetNextElement(Noeud *cell);*/
Data getData(Noeud *cell);

#endif
