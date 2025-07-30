#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int parent;
} nod;

typedef enum {
    NU, //stanga
    DA, //dreapta
}Raspuns;

typedef struct node {
    int cheie;
    struct node *stanga;
    struct node *dreapta;
} node;

node *nou(int cheie) {
    node *nou = (node *)malloc(sizeof(node));
    if (nou == NULL) {
        printf("Eroare la alocare nod\n");
        perror(NULL);
        exit(1);
    }
    nou->cheie = cheie;
    nou->stanga = NULL;
    nou->dreapta = NULL;
    return nou;
}

int append(node **arbore, int cheieFiu, Raspuns pozitie, int cheieParinte) {
    if (*arbore == NULL) {
        return 0;
    }
    else if ((*arbore)->cheie == cheieParinte){
        if (pozitie == NU) {
            (*arbore)->stanga = nou(cheieFiu);
        }
        else {
            (*arbore)->dreapta = nou(cheieFiu);
        }

    }
    else {
        if (append(&((*arbore)->stanga), cheieFiu, pozitie, cheieParinte)) return 1;
        if (append(&((*arbore)->dreapta), cheieFiu, pozitie, cheieParinte)) return 1;
    }

    return 0;
}

void afisareRsd(node *arbore) {
    if (arbore == NULL) {
        return;
    }
    printf("%d ", arbore->cheie);
    afisareRsd(arbore->stanga);
    afisareRsd(arbore->dreapta);
}

void eliberare(node *arbore) {
    if (arbore == NULL) {
        return;
    }

    eliberare(arbore->stanga);
    eliberare(arbore->dreapta);
    free(arbore);


}

void adaugare(node **arbore, const char *in) {
    FILE *fin=NULL;
    if ((fin=fopen(in, "r"))==NULL) {
        printf("Eroare la deschidere fisier 1\n");
        perror(NULL);
        exit(-1);
    }
    int size=0;

    fscanf(fin, "%d", &size);
    nod *noduri=(nod *)malloc(size*sizeof(nod));

    for (int i=0;i<size;i++) {
        fscanf(fin, "%d", &noduri[i].parent);
        noduri[i].key=i+1;
        //printf("%ld ",ftell(fin));
    }
    //append(arbore, noduri[0].key, NU, noduri[0].parent);
    *arbore=nou(noduri[0].key);
    for (int i=1;i<size-1;i+=2) {
        if (!append(arbore, noduri[i].key, NU, noduri[i].parent)) printf("Rau\n");
        if (!append(arbore, noduri[i+1].key, DA, noduri[i+1].parent)) printf("Rau\n");

    }
    free(noduri);
    fclose(fin);
}

void adancime(node *arbore, int minCrt, int *min) {
    if (arbore == NULL) {
        return;
    }
    if (arbore->stanga == NULL && arbore->dreapta == NULL && minCrt<*min) {
        *min=minCrt;
        minCrt=0;
    }
    adancime(arbore->stanga, minCrt+1, min);
    adancime(arbore->dreapta, minCrt+1, min);
}

node *deplasare(node *arbore, int direction) {
    if (direction == NU) {
        return arbore->stanga;
    }
    else if (direction == DA) {
        return arbore->dreapta;
    }
}

int diagnostic(node *arbore, const char *in) {
    FILE *fin=NULL;
    if ((fin=fopen(in, "r"))==NULL) {
        printf("Eroare la deschidere fisier 2\n");
        perror(NULL);
        exit(-1);
    }

    while (!feof(fin)) {
        int direction=0;
        fscanf(fin, "%d", &direction);
        arbore = deplasare(arbore, direction);
    }
    int min=INT_MAX, minCrt=0;
    adancime(arbore, minCrt, &min);

    fclose(fin);
    return min;
}

void adancimeMax(node *arbore, int maxCrt, int *max) {
    if (arbore == NULL) {
        return;
    }
    if (arbore->stanga == NULL && arbore->dreapta == NULL && maxCrt>*max) {
        *max=maxCrt;
        maxCrt=0;
    }
    adancimeMax(arbore->stanga, maxCrt+1, max);
    adancimeMax(arbore->dreapta, maxCrt+1, max);
}

int main(int argc, char **argv) {
    node *arbore=NULL;
    adaugare(&arbore, argv[1]);

    afisareRsd(arbore);

    int min=0;
    min=diagnostic(arbore, argv[2]);
    printf("\nNr necesar de intrebari: %d\n", min);
    int max=0, maxCrt=0;
    adancimeMax(arbore, maxCrt, &max);
    printf("\nNr maxim de intrebari: %d\n", max);
    eliberare(arbore);
    return 0;
}