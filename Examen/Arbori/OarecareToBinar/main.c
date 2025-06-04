#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cheie;
    int primFiu;
    int frateDreapta;
}nod;

typedef struct {
    nod *noduri;
    int size;
}Arbore;

typedef struct Binar{
    int cheie;
    struct Binar *stanga;
    struct Binar *dreapta;
} Binar;

typedef enum {
    STANGA,
    DREAPTA
}Pozitie;

void arboreInit(Arbore *arbore, int size) {
    arbore->noduri = (nod *)malloc(size * sizeof(nod));
    arbore->size = size;
}

void append(Arbore *arbore, int cheie, int primFiu, int frateDreapta) {
    arbore->noduri[cheie].cheie = cheie;
    arbore->noduri[cheie].primFiu = primFiu;
    arbore->noduri[cheie].frateDreapta = frateDreapta;
}

void printArbore(Arbore *arbore) {
    printf("Index:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", i);
    }printf("\n");

    printf("Cheie:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", arbore->noduri[i].cheie);
    }printf("\n");

    printf("PrimFiu:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", arbore->noduri[i].primFiu);
    }printf("\n");

    printf("FrateDreapta:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", arbore->noduri[i].frateDreapta);
    }printf("\n");
}

void rsd(Arbore *arbore, int start) {
    printf("%d ", start);
    int copil=arbore->noduri[start].primFiu;
    while (copil != -1) {
        rsd(arbore, copil);
        copil = arbore->noduri[copil].frateDreapta;
    }
}


Binar *nou(int cheie) {
    Binar *arbore = (Binar *)malloc(sizeof(Binar));
    arbore->cheie = cheie;
    arbore->dreapta = arbore->stanga = NULL;
    return arbore;
}


void appendBinar(Binar *arbore, int cheieFiu, int cheieParinte, Pozitie poz) {
    if (arbore == NULL) {
        arbore = nou(cheieFiu);
    }
    else {
        if (arbore->cheie == cheieParinte) {
            if (poz == STANGA) {
                arbore->stanga = nou(cheieFiu);
            }
            else {
                arbore->dreapta = nou(cheieFiu);
            }
        }
        else {
            appendBinar(arbore->stanga, cheieFiu, cheieParinte, poz);
            appendBinar(arbore->dreapta, cheieFiu, cheieParinte, poz);
        }

    }
}

void eliberare(Binar *arbore) {
    if(arbore==NULL) return;
    if(arbore->stanga==NULL && arbore->dreapta==NULL) {
        free(arbore);
    }
    else {
        eliberare(arbore->stanga);
        eliberare(arbore->dreapta);
    }
}

void rsdBinar(Binar *arbore) {
    if(arbore==NULL) return;
    printf("%d ", arbore->cheie);
    rsdBinar(arbore->stanga);
    rsdBinar(arbore->dreapta);
}

void transformare(Arbore *arbore, Binar *arboreBinar, int start) {

    if (start == arbore->size) {
        return;
    }
    if (arbore->noduri[start].primFiu != -1) {
        appendBinar(arboreBinar, arbore->noduri[start].primFiu, arbore->noduri[start].cheie,STANGA);
        transformare(arbore, arboreBinar, arbore->noduri[start].primFiu);
    }
    if (arbore->noduri[start].frateDreapta != -1) {
        appendBinar(arboreBinar, arbore->noduri[start].frateDreapta, arbore->noduri[start].cheie,DREAPTA);
        transformare(arbore, arboreBinar, arbore->noduri[start].frateDreapta);
    }


}


int main(void) {
    Arbore arbore;
    arboreInit(&arbore, 10);
    append(&arbore, 0, 1, -1);
    append(&arbore, 1, 4, 2);
    append(&arbore, 2, 6, 3);
    append(&arbore, 3, 7, -1);
    append(&arbore, 4, -1, 5);
    append(&arbore, 5, -1, -1);
    append(&arbore, 6, -1, -1);
    append(&arbore, 7, -1, 8);
    append(&arbore, 8, -1, 9);
    append(&arbore, 9, -1, -1);

   // printArbore(&arbore);

    printf("\nRsd: ");
    rsd(&arbore, 0);

    Binar *binar=nou(arbore.noduri[0].cheie);
    transformare(&arbore, binar, arbore.noduri[0].cheie);

    printf("\nRsdBinar: ");
    rsdBinar(binar);

    eliberare(binar);
    free(arbore.noduri);
    return 0;
}