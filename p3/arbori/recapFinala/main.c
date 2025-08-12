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

typedef struct nod2 {
    int cheie;
    int primFiu;
    int frateDreapta;
}nod2;

typedef struct {
    int size;
    nod2 *noduri;
}Arbore2;

typedef struct node {
    int cheie;
    struct node *stanga;
    struct node *dreapta;
}node;

typedef enum {
    STANGA,
    DREAPTA
}Pozitie;

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


void sdr1(Arbore1 *arbore, int start) {
    for (int i = 0; i < arbore->size; i++) {
        if (arbore->noduri[start].cheie == arbore->noduri[i].parinte) {
            sdr1(arbore, arbore->noduri[i].cheie);
        }
    }

    printf("%d ",arbore->noduri[start].cheie);
}

void arbore2Init(Arbore2 *arbore, int size) {
    arbore->size = size;
    arbore->noduri = (nod2 *)malloc(size * sizeof(nod2));
}

void append2(Arbore2 *arbore, int cheie, int primFiu, int frateDreapta) {
    arbore->noduri[cheie].cheie = cheie;
    arbore->noduri[cheie].primFiu = primFiu;
    arbore->noduri[cheie].frateDreapta = frateDreapta;
}

void afisare2(Arbore2 arbore) {
    printf("Cheie:\n");
    for (int i = 0; i < arbore.size; i++) {
        printf("%d ", arbore.noduri[i].cheie);
    }printf("\n");

    printf("Prim fiu:\n");
    for (int i = 0; i < arbore.size; i++) {
        printf("%d ", arbore.noduri[i].primFiu);
    }printf("\n");

    printf("Frate dreapta:\n");
    for (int i = 0; i < arbore.size; i++) {
        printf("%d ", arbore.noduri[i].frateDreapta);
    }printf("\n");
}

void rsd2(Arbore2 *arbore, int start) {
    printf("%d ",arbore->noduri[start].cheie);

    int copil=arbore->noduri[start].primFiu;
    while (copil!=-1) {
        rsd2(arbore, copil);
        copil=arbore->noduri[copil].frateDreapta;
    }
}

void srd2(Arbore2 *arbore, int start) {
    int copil=arbore->noduri[start].primFiu;
    int flag=0;
    while (copil!=-1) {
        if (!flag) {
            srd2(arbore, copil);
            printf("%d ",start);
            flag = 1;
        }
        else {
            srd2(arbore, copil);
        }
        copil=arbore->noduri[copil].frateDreapta;
    }

    if (!flag) {
        printf("%d ",start);
    }
}

void sdr2(Arbore2 *arbore, int start) {
    int copil=arbore->noduri[start].primFiu;
    while (copil!=-1) {
        sdr2(arbore, copil);
        copil=arbore->noduri[copil].frateDreapta;
    }
    printf("%d ",start);
}

void transform1(Arbore1 *arbore1, Arbore2 *arbore2) {
    for (int i = 0; i < arbore1->size; i++) {
        arbore2->noduri[i].cheie = arbore1->noduri[i].cheie;
        arbore2->noduri[i].primFiu = -1;
        arbore2->noduri[i].frateDreapta = -1;
    }

    for (int i=0;i<arbore1->size;i++) {
        for (int j=0;j<arbore1->size;j++) {
            if (arbore1->noduri[i].cheie == arbore1->noduri[j].parinte) {
                arbore2->noduri[i].primFiu = arbore1->noduri[j].cheie;
                break;
            }
        }
    }

    for (int i=0;i<arbore1->size;i++) {
        int frate=arbore1->noduri[i+1].cheie;
        for (int j=i+1;j<arbore1->size;j++) {
            if (arbore1->noduri[i].parinte == arbore1->noduri[j].parinte) {
                arbore2->noduri[i].frateDreapta = frate;
                frate = arbore1->noduri[j].cheie;
            }
            else {
                break;
            }
        }
    }
}

node *nou(int cheie) {
    node *e=(node *)malloc(sizeof(node));
    e->cheie = cheie;
    e->stanga=e->dreapta=NULL;
    return e;
}

