#include <stdio.h>
#include <stdlib.h>

typedef struct nod {
    int cheie;
    int parinte;
}nod;

typedef struct {
    int size;
    nod *noduri;
}ArboreOarecare;

typedef struct nod1 {
    int cheie;
    int primFiu;
    int frateDreapta;
}nod1;

typedef struct {
    int size;
    nod1 *noduri;
}ArboreOarecare1;

typedef enum {
    STANGA,
    DREAPTA
}poz;

typedef struct node{
    int cheie;
    struct node *stanga;
    struct node *dreapta;
}node;


void arboreOarecareInit(ArboreOarecare *arbore, int size) {
    arbore->size = size;
    arbore->noduri = (nod*)malloc(size * sizeof(nod));

}

void append(ArboreOarecare *arbore, int cheie,int parinte) {
    arbore->noduri[cheie].cheie = cheie;
    arbore->noduri[cheie].parinte = parinte;
}

void afisare(ArboreOarecare arbore) {
    printf("Cheie:\n");
    for (int i = 0; i < arbore.size; i++) {
        printf("%d ", arbore.noduri[i].cheie);
    }printf("\n");

    printf("Parinte:\n");
    for (int i = 0; i < arbore.size; i++) {
        printf("%d ", arbore.noduri[i].parinte);
    }printf("\n");
}

void afisareRsd(ArboreOarecare *arbore, int start) {
    if (arbore==NULL)return;
    printf("%d ", arbore->noduri[start].cheie);
    for (int i = 0; i < arbore->size ; i++) {
        if (start == arbore->noduri[i].parinte) {
            afisareRsd(arbore, arbore->noduri[i].cheie);
        }
    }
}

void afisareSrd(ArboreOarecare *arbore, int start) {
    if (arbore==NULL)return;
    int flag=0;
    for (int i = 0; i < arbore->size ; i++) {
        if (arbore->noduri[start].cheie == arbore->noduri[i].parinte) {
            //printf("%d\n", arbore->noduri[start].cheie);
            if (!flag) {
                afisareSrd(arbore, arbore->noduri[i].cheie);
                flag = 1;
                printf("%d ", arbore->noduri[start].cheie);
            }
            else {
                afisareSrd(arbore, arbore->noduri[i].cheie);
            }
        }
    }

    if (!flag) {
        printf("%d ", arbore->noduri[start].cheie);
    }
}

void afisareSdr(ArboreOarecare *arbore, int start) {
    if (arbore==NULL)return;
    for (int i = 0; i < arbore->size ; i++) {
        if (start == arbore->noduri[i].parinte) {
            afisareSdr(arbore, arbore->noduri[i].cheie);

        }
    }
    printf("%d ", arbore->noduri[start].cheie);
}

void arboreOarecare1Init(ArboreOarecare1 *arbore, int size) {
    arbore->size = size;
    arbore->noduri = (nod1*)malloc(size * sizeof(nod1));
}

void afisare1(ArboreOarecare1 arbore) {
    printf("Cheie:\n");
    for (int i = 0; i < arbore.size; i++) {
        printf("%d ", arbore.noduri[i].cheie);
    }printf("\n");

    printf("Prim Fiu:\n");
    for (int i = 0; i < arbore.size; i++) {
        printf("%d ", arbore.noduri[i].primFiu);
    }printf("\n");

    printf("Frate Dreapta:\n");
    for (int i = 0; i < arbore.size; i++) {
        printf("%d ", arbore.noduri[i].frateDreapta);
    }printf("\n");
}

void append1(ArboreOarecare1 *arbore, int cheie, int primFiu, int frateDreapta) {
    arbore->noduri[cheie].cheie = cheie;
    arbore->noduri[cheie].primFiu = primFiu;
    arbore->noduri[cheie].frateDreapta = frateDreapta;
}

void afisareRsd1(ArboreOarecare1 *arbore, int start) {
    printf("%d ", arbore->noduri[start].cheie);
    int copil=arbore->noduri[start].primFiu;
    while (copil!=-1) {
        afisareRsd1(arbore, copil);
        copil=arbore->noduri[copil].frateDreapta;
    }
}

