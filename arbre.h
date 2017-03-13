#ifndef _ARBRE_H
#define _ARBRE_H

typedef int Data;
typedef struct Noeud Noeud;
typedef struct SArbre SArbre;

SArbre* CreateArbre(int taille);
void DeleteArbre(SArbre *arbre);
void AddElement(Noeud *noeud, Data *elem, int nbElement);

Noeud* headOfArbre(SArbre *arbre);
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
Data getData(Noeud *noeud);

#endif