void appendBinar(node *arbore, int cheieFiu, Pozitie poz, int cheieParinte) {
    if (arbore == NULL) {
        arbore = nou(cheieFiu);
    }
    else {
        if (arbore->cheie == cheieParinte) {
            if (poz == STANGA) {
                arbore->stanga = nou(cheieFiu);
            }
            else {
                arbore->dreapta = nou(cheieFiu);
            }
        }
        else {
            appendBinar(arbore->stanga,cheieFiu,poz,cheieParinte);
            appendBinar(arbore->dreapta,cheieFiu,poz,cheieParinte);
        }
    }

}

void rsd(node *arbore) {
    if (arbore == NULL) {
        return;
    }
    printf("%d ",arbore->cheie);
    rsd(arbore->stanga);
    rsd(arbore->dreapta);
}

void srd(node *arbore) {
    if (arbore == NULL) {
        return;
    }
    srd(arbore->stanga);
    printf("%d ",arbore->cheie);
    srd(arbore->dreapta);
}

void sdr(node *arbore) {
    if (arbore == NULL) {
        return;
    }
    sdr(arbore->stanga);
    sdr(arbore->dreapta);
    printf("%d ",arbore->cheie);
}

void eliberare(node *arbore) {
    if (arbore == NULL) {
        return;
    }
    eliberare(arbore->stanga);
    eliberare(arbore->dreapta);
    free(arbore);
}

void transform2(Arbore2 *arbore1, node *arbore2, int start) {
    if (arbore1->noduri[start].primFiu != -1) {
        appendBinar(arbore2,arbore1->noduri[start].primFiu,STANGA,arbore1->noduri[start].cheie);
        transform2(arbore1,arbore2,arbore1->noduri[start].primFiu);
    }

    if (arbore1->noduri[start].frateDreapta != -1) {
        appendBinar(arbore2,arbore1->noduri[start].frateDreapta,DREAPTA,arbore1->noduri[start].cheie);
        transform2(arbore1,arbore2,arbore1->noduri[start].frateDreapta);
    }

}

int check(Arbore1 arbore, int cheie) {
    for (int i=0;i<arbore.size;i++) {
        if (arbore.noduri[i].parinte == cheie) return 0;
    }
    return 1;
}

void inaltimeOarecare(Arbore1 *arbore, int start, int *max, int crtMax) {
    if (check(*arbore,start)) {
        if (*max<crtMax) {
            *max=crtMax;

        }
        crtMax=0;
    }
    for (int i = 0; i < arbore->size; i++) {
        if (arbore->noduri[i].parinte == arbore->noduri[start].cheie) {
            inaltimeOarecare(arbore,arbore->noduri[i].cheie,max,crtMax+1);
        }
    }
}

void inaltimeBinar(node *arbore, int *max, int maxCrt) {
    if (arbore == NULL) {
        return;
    }
    if (maxCrt>*max && arbore->stanga == NULL && arbore->dreapta == NULL) {
        *max=maxCrt;
        maxCrt=0;
    }
    inaltimeBinar(arbore->stanga,max,maxCrt+1);
    inaltimeBinar(arbore->dreapta,max,maxCrt+1);
}

int main(void) {
    Arbore1 arbore1;
    arbore1Init(&arbore1, 11);
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
    append1(&arbore1, 10, 4);

    //afisare1(arbore1);

    printf("rsd pe arbore oarecare1: ");
    rsd1(&arbore1,0);

    Arbore2 arbore2;
    arbore2Init(&arbore2, 11);
    transform1(&arbore1, &arbore2);
    printf("\nrsd pe arbore oarecare2: ");
    rsd2(&arbore2,0);

    node *arbore=nou(arbore1.noduri[0].cheie);
    transform2(&arbore2, arbore, arbore1.noduri[0].cheie);

    printf("\nrsd pe arbore binar: ");
    rsd(arbore);

    int max1=0, max1Crt=0;
    inaltimeOarecare(&arbore1,0,&max1,max1Crt);
    printf("\ninaltime pe oarecare: %d",max1);

    int max=0,maxCrt=0;
    inaltimeBinar(arbore,&max,maxCrt);
    printf("\ninaltime pe binar: %d\n",max);

    free(arbore1.noduri);
    free(arbore2.noduri);
    eliberare(arbore);
    return 0;
}