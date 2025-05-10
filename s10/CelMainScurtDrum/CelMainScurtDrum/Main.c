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

void coadaInit(Coada *c) {
	c->prim = c->ultim=NULL;
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
	nod* aux = c->prim;
	for(;aux->urm!=c->ultim;aux=aux->urm) {}
	aux->urm = NULL;
	c->ultim->pred = NULL;
	free(c->ultim);
	c->ultim = aux;
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

int cautare(int** v, int indiceLinie, int size, int *newStartLine) {
	for (int i = 0; i < size; i++) {
		if (v[indiceLinie][i] == 1) {
			*newStartLine = i;
			return v[indiceLinie][i];
		}
	}
	return 0;
}

Coada *parcurgere(Coada *rezultat, int** v, int start, int end, int size) {
	int newStartLine = 0;
	if (!cautare(v, start, size, &newStartLine)) {
		pop(rezultat);
		
	}
	else {

	}

	if (start == end) {
		push(rezultat, start);
	}
}

int main(void) {
	int** v = NULL;
	int size = 0;
	v = citire(&size, IN);
	//afisare(v, size);
	eliberare(v, size);

	int start = 0, end = 0;
	printf("Dati elementul de inceput: ");
	scanf("%d", &start);

	printf("Dati elementul de final: ");
	scanf("%d", &end);

	Coada c;
	coadaInit(&c);
	

	afisareCoada(c);
	eliberareCoada(&c);
}