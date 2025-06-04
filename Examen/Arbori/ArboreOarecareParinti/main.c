#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cheie;
    int parinte;
}Nod;

typedef struct {
    int size;
    Nod *array;
}Tree;

void treeInit(Tree *arbore, int size) {
    arbore->size = size;
    arbore->array = (Nod *)malloc(size * sizeof(Nod));
}

void append(Tree *arbore, int cheie, int parinte) {
    arbore->array[cheie].cheie=cheie;
    arbore->array[cheie].parinte = parinte;
}

void printArray(Tree *arbore) {
    printf("Index:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", i);
    }

    printf("\nCheie:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", arbore->array[i].cheie);
    }

    printf("\nParinte:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ", arbore->array[i].parinte);
    }
}

void rsd(Tree *arbore, int start) {
    printf("%d ", arbore->array[start].cheie);
    if (start == arbore->size - 1) return;
    for (int i=0;i<arbore->size;i++) {
        if (arbore->array[i].parinte == arbore->array[start].cheie) {
            rsd(arbore, arbore->array[i].cheie);
        }
    }
}

int primFiu(Tree *arbore, int cheie) {
    for (int i = 0; i < arbore->size; i++) {
        if (arbore->array[i].parinte == cheie) {
            return arbore->array[i].cheie;
        }
    }
    return -1;
}

void srd(Tree *arbore, int start) {
    int flag=0;
    for (int i = 0; i < arbore->size; i++) {
        if (arbore->array[i].parinte == arbore->array[start].cheie) {
            if (!flag) {
                srd(arbore, arbore->array[i].cheie);
                printf("%d ", arbore->array[start].cheie);
                flag = 1;
            }
            else {
                srd(arbore, arbore->array[i].cheie);
            }
        }
    }

    if (!flag) {
        printf("%d ",arbore->array[start].cheie);
    }
}

void sdr(Tree *arbore, int start) {

    for (int i=0;i<arbore->size;i++) {
        if (arbore->array[i].parinte == arbore->array[start].cheie) {
            sdr(arbore, arbore->array[i].cheie);

        }
    }
    printf("%d ", arbore->array[start].cheie);
}


int main(void) {
    Tree arbore;
    treeInit(&arbore, 10);
    append(&arbore, 0, -1);
    append(&arbore, 1, 0);
    append(&arbore, 2, 0);
    append(&arbore, 3, 0);
    append(&arbore, 4, 1);
    append(&arbore, 5, 1);
    append(&arbore, 6, 2);
    append(&arbore, 7, 3);
    append(&arbore, 8, 3);
    append(&arbore, 9, 3);
    printArray(&arbore);

    printf("\nrsd: ");
    rsd(&arbore, 0);

    printf("\nsrd: ");
    srd(&arbore, 0);

    printf("\nsdr: ");
    sdr(&arbore, 0);


    free(arbore.array);
    return 0;
}