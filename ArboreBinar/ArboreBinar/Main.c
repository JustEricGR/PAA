#include<stdio.h>
#include<stdlib.h>

typedef enum {
	STANGA,
	DREAPTA
}Pozitie;

typedef struct Arbore {
	int cheie;
	struct Arbore* parinte;
	struct Arbore* stanga;
	struct Arbore* dreapta;
}Arbore;

Arbore* nou(int cheie, Arbore *parinte) {
	Arbore* e = (Arbore*)malloc(sizeof(Arbore));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	e->parinte = parinte;
	e->cheie = cheie;
	e->stanga = e->dreapta = NULL;
	return e;
}

Arbore* cautare(Arbore* arbore, int cheie) {
	if (arbore == NULL) {
		return NULL;
	}
	if (arbore->cheie == cheie) {
		return arbore;
	}

	Arbore* gasit = cautare(arbore->stanga, cheie);
	if (gasit != NULL) return gasit;

	return cautare(arbore->dreapta, cheie);
}


void append(Arbore* arbore, int cheieParinte, Pozitie poz, int cheieCopil) {
	if (arbore == NULL) {
		arbore = nou(cheieCopil, arbore);
	}
	else {
		Arbore* aux = cautare(arbore, cheieParinte);
		switch (poz) {
			case STANGA :
				aux->stanga = nou(cheieCopil, aux);
				break;
			case DREAPTA :
				aux->dreapta = nou(cheieCopil, aux);
				break;
		}
	}
}

void afisare(Arbore* arbore) {
	if (arbore == NULL) {
		return;
	}
	else {
		printf("%d ", arbore->cheie);
		afisare(arbore->stanga);
		afisare(arbore->dreapta);
	}
}

void eliberare(Arbore* arbore) {
	if (arbore == NULL) return;
	if (arbore->stanga == arbore->dreapta == NULL) {
		free(arbore);
	}
	else {
		if (arbore->stanga == NULL) eliberare(arbore->dreapta);
		eliberare(arbore->stanga);
	}
}

int main(void) {
	Arbore* arbore = nou(1, NULL);
	append(arbore, 1, STANGA, 5);
	append(arbore, 1, DREAPTA, 7);
	append(arbore, 5, STANGA, 3);
	append(arbore, 5, DREAPTA, 2);
	append(arbore, 7, STANGA, 6);

	afisare(arbore);

	eliberare(arbore);
}