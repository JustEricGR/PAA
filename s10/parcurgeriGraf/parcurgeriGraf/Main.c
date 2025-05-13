#include<stdio.h>
#include<stdlib.h>

#define IN "matrice.txt"

typedef struct nod {
	int cheie;
	struct nod* urm;
	struct nod* pred;
}nod;

typedef struct {
	nod* prim;
	nod* ultim;
}Coada;

int** citire(int* size, const char* in) {
	FILE* fin = NULL;
	if ((fin = fopen(in, "r")) == NULL) {
		printf("Eroare la deschidere fisier\n");
		perror(NULL);
		exit(-1);
	}

	fscanf(fin, "%d", size);
	int** v = (int**)malloc(*size * sizeof(int*));
	if (v == NULL) {
		printf("Eroare alocare matrice\n");
		perror(NULL);
		exit(-1);
	}

	for (int i = 0; i < *size; i++) {
		v[i] = (int*)malloc(*size * sizeof(int));
		if (v[i] == NULL) {
			printf("Eroare la alocare linie\n");
			perror(NULL);
			exit(-1);
		}
		for (int j = 0; j < *size; j++) {
			if (fscanf(fin, "%d", &v[i][j]) != 1) {
				printf("Eroare la citirea elementului [%d][%d]\n", i, j);
			}
		}
	}

	return v;
}

void afisare(int** v, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", v[i][j]);
		}printf("\n");
	}
}

void eliberare(int** v, int size) {
	for (int i = 0; i < size; i++)
		free(v[i]);
	free(v);
}

void coadaInit(Coada* c) {
	c->prim = c->ultim = NULL;
}

nod* nou(int n) {
	nod* e = (nod*)malloc(sizeof(nod));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	e->urm = e->pred = NULL;
	e->cheie = n;

	return e;
}

void push(Coada* c, int n) {
	if (c->prim == NULL) {
		//coadaInit(c);
		c->prim = c->ultim = nou(n);
	}
	else {
		nod* aux = nou(n);
		c->ultim->urm = aux;
		aux->pred = c->ultim;
		c->ultim = aux;
	}
}

void pop(Coada* c) {
	if (c->ultim == NULL) return;

	nod* deSters = c->ultim;
	c->ultim = c->ultim->pred;

	if (c->ultim)
		c->ultim->urm = NULL;
	else
		c->prim = NULL;

	free(deSters);
}

void adaugare(Coada* q, int elem) {
	nod* aux = nou(elem);
	aux->urm = q->prim;
	q->prim->pred = aux;
	q->prim = aux;
}

void stergereDinCoada(Coada* c, int elem) {
	if (c->ultim->cheie == elem) pop(c);
	else if (c->prim->cheie == elem) {
		nod* aux = c->prim->urm;
		aux->pred = NULL;
		free(c->prim);
		c->prim = aux;
	}
	else {
		nod* p = c->prim;
		for (; p != NULL; p = p->urm) {
			if (p->cheie == elem) {
				p->pred->urm = p->urm;
				p->urm->pred = p->pred;
				p->urm = NULL;
				p->pred = NULL;
				free(p);
				break;
			}
		}
	}
}


void afisareCoada(Coada c) {
	nod* aux = c.prim;
	for (; aux != NULL; aux = aux->urm) {
		printf("%d ", aux->cheie);
	}
}

void eliberareCoada(Coada* c) {
	nod* p = c->prim;
	while (p != NULL) {
		nod* aux = p;
		p = p->urm;
		free(aux);
	}
	c->prim = c->ultim = NULL;
}

int parcurgereDFS(Coada* c, int** v, int start, int size, int *vizitat) {
	vizitat[start] = 1;
	for (int i = 0; i < size; i++) {
		if (!vizitat[i] && v[start][i] == 1) {
			if (parcurgereDFS(c, v, i, size, vizitat)) {
				return 1;
			}
		}
	}

	return 0;
}

int main(void) {
	int size = 0;
	int** v = NULL;
	v = citire(size, IN);
	afisare(v, size);

	//int* vizitat = (int*)calloc(size, sizeof(int));

	eliberare(v, size);
}