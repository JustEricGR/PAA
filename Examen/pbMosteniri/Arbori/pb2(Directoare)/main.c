#include <stdio.h>
#include <stdlib.h>

typedef struct nod {
    int cheie;
    int primFiu;
    int frateDreapta;
}nod;

typedef struct {
    nod *noduri;
    int size;
}Arbore;

void arboreInit(Arbore *arbore, int size) {
    arbore->noduri = (nod*)malloc(size * sizeof(nod));
    arbore->size = size;
}

void append(Arbore *arbore, int cheie, int primFiu, int frateDreapta) {
    arbore->noduri[cheie].cheie = cheie;
    arbore->noduri[cheie].primFiu = primFiu;
    arbore->noduri[cheie].frateDreapta = frateDreapta;
}

void printArbore(Arbore *arbore) {
    printf("Index:\n ");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", i);
    }

    printf("\n");

    printf("Cheie:\n ");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", arbore->noduri[i].cheie);
    }printf("\n");

    printf("PrimFiu:\n ");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", arbore->noduri[i].primFiu);
    }printf("\n");

    printf("FrateDreapta:\n ");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", arbore->noduri[i].frateDreapta);
    }printf("\n");
}

void parcurgereRsd(Arbore *arbore, int start, int *totRamura, int *max) {
    printf("%d ", arbore->noduri[start].cheie);
    int copil=arbore->noduri[start].primFiu;
    while (copil != -1) {
        *totRamura += 1;
        parcurgereRsd(arbore, copil, totRamura, max);
        copil=arbore->noduri[copil].frateDreapta;
    }
    if (arbore->noduri[start].primFiu == -1 && arbore->noduri[start].frateDreapta == -1 && *totRamura > *max) {
        *max=*totRamura;
    }
    *totRamura=0;
}

int main(void) {
    Arbore arbore;
    int max=0, totRamura=0;
    arboreInit(&arbore, 11);
    append(&arbore, 0, 1, -1);
    append(&arbore, 1, 4, 2);
    append(&arbore, 2, 6, 3);
    append(&arbore, 3, 7, -1);
    append(&arbore, 4, -1, 5);
    append(&arbore, 5, -1, -1);
    append(&arbore, 6, 10, -1);
    append(&arbore, 7, -1, 8);
    append(&arbore, 8, -1, 9);
    append(&arbore, 9, -1, -1);
    append(&arbore, 10, -1, -1);

    printArbore(&arbore);

    printf("\nRsd: ");
    parcurgereRsd(&arbore, arbore.noduri[0].cheie, &totRamura, &max);

    printf("\nCel mai lung drum: %d\n",max);

    free(arbore.noduri);
    return 0;
}