void afisareSrd1(ArboreOarecare1 *arbore, int start) {
    int copil=arbore->noduri[start].primFiu;
    int flag=0;
    while (copil!=-1) {

        if (!flag) {
            afisareSrd1(arbore, copil);

            flag = 1;
            printf("%d ", arbore->noduri[start].cheie);
        }
        else {
            afisareSrd1(arbore, copil);
        }
        copil=arbore->noduri[copil].frateDreapta;
    }

    if (!flag) {
        printf("%d ", arbore->noduri[start].cheie);
    }
}

void afisareSdr1(ArboreOarecare1 *arbore, int start) {
    int copil=arbore->noduri[start].primFiu;
    while (copil!=-1) {
        afisareSdr1(arbore, copil);
        copil=arbore->noduri[copil].frateDreapta;
    }
    printf("%d ", arbore->noduri[start].cheie);
}

node *nou(int cheie) {
    node *e=(node*)malloc(sizeof(node));
    e->cheie=cheie;
    e->stanga=e->dreapta=NULL;
    return e;
}

void adaugare(node* arbore, int cheieParinte, poz pozitie, int cheieFiu) {
    if (arbore==NULL)return;
    if (arbore->cheie==cheieParinte) {
        if (pozitie == STANGA) {
            arbore->stanga=nou(cheieFiu);
        }
        else {
            arbore->dreapta=nou(cheieFiu);
        }
    }
    else {
        adaugare(arbore->stanga,cheieParinte,pozitie,cheieFiu);
        adaugare(arbore->dreapta,cheieParinte,pozitie,cheieFiu);
    }
}

void rsd(node *arbore) {
    if (arbore==NULL)return;
    printf("%d ", arbore->cheie);
    rsd(arbore->stanga);
    rsd(arbore->dreapta);
}

void srd(node *arbore) {
    if (arbore==NULL)return;
    srd(arbore->stanga);
    printf("%d ", arbore->cheie);
    srd(arbore->dreapta);
}

void sdr(node *arbore) {
    if (arbore==NULL)return;
    sdr(arbore->stanga);
    sdr(arbore->dreapta);
    printf("%d ", arbore->cheie);
}

void eliberare(node *arbore) {
    if (arbore == NULL ) {
        //free(arbore);
        return;
    }
    else {
        eliberare(arbore->stanga);
        eliberare(arbore->dreapta);
    }

}

void convert1(ArboreOarecare *arbore, ArboreOarecare1 *arbore1) {
    for (int i=0;i<arbore1->size;i++) {
        arbore1->noduri[i].primFiu=-1;
        arbore1->noduri[i].frateDreapta=-1;
        arbore1->noduri[i].cheie=arbore->noduri[i].cheie;
    }

    for (int i=0;i<arbore1->size;i++) {
        for (int j=0;j<arbore1->size;j++) {

            if (arbore->noduri[i].cheie==arbore->noduri[j].parinte) {
                arbore1->noduri[i].primFiu=arbore->noduri[j].cheie;
                for (int k=j;k<arbore1->size;k++) {
                    for (int l=k+1;l<arbore1->size;l++) {
                        if (arbore->noduri[k].parinte==arbore->noduri[l].parinte) {
                            arbore1->noduri[k].frateDreapta=arbore1->noduri[l].cheie;
                            break;
                        }
                    }

                }
                break;
            }
        }
    }
}

int main(void) {
    ArboreOarecare arbore;
    ArboreOarecare1 arbore1;
    int size=10;
    arboreOarecareInit(&arbore, size);
    arboreOarecare1Init(&arbore1, size);
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

    // afisare(arbore);
    // printf("Rsd: ");
    // afisareRsd(&arbore, 0);
    //
    // printf("\nSrd: ");
    // afisareSrd(&arbore, 0);
    //
    // printf("\nSdr: ");
    // afisareSdr(&arbore, 0);
    convert1(&arbore, &arbore1);
    afisare1(arbore1);
    free(arbore.noduri);
    free(arbore1.noduri);

    // node *arbore=nou(0);
    // adaugare(arbore, 0, STANGA, 1);
    // adaugare(arbore, 1, STANGA, 3);
    // adaugare(arbore, 1, DREAPTA, 4);
    // adaugare(arbore, 0, DREAPTA, 2);
    // adaugare(arbore, 2, STANGA, 5);
    // printf("rsd: ");
    // rsd(arbore);
    //
    // printf("srd: ");
    // srd(arbore);
    //
    // printf("sdr: ");
    // sdr(arbore);
    // eliberare(arbore);

    return 0;
}