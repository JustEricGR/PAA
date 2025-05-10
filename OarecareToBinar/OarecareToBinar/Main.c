#include<stdio.h>
#include<stdlib.h>
#include"Arbore.h"

typedef enum {
	STANGA,
	DREAPTA
}Pozitie;

typedef struct Arbore {
	int cheie;
	struct Arbore* stanga;
	struct Arbore* dreapta;
}Arbore;

Arbore* nou(int cheie) {
	Arbore* e = (Arbore*)malloc(sizeof(Arbore));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}

	e->cheie = cheie;
	e->stanga = e->dreapta = NULL;

	return e;
}

Arbore* cautare(Arbore* a, int cheie) {
	if (a == NULL)return NULL;
	if (a->cheie == cheie) {
		return a;
	}
	else {
		Arbore *stanga = cautare(a->stanga, cheie);
		if (stanga != NULL) return stanga;

		return cautare(a->dreapta, cheie);
	}
	return NULL;
}

void inserare(Arbore* a, int cheieFiu, int cheieParinte, Pozitie poz) {
	if (a == NULL) {
		a = nou(cheieFiu);
		return;
	}
	Arbore* parinte = cautare(a, cheieParinte);
	if (parinte != NULL) {
		switch (poz) {
			case STANGA :
				parinte->stanga = nou(cheieFiu);
				break;
			case DREAPTA :
				parinte->dreapta = nou(cheieFiu);
		}
	}
}

void afisarePreordine(Arbore* a) {
	if (a == NULL)return;
	printf("%d ", a->cheie);

	afisarePreordine(a->stanga);
	afisarePreordine(a->dreapta);
}

void afisareInordine(Arbore* a) {
	if (a == NULL)return;
	afisareInordine(a->stanga);
	printf("%d ", a->cheie);
	afisareInordine(a->dreapta);
}

void afisarePostordine(Arbore* a) {
	if (a == NULL)return;
	afisarePostordine(a->stanga);
	afisarePostordine(a->dreapta);
	printf("%d ", a->cheie);
}

void eliberare(Arbore* a) {
	if (a == NULL) return;
	eliberare(a->stanga);
	eliberare(a->dreapta);
	free(a);
}

Arbore* transformare(TTree tree, TNodeRef root) {
	if (root == 0)return NULL;
	Arbore* a = nou(tree.nodes[root].key);

	TNodeRef tmp = tree.nodes[root].primFiu;

	if (tmp) {
		a->stanga = transformare(tree, root);
	}

	TNodeRef fd = tree.nodes[root].frateDreapta;
	if (fd) {
		a->dreapta = transformare(tree, fd);
	}

	

	return a;
}


int main(void) {
	/*Arbore* a = NULL;

	a = nou(1);
	
	inserare(a, 5, 1, STANGA);
	inserare(a, 7, 1, DREAPTA);
	inserare(a, 3, 5, STANGA);
	inserare(a, 2, 5, DREAPTA);
	inserare(a, 6, 7, STANGA);

	printf("\nPreordine:\n");
	afisarePreordine(a);

	printf("\nInordine:\n");
	afisareInordine(a);

	printf("\nPostordine:\n");
	afisarePostordine(a);

	eliberare(a);*/

	TTree a = { 0,0,0 };
	a = InitTree(a);

	a=InsertNode(a, 2, 0, 1);
	a=InsertNode(a, 6, 3, 5);
	a = InsertNode(a, 0, 2, 6);
	a=InsertNode(a, 0, 0, 2);
	a=InsertNode(a, 0, 7, 3);
	
	a=InsertNode(a, 4, 0, 7);
	a=InsertNode(a, 0, 0, 4);

	Arbore* arbore = NULL;

	arbore = transformare(a, getRoot(a));

	printArray(a);
	afisarePreordine(arbore);
}