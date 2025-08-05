#include <stdio.h>
#include <stdlib.h>

typedef struct nod1 {
    int cheie;
    int parinte;
}nod1;

typedef struct {
    int size;
    nod1 *noduri;
}Arbore1;

void arbore1Init(Arbore1 *arbore, int size) {
    arbore->size = size;
    arbore->noduri = (nod1 *)malloc(size * sizeof(nod1));
}

void append1(Arbore1 *arbore, int cheie, int parinte) {
    arbore->noduri[cheie].cheie = cheie;
    arbore->noduri[cheie].parinte = parinte;
}

void afisare1(Arbore1 arbore) {
    printf("Cheie:\n");
    for (int i = 0; i < arbore.size; i++) {
        printf("%d ", arbore.noduri[i].cheie);
    }printf("\n");

    printf("Parinte:\n");
    for (int i = 0; i < arbore.size; i++) {
        printf("%d ", arbore.noduri[i].parinte);
    }printf("\n");
}

void rsd1(Arbore1 *arbore, int start) {
    printf("%d ",arbore->noduri[start].cheie);

    for (int i = 0; i < arbore->size; i++) {
        if (arbore->noduri[start].cheie == arbore->noduri[i].parinte) {
            rsd1(arbore, arbore->noduri[i].cheie);
        }
    }
}

void srd1(Arbore1 *arbore, int start) {
    int flag=0;
    for (int i = 0; i < arbore->size; i++) {
        if (arbore->noduri[start].cheie == arbore->noduri[i].parinte) {
            if (!flag) {
                srd1(arbore, arbore->noduri[i].cheie);

                printf("%d ",arbore->noduri[start].cheie);
                flag = 1;
            }
            else {
                srd1(arbore, arbore->noduri[i].cheie);
            }
        }
    }

    if (!flag) {
        printf("%d ",arbore->noduri[start].cheie);
    }
}

void srd(Arbore1 *arbore, int start) {
    int flag=0;
    for (int i = 0; i < arbore->size; i++) {
        if (arbore->noduri[i].parinte == arbore->noduri[start].cheie) {
            if (!flag) {
                srd(arbore, arbore->noduri[i].cheie);
                printf("%d ", arbore->noduri[start].cheie);
                flag = 1;
            }
            else {
                srd(arbore, arbore->noduri[i].cheie);
            }
        }
    }

    if (!flag) {
        printf("%d ",arbore->noduri[start].cheie);
    }
}


void sdr1(Arbore1 *arbore, int start) {
    for (int i = 0; i < arbore->size; i++) {
        if (arbore->noduri[start].cheie == arbore->noduri[i].parinte) {
            sdr1(arbore, arbore->noduri[i].cheie);
        }
    }

    printf("%d ",arbore->noduri[start].cheie);
}

int main(void) {
    Arbore1 arbore1;
    arbore1Init(&arbore1, 10);
    append1(&arbore1, 0, -1);
    append1(&arbore1, 1, 0);
    append1(&arbore1, 2, 0);
    append1(&arbore1, 3, 0);
    append1(&arbore1, 4, 1);
    append1(&arbore1, 5, 1);
    append1(&arbore1, 6, 2);
    append1(&arbore1, 7, 3);
    append1(&arbore1, 8, 3);
    append1(&arbore1, 9, 3);

    afisare1(arbore1);

    printf("Rsd1: ");
    rsd1(&arbore1, 0);

    printf("\nSrd1: ");
    srd1(&arbore1, 0);

    printf("\nSdr1: ");
    sdr1(&arbore1, 0);

    free(arbore1.noduri);

    return 0;
}