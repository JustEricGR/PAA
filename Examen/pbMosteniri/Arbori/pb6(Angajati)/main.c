#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//folosesc 3 arbori, unul generalizat cu parinte-cheie(cerinta)
//il transform in prim fiu frate dreapta pt ca e mult mai usor la transformarea in binar

typedef struct {
    int ID;
    char nume[30];
    int parentID;
    int index;
} nodType1;

typedef struct {
    int size;
    nodType1* angajati;
}arboreType1;

typedef struct {
    int ID;
    char nume[30];
    int primFiu;
    int frateDreapta;
    int index;
} nodType2;

typedef struct {
    int size;
    nodType2* angajati;
}arboreType2;

typedef struct Binar{
    int ID;
    char nume[30];
    struct Binar* stanga;
    struct Binar* dreapta;
}Binar;

typedef enum {
    STANGA,
    DREAPTA
}Pozitie;

void arbore1Init(arboreType1 *arbore, int size) {
    arbore->size = size;
    arbore->angajati = (nodType1*) malloc(size * sizeof(nodType1));
}

void appendArbore1(arboreType1 *arbore, int *index, int ID, int parentID ,char nume[30]) {
    arbore->angajati[*index].index=*index;
    arbore->angajati[*index].ID = ID;
    strcpy(arbore->angajati[*index].nume, nume);
    arbore->angajati[*index].parentID = parentID;
    *index+=1;
}

void afisareArbore1(arboreType1 *arbore) {
    printf("Index:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ",arbore->angajati[i].index);
    }printf("\n");

    printf("ID:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ",arbore->angajati[i].ID);
    }printf("\n");

    printf("ParentID:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ",arbore->angajati[i].parentID);
    }printf("\n");
}

void initArbore2(arboreType2 *arbore, int size) {
    arbore->size = size;
    arbore->angajati = (nodType2*) malloc(size * sizeof(nodType2));
}

void appendArbore2(arboreType2 *arbore, int *index, int ID, int primFiu, int frateDreapta ,char nume[30]) {
    arbore->angajati[*index].index=*index;
    arbore->angajati[*index].ID = ID;
    strcpy(arbore->angajati[*index].nume, nume);
    arbore->angajati[*index].primFiu = primFiu;
    arbore->angajati[*index].frateDreapta = frateDreapta;
    *index+=1;
}

void afisareArbore2(arboreType2 *arbore) {
    printf("Index:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ",arbore->angajati[i].index);
    }printf("\n");

    printf("ID:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ",arbore->angajati[i].ID);
    }printf("\n");

    printf("PrimFiu:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ",arbore->angajati[i].primFiu);
    }printf("\n");

    printf("FrateDreapta:\n");
    for (int i = 0; i < arbore->size; i++) {
        printf("%d ",arbore->angajati[i].frateDreapta);
    }
}

int check(arboreType2 *arbore) {
    for (int i = 0; i < arbore->size; i++) {
        if (arbore->angajati[i].primFiu == 0 || arbore->angajati[i].frateDreapta == 0) {
            return 0;
        }
    }
    return 1;
}

void transformare1(arboreType1 *arbore1, arboreType2 *arbore2) {

    for (int i = 0; i < arbore1->size; i++) {
        arbore2->angajati[i].index=arbore1->angajati[i].index;
        arbore2->angajati[i].ID = arbore1->angajati[i].ID;
        arbore2->angajati[i].primFiu=0;
        arbore2->angajati[i].frateDreapta=0;
    }
    arbore2->angajati[0].frateDreapta=-1;
    for (int i = 0; i < arbore1->size; i++) {
        int found=0;

        for (int j = i+1; j < arbore1->size; j++) {
            if (check(arbore2))break;
            if (arbore1->angajati[i].ID == arbore1->angajati[j].parentID) {
                found=1;
                arbore2->angajati[i].primFiu=arbore1->angajati[j].ID;
                int found1=0;
                int ultimFrate=j;
                for (int k = j+1; k < arbore1->size; k++) {
                    if (arbore1->angajati[i].ID == arbore1->angajati[k].parentID ) {
                        arbore2->angajati[ultimFrate].frateDreapta=arbore1->angajati[k].ID;
                        found1=1;
                        ultimFrate=k;

                    }



                }
                if (!found1) {
                    arbore2->angajati[ultimFrate].frateDreapta=-1;
                }
                else
                    break;
            }
        }
        if (!found) {
            arbore2->angajati[i].primFiu = -1;
        }
    }

    for (int i = 0; i < arbore2->size; i++) {
        if (arbore2->angajati[i].frateDreapta == 0) {
            arbore2->angajati[i].frateDreapta = -1;
        }
    }

}

Binar *nou(int ID, char nume[30]) {
    Binar *arbore = (Binar*) malloc(sizeof(Binar));
    if (arbore == NULL) {
        printf("Erreur\n");
        exit(1);
    }
    arbore->ID = ID;
    strcpy(arbore->nume, nume);
    arbore->stanga=NULL;
    arbore->dreapta=NULL;
    return arbore;
}

