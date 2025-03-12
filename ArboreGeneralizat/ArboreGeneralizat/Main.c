#include<stdio.h>
#include<stdlib.h>
#define CHUNK_COPII 4

typedef struct Arbore {
	int n;
	struct Arbore** copii;
	int nrCopii;
	int crtCapacity;
}Arbore;

Arbore* nou(int n) {
	Arbore* e = (Arbore*)malloc(sizeof(Arbore));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	e->n = n;
	e->copii = NULL;
	e->nrCopii = 0;
	e->crtCapacity = 0;
	return e;
}

Arbore* cautare(Arbore* arbore, int cheie) {
	if (arbore->n == cheie) {
		return arbore;
	}
	else {
		for (int i = 0; i < arbore->nrCopii; i++) {
			Arbore* aux = cautare(arbore->copii[i], cheie);
			if (aux != NULL) return aux;
		}
	}
	return NULL;
}

void append(Arbore** arbore, int cheieCopil, int cheieParinte) {
	if (*arbore == NULL) {
		*arbore = nou(cheieCopil);
	}
	else {
		Arbore* parinte = cautare(*arbore, cheieParinte);
		if (parinte == NULL)return;
		if (parinte->nrCopii >= parinte->crtCapacity) {
			parinte->crtCapacity += CHUNK_COPII;
			parinte->copii = (Arbore**)realloc(parinte->copii, parinte->crtCapacity * sizeof(Arbore*));
		}
		parinte->copii[parinte->nrCopii++] = nou(cheieCopil);
	}
}

void afisare(Arbore* arbore) {
	printf("%d ", arbore->n);
	for (int i = 0; i < arbore->nrCopii; i++) {
		afisare(arbore->copii[i]);
	}

}

void eliberare(Arbore* arbore) {
	for (int i = 0; i < arbore->nrCopii; i++) {
		eliberare(arbore->copii[i]);
	}
	free(arbore->copii);
	free(arbore);
}

int main(void) {
	Arbore* arbore = NULL;
	append(&arbore, 1, 0);
	append(&arbore, 2, 1);
	append(&arbore, 3, 1);
	append(&arbore, 4, 1);
	append(&arbore, 5, 2);
	append(&arbore, 6, 2);
	append(&arbore, 7, 4);

	afisare(arbore);

	eliberare(arbore);
}