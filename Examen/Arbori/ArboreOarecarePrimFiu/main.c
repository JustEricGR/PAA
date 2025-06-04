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

void srd(Arbore *arbore, int start) {
    int copil=arbore->noduri[start].primFiu;
    int flag=0;
    while (copil != -1) {

        if (!flag) {
            srd(arbore, copil);
            printf("%d ", arbore->noduri[start].cheie);
            flag = 1;
        }
        else {
            srd(arbore, copil);
        }

        copil = arbore->noduri[copil].frateDreapta;

    }
    if (!flag)
        printf("%d ",arbore->noduri[start].cheie);


}

void sdr(Arbore *arbore, int start) {
    int copil=arbore->noduri[start].primFiu;
    while (copil != -1) {
        sdr(arbore, copil);
        copil = arbore->noduri[copil].frateDreapta;
    }
    printf("%d ", arbore->noduri[start].cheie);
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

    printArbore(&arbore);

    printf("\nRsd: ");
    rsd(&arbore, 0);

    printf("\nSrd: ");
    srd(&arbore, 0);

    printf("\nSdr: ");
    sdr(&arbore, 0);

    free(arbore.noduri);
    return 0;
}