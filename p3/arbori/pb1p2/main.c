#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cheie;
    int parinte;
}nod;

typedef struct {
    int size;
    nod *array;
}Arbore;

void citire(Arbore *arbore, const char *in) {
    FILE *fin=NULL;
    if ((fin=fopen(in,"r"))==NULL) {
        printf("Eroare la deschidere fisier\n");
        perror(NULL);
        exit(-1);
    }
    arbore->size=0;
    arbore->array=malloc(sizeof(nod));
    while (fscanf(fin,"%d,%d",&(arbore->array[arbore->size].cheie),&(arbore->array[arbore->size].parinte))==2) {
        arbore->size++;
        arbore->array=realloc(arbore->array,(arbore->size+1)*sizeof(nod));
    }

}

void afisare(Arbore arbore) {
    printf("Chei:\n");
    for (int i=0;i<arbore.size;i++) {
        printf("%d ",arbore.array[i].cheie);
    }printf("\n");

    printf("Parinte:\n");
    for (int i=0;i<arbore.size;i++) {
        printf("%d ",arbore.array[i].parinte);
    }printf("\n");
}

void rsd(Arbore *arbore, int start) {
    printf("%d ",arbore->array[start].cheie);
    for (int i=0;i<arbore->size;i++) {
        if (arbore->array[start].cheie==arbore->array[i].parinte) {
            rsd(arbore,i);
        }
    }
}

int nivelManagement(Arbore *arbore, int start, int end, int nivel) {
    if (start==end) {
        return nivel;
    }
    for (int i=0;i<arbore->size;i++) {
        if (arbore->array[start].cheie==arbore->array[i].parinte) {
            int rez=nivelManagement(arbore,i,end,nivel+1);
            if (rez!=-1) {
                return rez;
            }
        }
    }
    return -1;
}

void nivelTotal(Arbore *arbore) {
    for (int i=1;i<arbore->size;i++) {

        int nivel=nivelManagement(arbore,0,i,0);
        printf("Nivelul de management pt %d : %d\n",arbore->array[i].cheie, nivel);
    }
}

int commandChain(Arbore *arbore, int start, int end) {

    if (start==end) {
        printf("%d ",start);
        return 1;
    }
    for (int i=0;i<arbore->size;i++) {
        if (arbore->array[start].cheie==arbore->array[i].parinte) {
            int rez=commandChain(arbore,i,end);

            if (rez!=-1) {
                printf("%d ",start);
                return 1;
            }
        }
    }
    return -1;
}

int main(int argc, char **argv) {
    Arbore arbore;
    citire(&arbore,argv[1]);
    afisare(arbore);
    rsd(&arbore,3);
    printf("\n");
    nivelTotal(&arbore);
    commandChain(&arbore,0,9);

    free(arbore.array);
    return 0;
}