void appendBinar(Binar *arbore, int ID, char nume[30], int parentID, Pozitie poz) {
    if (arbore==NULL) return;
    if (arbore->ID == parentID) {
        if (poz == STANGA) {
            arbore->stanga = nou(ID, nume);
        }
        else if (poz == DREAPTA) {
            arbore->dreapta = nou(ID, nume);
        }
    }
    else {
        appendBinar(arbore->stanga, ID, nume, parentID, poz);
        appendBinar(arbore->dreapta, ID, nume, parentID, poz);
    }
}

int getIndexByID(arboreType2 *arbore, int ID) {
    for (int i = 0; i < arbore->size; i++) {
        if (arbore->angajati[i].ID == ID) {
            return i;
        }
    }
    return -1;
}


void transformare2(Binar *arbore1, arboreType2 *arbore2, int start) {
    if (start==arbore2->size) return;
    int primFiuID = arbore2->angajati[start].primFiu;
    if (arbore2->angajati[start].primFiu != -1) {
        appendBinar(arbore1, arbore2->angajati[start].primFiu, arbore2->angajati[getIndexByID(arbore2,primFiuID)].nume, arbore2->angajati[start].ID, STANGA);
        transformare2(arbore1, arbore2, arbore2->angajati[start].primFiu);
    }
    if (arbore2->angajati[start].frateDreapta != -1) {
        appendBinar(arbore1, arbore2->angajati[start].frateDreapta, arbore2->angajati[getIndexByID(arbore2,primFiuID)].nume, arbore2->angajati[start].ID, DREAPTA);
        transformare2(arbore1, arbore2, arbore2->angajati[start].frateDreapta);
    }
}

void rsdBinar(Binar *arbore) {
    if (arbore==NULL) return;
    printf("%d ", arbore->ID);
    rsdBinar(arbore->stanga);
    rsdBinar(arbore->dreapta);
}

void rsdArbore1(arboreType1 *arbore, int start) {
    printf("%d ", arbore->angajati[start].ID);
    if (start==arbore->size-1) return;

    for (int i = 0; i < arbore->size; i++) {
        if (arbore->angajati[i].parentID == arbore->angajati[start].ID) {
            rsdArbore1(arbore, i);
        }
    }

}

void eliberare(Binar *arbore) {
    if (arbore==NULL) return;
    if (arbore->stanga == NULL && arbore->dreapta == NULL) {
        free(arbore);
    }
    else {
        eliberare(arbore->stanga);
        eliberare(arbore->dreapta);
    }
}

int main(void) {
    const char* nume[50] = {
        "Andrei", "Maria", "Ioana", "Alexandru", "Elena",
        "Stefan", "Gabriela", "Vlad", "Ana", "Mihai",
        "Daria", "Cristian", "Radu", "Irina", "George",
        "Alina", "Cosmin", "Larisa", "Paul", "Diana",
        "Ionut", "Roxana", "Florin", "Teodora", "David",
        "Bianca", "Robert", "Anca", "Lucian", "Andreea",
        "Victor", "Georgiana", "Daniel", "Delia", "Sebastian",
        "Alexandra", "Sorin", "Ilinca", "Eduard", "Camelia",
        "Denis", "Adriana", "Petru", "Monica", "Claudiu",
        "Carmen", "Razvan", "Lavinia", "Tudor", "Nicoleta"
    };

    arboreType1 arbore1;
    arbore1Init(&arbore1, 10);

    int index=0;
    appendArbore1(&arbore1, &index, 0, -1, nume[index]);
    appendArbore1(&arbore1, &index, 1, 0, nume[index]);
    appendArbore1(&arbore1, &index, 2, 0, nume[index]);
    appendArbore1(&arbore1, &index, 3, 0, nume[index]);
    appendArbore1(&arbore1, &index, 4, 1, nume[index]);
    appendArbore1(&arbore1, &index, 5, 1, nume[index]);
    appendArbore1(&arbore1, &index, 6, 2, nume[index]);
    appendArbore1(&arbore1, &index, 7, 3, nume[index]);
    appendArbore1(&arbore1, &index, 8, 3, nume[index]);
    appendArbore1(&arbore1, &index, 9, 3, nume[index]);
    //afisareArbore1(&arbore1);

    arboreType2 arbore2;
    initArbore2(&arbore2, arbore1.size);

    Binar *arbore3=nou(arbore1.angajati[0].ID, arbore1.angajati[0].nume);

    transformare1(&arbore1, &arbore2);

    int start=0;
    transformare2(arbore3, &arbore2, start);

    printf("Rsd binar: ");
    rsdBinar(arbore3);

    start=0;
    printf("\nRsd oarecare: ");
    rsdArbore1(&arbore1, start);

    //afisareArbore2(&arbore2);

    free(arbore1.angajati);
    free(arbore2.angajati);
    eliberare(arbore3);
    return 0;
}