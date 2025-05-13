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
	if (c->ultim == NULL) return;

	nod* deSters = c->ultim;
	c->ultim = c->ultim->pred;

	if (c->ultim)
		c->ultim->urm = NULL;
	else
		c->prim = NULL;

	free(deSters);
}

void adaugare(Coada* q, int pozitie, int elem) {
	nod* aux = nou(elem);
	nod* pos = q->prim;
	if (pos->cheie == pozitie) {
		aux->urm = pos;
		pos->pred = aux;
		pos = aux;
		q->prim = aux;
	}
	else {
		for (; pos != NULL; pos = pos->urm) {
			if (pos->cheie == pozitie) {
				aux->pred = pos->pred;
				aux->urm = pos;
				pos->pred->urm = aux;
				pos->pred = aux;
				
				break;
			}
		}
	}
	
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

//parcurgere adancime
int parcurgereAdancime(Coada* c, int** v, int start, int size, int* vizitat) {
	vizitat[start] = 1;
	push(c, start);

	for (int i = 0; i < size; i++) {
		if (v[start][i] == 1 && !vizitat[i]) {
			if (parcurgereAdancime(c, v, i, size, vizitat)) {
				return 1;
			}
		}
	}
	return 0;
}


void parcurgereLatime(Coada* c, int** v, int start, int size) {
	int* vizitat = (int*)calloc(size, sizeof(int));
	

	Coada q;
	coadaInit(&q);
	push(&q, start);
	vizitat[start] = 1;

	while (q.prim != NULL) {
		if (q.prim->urm == NULL) {
			push(c, q.prim->cheie);
			int nodAux = q.prim->cheie;
			pop(&q);
			for (int i = 0; i < size; i++) {
				if (!vizitat[i] && v[nodAux][i] == 1) {
					vizitat[i] = 1;
					push(&q, i);

				}
			}
		}
		else {
			nod* aux = q.prim;
			while (aux != NULL) {
				push(c, aux->cheie);
				nod* next = aux->urm;
				int nodAux = aux->cheie;
				stergereDinCoada(&q, nodAux);
				aux = next;
				for (int i = 0; i < size; i++) {
					if (v[nodAux][i] == 1 && !vizitat[i]) {
						vizitat[i] = 1;
						if (aux != NULL)
							adaugare(&q, aux->cheie, i);
						else
							push(&q, i);
					}
				}
				
			}
		}
	}

	free(vizitat);
}



int main(void) {
	int** v = NULL;
	int size = 0;
	v = citire(&size, IN);
	//afisare(v, size);
	int* vizitat = (int*)calloc(size, sizeof(int));

	int start = 0, end = 0;
	printf("Dati elementul de inceput: ");
	scanf("%d", &start);

	/*printf("Dati elementul de final: ");
	scanf("%d", &end);*/

	Coada c;
	coadaInit(&c);
	/*if (parcurgereAdancime(&c, v, start, size, vizitat)) {
		afisareCoada(c);
	}*/

	parcurgereLatime(&c, v, start, size);
	

	//bfs(&c, v, start, end, size);
	
	afisareCoada(c);

	//afisareCoada(c);
	eliberareCoada(&c);
	eliberare(v, size);
}