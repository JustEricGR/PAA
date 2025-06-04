#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nod {
    int cheie;
    struct nod *stanga;
    struct nod *dreapta;
}nod;

nod *nou(int cheie) {
    nod *e = (nod *)malloc(sizeof(nod));
    if (e == NULL) {
        printf("Eroare la alocare nod\n");
        perror(NULL); exit(-1);
    }
    e->cheie = cheie;
    e->stanga = NULL;
    e->dreapta = NULL;
    return e;
}

void append(nod *arbore, int cheie) {
    if (arbore == NULL) {
        arbore = nou(cheie);
    }
    else {
        if (cheie < arbore->cheie) {
            if (arbore->stanga == NULL) {
                arbore->stanga = nou(cheie);
            }
            else {
                append(arbore->stanga, cheie);
            }
        }
        else {
            if (arbore->dreapta == NULL) {
                arbore->dreapta = nou(cheie);
            }
            else {
                append(arbore->dreapta, cheie);
            }

        }
    }
}

void inordine(nod *arbore) {
    if (arbore == NULL) return;
    inordine(arbore->stanga);
    printf("%d ", arbore->cheie);
    inordine(arbore->dreapta);
}

void eliberare(nod *arbore) {
    if (arbore == NULL) return;
    if (arbore->stanga == NULL && arbore->dreapta == NULL) free(arbore);
    else {
        eliberare(arbore->stanga);
        eliberare(arbore->dreapta);
    }
}

nod *verificare(int size) {
    nod *arbore=NULL;
    srand(time(NULL));
    arbore=nou(rand()%size);
    for (int i = 1; i < size; i++) {
        append(arbore, rand()%100);
    }
    return arbore;
}

void predecesorParcurgereInordine(nod *arbore, int cheie, nod **predecesor, int *gasit) {
    if (arbore == NULL || *gasit) {
        return;
    }

    predecesorParcurgereInordine(arbore->stanga, cheie, predecesor, gasit);
    if (arbore->cheie == cheie) {
        *gasit=1;
        return;
    }

    if (!(*gasit)) {
        *predecesor=arbore;
    }
    predecesorParcurgereInordine(arbore->dreapta, cheie, predecesor, gasit);
}

nod *suprimare(nod *arbore, int cheie) {
    if (arbore == NULL) return;

    if (arbore->cheie == cheie) {
        if (arbore->stanga == NULL) {
            nod *temp = arbore->dreapta;
            free(arbore);
            return temp;
        }
        else if (arbore->dreapta == NULL) {
            nod *temp = arbore->stanga;
            free(arbore);
            return temp;
        }
        nod *pred=NULL;
        int gasit=0;
        predecesorParcurgereInordine(arbore, cheie, &pred, &gasit);
        arbore->cheie=pred->cheie;
        arbore->stanga=suprimare(arbore->stanga, pred->cheie);
    }
    else if (cheie < arbore->cheie) {
        arbore->stanga=suprimare(arbore->stanga, cheie);
    }
    else if (cheie > arbore->cheie) {
        arbore->dreapta=suprimare(arbore->dreapta, cheie);
    }

    return arbore;
}

int main(void) {
    nod *arbore=NULL;
    //int size=0;
    //printf("Dati o valoare: ");
    //scanf("%d", &size);
    //arbore = verificare(size);
    arbore=nou(4);
    append(arbore, 2);
    append(arbore, 3);
    append(arbore, 1);
    append(arbore, 6);
    append(arbore, 7);
    append(arbore, 5);
    inordine(arbore);

    arbore=suprimare(arbore, 2);
    printf("\n");
    inordine(arbore);

    eliberare(arbore);
    return 0;
}