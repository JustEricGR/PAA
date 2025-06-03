#include <stdio.h>
#include<stdlib.h>

typedef enum {
    STANGA,
    DREAPTA
}Pozitie;

typedef struct nod {
    int cheie;
    struct nod *stanga;
    struct nod *dreapta;
}nod;

void arboreInit(nod *arbore) {
    arbore->stanga = NULL;
    arbore->dreapta = NULL;
}

nod *nou(int cheie) {
    nod *e=(nod*)malloc(sizeof(nod));
    if(e==NULL) {
        printf("Eroare alocare nod\n");
        perror(NULL);
        exit(-1);
    }
    e->cheie = cheie;
    e->stanga = NULL;
    e->dreapta = NULL;
    return e;
}


void append(nod *arbore, int cheie, int parinte, Pozitie poz) {
    if(arbore==NULL) {
        arbore = nou(cheie);
    }
    else {
        if (arbore->cheie==parinte) {
            if (poz==STANGA) {
                arbore->stanga = nou(cheie);
            }
            else if (poz==DREAPTA) {
                arbore->dreapta = nou(cheie);
            }
        }
        else {
            append(arbore->stanga, cheie, parinte, poz);
            append(arbore->dreapta, cheie, parinte, poz);
        }
    }
}

void rsd(nod *arbore) {
    if(arbore==NULL) return;
    printf("%d ",arbore->cheie);
    rsd(arbore->stanga);
    rsd(arbore->dreapta);
}

void eliberare(nod *arbore) {
    if(arbore==NULL) return;
    if(arbore->stanga==NULL && arbore->dreapta==NULL) {
        free(arbore);
    }
    else {
        eliberare(arbore->stanga);
        eliberare(arbore->dreapta);
    }
}

void srd(nod *arbore) {
    if(arbore==NULL) return;
    srd(arbore->stanga);
    printf("%d ",arbore->cheie);
    srd(arbore->dreapta);
}

void sdr(nod *arbore) {
    if(arbore==NULL) return;
    sdr(arbore->stanga);
    sdr(arbore->dreapta);
    printf("%d ",arbore->cheie);
}

int main(void) {
    nod *arbore=nou(1);
    append(arbore, 1, 0, STANGA);
    append(arbore, 2, 1, STANGA);
    append(arbore, 3, 1, DREAPTA);
    append(arbore, 4, 2, STANGA);
    append(arbore, 5, 2, DREAPTA);
    append(arbore, 6, 3, DREAPTA);
    printf("rsd: ");
    rsd(arbore);
    printf("\nsrd: ");
    srd(arbore);
    printf("\nsdr: ");
    sdr(arbore);

    eliberare(arbore);
    return 0;
}
