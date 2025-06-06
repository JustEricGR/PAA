#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod {
    char nume[20];
    struct nod *stanga;
    struct nod *dreapta;
}nod;

nod *nou(char nume[20]) {
    nod *e = (nod *)malloc(sizeof(nod));
    if (e == NULL) {
        printf("Eroare la alocare nod\n");
        perror(NULL);
        exit(-1);
    }
    strcpy(e->nume, nume);
    e->stanga = NULL;
    e->dreapta = NULL;
    return e;
}

void append(nod *arbore, char nume[20]) {

    if (strlen(nume) < strlen(arbore->nume)) {
        if (arbore->stanga == NULL) {
            arbore->stanga = nou(nume);
        }
        else {
            append(arbore->stanga, nume);
        }
    }
    else if (strlen(nume) >= strlen(arbore->nume)) {
        if (arbore->dreapta == NULL) {
            arbore->dreapta = nou(nume);
        }
        else {
            append(arbore->dreapta, nume);
        }
    }


}

void afisareInordine(nod *arbore) {
    if (arbore == NULL) {
        return;
    }
    afisareInordine(arbore->stanga);
    printf("%s ", arbore->nume);
    afisareInordine(arbore->dreapta);
}

void eliberare(nod *arbore) {
    if (arbore == NULL) return;
    eliberare(arbore->stanga);
    eliberare(arbore->dreapta);
    free(arbore);
}


int cmp(const void **e1, const void **e2) {
    char **str1 = (char **)e1;
    char **str2 = (char **)e2;
    return strcmp(*str2, *str1);
}

nod *adugareEficienta(char *nume[20], int size, int *lungime) {
    qsort(nume, size, sizeof(char*), cmp);


    int mijl=size/2;
    nod *arbore=nou(nume[mijl]);
    *lungime+=strlen(nume[mijl]);


    for (int i=1; i<=size/2; i++) {
        if (mijl+i >= size) break;
        append(arbore, nume[mijl+i]);
        if (mijl-i < 0) break;
        append(arbore, nume[mijl-i]);
        *lungime+=strlen(nume[mijl-i])+strlen(nume[mijl+i]);
    }

    return arbore;
}

int main(void) {


    char *elemente[20] = {
        "Hidrogen",
        "Heliu",
        "Carbon",
        "Azot",
        "Oxigen",
        "Sodiu",
        "Clor",
        "Fier",
        "Cupru",
        "Zinc"
    };

    int lungime=0;
    int size=10;
    nod *arbore=adugareEficienta(elemente, size, &lungime);
    printf("Lungime medie: %g\n", (float)lungime/size);

    afisareInordine(arbore);

    eliberare(arbore);


    return 0;
}