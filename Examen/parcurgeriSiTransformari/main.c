#include <stdio.h>
#include <stdlib.h>

typedef enum {
    STANGA,
    DREAPTA
}Pozitie;

typedef struct nodType1 {
    int cheie;
    int parinte;
}nodType1;

typedef struct {
    nodType1 *elemente;
    int size;
}arboreType1;

typedef struct nodType2 {
    int cheie;
    int primFiu;
    int frateDreapta;
}nodType2;

typedef struct {
    nodType2 *elemente;
    int size;
}arboreType2;

typedef struct Binar {
    int cheie;
    struct Binar *stanga;
    struct Binar *dreapta;
}Binar;

void arbore1Init(arboreType1 *arbore, int size) {
    arbore->elemente = (nodType1 *)malloc(size * sizeof(nodType1));
    arbore->size = size;
}

void arbore1Append(arboreType1 *arbore, int cheie, int parinte, int index) {
    arbore->elemente[index].cheie = cheie;
    arbore->elemente[index].parinte = parinte;

}

void printArray(arboreType1 *arbore) {
    printf("Index:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", i);
    }

    printf("\nCheie:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", arbore->elemente[i].cheie);
    }

    printf("\nParinte:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", arbore->elemente[i].parinte);
    }
}

void arbore1Rsd(arboreType1 *arbore, int start) {
    printf("%d ",start);

    for (int i = 0; i < arbore->size; i++) {
        if (arbore->elemente[start].cheie == arbore->elemente[i].parinte) {
            arbore1Rsd(arbore,i);
        }
    }
}


void arbore1Srd(arboreType1 *arbore, int start) {

    int flag=0;
    for (int i = 0; i < arbore->size; i++) {
        if (arbore->elemente[start].cheie == arbore->elemente[i].parinte) {
            if (!flag) {

                arbore1Srd(arbore,i);
                printf("%d ",start);
                flag=1;
            }
            else {
                arbore1Srd(arbore,i);
            }
        }
    }

    if (!flag) {
        printf("%d ",start);
    }
}

void arbore1Sdr(arboreType1 *arbore, int start) {
    for (int i = 0; i < arbore->size; i++) {
        if (arbore->elemente[i].parinte == arbore->elemente[start].cheie) {
            arbore1Sdr(arbore,i);;
        }
    }
    printf("%d ",start);
}

void arbore2Init(arboreType2 *arbore, int size) {
    arbore->elemente = (nodType2 *)malloc(size * sizeof(nodType2));
    arbore->size = size;
}

void arbore2Append(arboreType2 *arbore, int cheie, int primFiu, int frateDreapta, int index) {
    arbore->elemente[index].cheie = cheie;
    arbore->elemente[index].primFiu = primFiu;
    arbore->elemente[index].frateDreapta = frateDreapta;
}


void printArbore(arboreType2 *arbore) {
    printf("Index:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", i);
    }printf("\n");

    printf("Cheie:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", arbore->elemente[i].cheie);
    }printf("\n");

    printf("PrimFiu:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", arbore->elemente[i].primFiu);
    }printf("\n");

    printf("FrateDreapta:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", arbore->elemente[i].frateDreapta);
    }
}


void arbore2Rsd(arboreType2 *arbore, int start) {
    printf("%d ",start);
    int copil=arbore->elemente[start].primFiu;
    while (copil!=-1) {
        arbore2Rsd(arbore,copil);
        copil=arbore->elemente[copil].frateDreapta;
    }
}

void arbore2Srd(arboreType2 *arbore, int start) {
    int copil=arbore->elemente[start].primFiu;
    int flag=0;
    while (copil!=-1) {
        if (!flag) {
            arbore2Srd(arbore,copil);
            printf("%d ",start);
            flag=1;
        }
        else {
            arbore2Srd(arbore,copil);
        }
        copil=arbore->elemente[copil].frateDreapta;
    }

    if (!flag) {
        printf("%d ",start);
    }
}

void arbore2Sdr(arboreType2 *arbore, int start) {
    int copil=arbore->elemente[start].primFiu;
    while (copil!=-1) {
        arbore2Sdr(arbore,copil);
        copil=arbore->elemente[copil].frateDreapta;
    }
    printf("%d ",start);
}


void transformare1(arboreType1 *arbore1, arboreType2 *arbore2) {
    for (int i = 0; i < arbore2->size; i++) {
        arbore2->elemente[i].cheie = arbore1->elemente[i].cheie;
        arbore2->elemente[i].primFiu=-1;
        arbore2->elemente[i].frateDreapta=-1;
    }

    for (int i = 0; i < arbore1->size; i++) {
        for (int j = i+1; j < arbore1->size; j++) {
            if (arbore1->elemente[i].cheie == arbore1->elemente[j].parinte) {
                arbore2->elemente[i].primFiu=arbore1->elemente[j].cheie;
                nodType1 original=arbore1->elemente[j];
                for (int k = j+1; k < arbore1->size; k++) {
                    if (original.parinte==arbore1->elemente[k].parinte) {
                        arbore2->elemente[original.cheie].frateDreapta=arbore1->elemente[k].cheie;
                        original.cheie=arbore1->elemente[k].cheie;
                    }
                }

                break;
            }
        }
    }
}

Binar *nou(int cheie) {
    Binar *e=(Binar *)malloc(sizeof(Binar));
    if (e==NULL) {
        printf("Erreur\n");
        perror("Erreur");
        exit(1);
    }
    e->cheie=cheie;
    e->stanga=NULL;
    e->dreapta=NULL;
    return e;
}

