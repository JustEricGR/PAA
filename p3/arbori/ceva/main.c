#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cheie;
    int parinte;
}nod1;

typedef struct {
    int size;
    nod1 *noduri;
}Arbore1;

typedef struct {
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

void arbore1Init(Arbore1 *arbore1, int size) {
    arbore1->size = size;
    arbore1->noduri = (nod1 *)malloc(size * sizeof(nod1));
}

void append1(Arbore1 *arbore1, int cheie, int parinte) {
    arbore1->noduri[cheie].cheie = cheie;
    arbore1->noduri[cheie].parinte = parinte;
}

void afisare1(Arbore1 arbore1) {
    printf("Chei: ");
    for (int i = 0; i < arbore1.size; i++) {
        printf("%d ", arbore1.noduri[i].cheie);
    }printf("\n");

    printf("Parinte: ");
    for (int i = 0; i < arbore1.size; i++) {
        printf("%d ", arbore1.noduri[i].parinte);
    }printf("\n");
}


void rsd1(Arbore1 *arbore, int start) {
    printf("%d ",arbore->noduri[start].cheie);
    for (int i=0;i<arbore->size;i++) {
        if (arbore->noduri[i].parinte==arbore->noduri[start].cheie) {
            rsd1(arbore, i);
        }
    }
}

void srd1(Arbore1 *arbore, int start) {
    int flag=0;
    for (int i=0;i<arbore->size;i++) {
        if (arbore->noduri[i].parinte==arbore->noduri[start].cheie) {
            if (!flag) {
                srd1(arbore, i);
                flag=1;
                printf("%d ",arbore->noduri[start].cheie);
            }
            else {
                srd1(arbore, i);
            }
        }
    }
    if (!flag) {
        printf("%d ",arbore->noduri[start].cheie);
    }
}

void sdr1(Arbore1 *arbore, int start) {
    for (int i=0;i<arbore->size;i++) {
        if (arbore->noduri[i].parinte==arbore->noduri[start].cheie) {
            sdr1(arbore, i);
        }
    }
    printf("%d ",arbore->noduri[start].cheie);
}


void arbore2Init(Arbore2 *arbore2, int size) {
    arbore2->size = size;
    arbore2->noduri = (nod2 *)malloc(size * sizeof(nod2));
}

void append2(Arbore2 *arbore2, int cheie, int primFiu, int frateDreapta) {
    arbore2->noduri[cheie].cheie = cheie;
    arbore2->noduri[cheie].primFiu = primFiu;
    arbore2->noduri[cheie].frateDreapta = frateDreapta;
}

void afisare2(Arbore2 arbore2) {
    printf("Chei: ");
    for (int i = 0; i < arbore2.size; i++) {
        printf("%d ", arbore2.noduri[i].cheie);
    }printf("\n");

    printf("PrimFiu: ");
    for (int i = 0; i < arbore2.size; i++) {
        printf("%d ", arbore2.noduri[i].primFiu);
    }printf("\n");

    printf("FrateDreapta: ");
    for (int i = 0; i < arbore2.size; i++) {
        printf("%d ", arbore2.noduri[i].frateDreapta);
    }printf("\n");
}

void rsd2(Arbore2 *arbore2, int start) {
    printf("%d ",arbore2->noduri[start].cheie);
    int copil=arbore2->noduri[start].primFiu;
    while (copil!=-1) {
        rsd2(arbore2, copil);
        copil=arbore2->noduri[copil].frateDreapta;
    }
}

void srd2(Arbore2 *arbore2, int start) {
    int flag=0;
    int copil=arbore2->noduri[start].primFiu;
    while (copil!=-1) {
        if (!flag) {
            srd2(arbore2, copil);
            flag=1;
            printf("%d ",arbore2->noduri[start].cheie);
        }
        else {
            srd2(arbore2, copil);
        }
        copil=arbore2->noduri[copil].frateDreapta;
    }

    if (!flag) {
        printf("%d ",arbore2->noduri[start].cheie);
    }
}

void sdr2(Arbore2 *arbore2, int start) {
    int copil=arbore2->noduri[start].primFiu;
    while (copil!=-1) {
        sdr2(arbore2, copil);
        copil=arbore2->noduri[copil].frateDreapta;
    }
    printf("%d ",arbore2->noduri[start].cheie);
}

void transform1(Arbore1 *arbore1, Arbore2 *arbore2) {
    for (int i=0;i<arbore1->size;i++) {
        arbore2->noduri[i].cheie = arbore1->noduri[i].cheie;
        arbore2->noduri[i].primFiu = -1;
        arbore2->noduri[i].frateDreapta = -1;
    }

    for (int i=0;i<arbore2->size;i++) {
        for (int j=0;j<arbore2->size;j++) {
            if (arbore1->noduri[i].cheie == arbore1->noduri[j].parinte) {
                arbore2->noduri[i].primFiu = arbore1->noduri[j].cheie;
                break;
            }
        }
    }

    for (int i=0;i<arbore2->size;i++) {
        int precedente = arbore2->noduri[i+1].cheie;
        for (int j=i+1;j<arbore2->size;j++) {
            //printf("precedente: %d\t parinte: %d\n",precedente,arbore1->noduri[j].parinte);
            if (arbore1->noduri[j].parinte == arbore1->noduri[i].parinte) {
                //printf("da");
                arbore2->noduri[i].frateDreapta = precedente;
                precedente = arbore2->noduri[j].cheie;
            }
            else break;
        }
    }
}

node *nou(int cheie) {
    node *e=(node *)malloc(sizeof(node));
    if (e==NULL) {
        printf("Eroare la alocare nod\n");
        perror(NULL);
        exit(-1);
    }
    e->cheie = cheie;
    e->stanga=e->dreapta=NULL;
    return e;
}

void appendBinar(node *arbore, int cheieFiu, int cheieParinte, Pozitie poz) {
    if (arbore->cheie==cheieParinte) {
        if (poz == STANGA) {
            arbore->stanga=nou(cheieFiu);
        }
        else {
            arbore->dreapta=nou(cheieFiu);
        }
    }
    else {
        if (arbore->stanga!=NULL) {
            appendBinar(arbore->stanga,cheieFiu,cheieParinte,poz);
        }
        if (arbore->dreapta!=NULL) {
            appendBinar(arbore->dreapta,cheieFiu,cheieParinte,poz);
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

void eliberare(node *arbore) {
    if (arbore == NULL) {
        return;
    }
    eliberare(arbore->stanga);
    eliberare(arbore->dreapta);
    free(arbore);
}

void transform2(Arbore2 *arbore1, node *arbore2, int start) {
    if (start==arbore1->size) {
        return;
    }
    if (arbore1->noduri[start].primFiu != -1) {
        appendBinar(arbore2, arbore1->noduri[start].primFiu,arbore1->noduri[start].cheie,STANGA);
        transform2(arbore1, arbore2, arbore1->noduri[start].primFiu);
    }
    if (arbore1->noduri[start].frateDreapta != -1) {
        appendBinar(arbore2, arbore1->noduri[start].frateDreapta,arbore1->noduri[start].cheie,DREAPTA);
        transform2(arbore1, arbore2, arbore1->noduri[start].frateDreapta);
    }
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
    //afisare1(arbore1);
    printf("Rsd1: ");
    rsd1(&arbore1, 0);
    printf("\nSrd1: ");
    srd1(&arbore1,0);
    printf("\nSdr1: ");
    sdr1(&arbore1,0);


    Arbore2 arbore2;
    arbore2Init(&arbore2, 10);
    transform1(&arbore1, &arbore2);

    printf("\nRsd2: ");
    rsd2(&arbore2, 0);
    printf("\nSrd2: ");
    srd2(&arbore2,0);
    printf("\nSdr2: ");
    sdr2(&arbore2,0);

    node *arbore=nou(arbore1.noduri[0].cheie);
    transform2(&arbore2, arbore, 0);

    printf("\nRsd3: ");
    rsd(arbore);

    eliberare(arbore);
    free(arbore1.noduri);
    free(arbore2.noduri);

    return 0;
}