void appendBinar(Binar *arbore, int cheieFiu, int cheieParinte, Pozitie poz) {
    if (arbore->cheie==cheieParinte) {
        if (arbore->stanga==NULL && poz==STANGA) {
            arbore->stanga=nou(cheieFiu);
        }
        else if (arbore->dreapta==NULL && poz==DREAPTA) {
            arbore->dreapta=nou(cheieFiu);
        }
    }
    if (arbore->stanga != NULL) {
        appendBinar(arbore->stanga,cheieFiu,cheieParinte,poz);
    }
    if (arbore->dreapta != NULL) {
        appendBinar(arbore->dreapta,cheieFiu,cheieParinte,poz);
    }
}

void rsdBinar(Binar *arbore) {
    if (arbore==NULL) {
        return;
    }
    printf("%d ",arbore->cheie);
    rsdBinar(arbore->stanga);
    rsdBinar(arbore->dreapta);
}

void srdBinar(Binar *arbore) {
    if (arbore==NULL) {
        return;
    }
    srdBinar(arbore->stanga);
    printf("%d ",arbore->cheie);
    srdBinar(arbore->dreapta);
}

void sdrBinar(Binar *arbore) {
    if (arbore==NULL) {
        return;
    }
    sdrBinar(arbore->stanga);
    sdrBinar(arbore->dreapta);
    printf("%d ",arbore->cheie);
}

void eliberare(Binar *arbore) {
    if (arbore==NULL) {
        return;
    }
    if (arbore->stanga==NULL && arbore->dreapta==NULL) {
        free(arbore);
    }
    else {
        eliberare(arbore->stanga);
        eliberare(arbore->dreapta);
    }

}

void transformare2(arboreType2 *arbore1, Binar *arbore2, int start) {
    if (arbore1->elemente[start].primFiu!=-1) {
        appendBinar(arbore2,arbore1->elemente[start].primFiu,arbore1->elemente[start].cheie,STANGA);
        transformare2(arbore1,arbore2,arbore1->elemente[start].primFiu);
    }
    if (arbore1->elemente[start].frateDreapta!=-1) {
        appendBinar(arbore2,arbore1->elemente[start].frateDreapta,arbore1->elemente[start].cheie,DREAPTA);
        transformare2(arbore1,arbore2,arbore1->elemente[start].frateDreapta);
    }
}

int main(void) {
    arboreType1 arbore1;
    arbore1Init(&arbore1, 10);
    arbore1Append(&arbore1, 0, -1, 0);
    arbore1Append(&arbore1, 1, 0, 1);
    arbore1Append(&arbore1, 2, 0, 2);
    arbore1Append(&arbore1, 3, 0, 3);
    arbore1Append(&arbore1, 4, 1, 4);
    arbore1Append(&arbore1, 5, 1, 5);
    arbore1Append(&arbore1, 6, 2, 6);
    arbore1Append(&arbore1, 7, 3, 7);
    arbore1Append(&arbore1, 8, 3, 8);
    arbore1Append(&arbore1, 9, 3, 9);
    printArray(&arbore1);

    printf("\nrsd1: ");
    arbore1Rsd(&arbore1, 0);

    printf("\nsrd1: ");
    arbore1Srd(&arbore1, 0);

    printf("\nsdr1: ");
    arbore1Sdr(&arbore1, 0);
    printf("\n\n");

    arboreType2 arbore2;
    arbore2Init(&arbore2, 10);
    // arbore2Append(&arbore2, 0, 1, -1,0);
    // arbore2Append(&arbore2, 1, 4, 2, 1);
    // arbore2Append(&arbore2, 2, 6, 3,2);
    // arbore2Append(&arbore2, 3, 7, -1, 3);
    // arbore2Append(&arbore2, 4, -1, 5, 4);
    // arbore2Append(&arbore2, 5, -1, -1, 5);
    // arbore2Append(&arbore2, 6, -1, -1, 6);
    // arbore2Append(&arbore2, 7, -1, 8, 7);
    // arbore2Append(&arbore2, 8, -1, 9, 8);
    // arbore2Append(&arbore2, 9, -1, -1,9);

    transformare1(&arbore1, &arbore2);

    printArbore(&arbore2);
    printf("\nrsd2: ");
    arbore2Rsd(&arbore2, 0);

    printf("\nsrd2: ");
    arbore2Srd(&arbore2, 0);

    printf("\nsdr2: ");
    arbore2Sdr(&arbore2, 0);

    printf("\n\n");

    Binar *arbore=nou(arbore2.elemente[0].cheie);
    //appendBinar(arbore, 1, 0, STANGA);
    // appendBinar(arbore, 2, 1, STANGA);
    // appendBinar(arbore, 3, 1, DREAPTA);
    // appendBinar(arbore, 4, 2, STANGA);
    // appendBinar(arbore, 5, 2, DREAPTA);
    // appendBinar(arbore, 6, 3, DREAPTA);
    transformare2(&arbore2,arbore,0);
    printf("rsdBinar: ");
    rsdBinar(arbore);
    printf("\nsrdBinar: ");
    srdBinar(arbore);
    printf("\nsdrBinar: ");
    sdrBinar(arbore);

    free(arbore1.elemente);
    free(arbore2.elemente);
    eliberare(arbore);
    return 0;
}