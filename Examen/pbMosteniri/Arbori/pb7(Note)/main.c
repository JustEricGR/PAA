#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//aleg un arbore binar ordonat ca sa am acces cat mai rapid cu complexitate O(log n) la id uri

#define LOCURI 10

typedef enum {
    RESPINS,
    ADMIS
}state;

typedef struct Student{
    int id;
    int nota;
    state status;
    struct Student* stanga;
    struct Student* dreapta;
} Student;

Student *nou(int id, int nota) {
    Student *s = malloc(sizeof(Student));
    if (s==NULL) {
        printf("Erreur\n");
        exit(1);
    }
    s->id = id;
    s->nota = nota;
    s->stanga = NULL;
    s->dreapta = NULL;
    return s;
}

void append(Student *arbore, int id, int nota, int cond) {
    if (arbore==NULL) {
        return;
    }
    if (arbore->id > id) {
        if (arbore->stanga==NULL) {

            arbore->stanga = nou(id, nota);
            if (cond) arbore->stanga->status = ADMIS;
            else arbore->stanga->status = RESPINS;
        }
        else {
            append(arbore->stanga, id, nota, cond);
        }
    }
    else {
        if (arbore->dreapta==NULL) {
            arbore->dreapta = nou(id, nota);
            if (cond) arbore->dreapta->status = ADMIS;
            else arbore->dreapta->status = RESPINS;
        }
        else {
            append(arbore->dreapta, id, nota, cond);
        }
    }
}

void afisareSrd(Student *arbore) {
    if (arbore==NULL) return;

    afisareSrd(arbore->stanga);
    printf("codStudent:%d - nota:%d\n",arbore->id,arbore->nota);
    afisareSrd(arbore->dreapta);
}

void eliberare(Student *arbore) {
    if (arbore == NULL) return;
    eliberare(arbore->stanga);
    eliberare(arbore->dreapta);
    free(arbore);
}


int verifCod(Student *arbore, int cod) {
    if (arbore==NULL) return 0;
    if (arbore->id == cod) return 1;
    if (cod < arbore->id)
        return verifCod(arbore->stanga, cod);
    else
        return verifCod(arbore->dreapta, cod);
}

Student *contestatie(Student *arbore, int codStudent, int notaNoua) {
    if (arbore==NULL) return arbore;
    if (arbore->id == codStudent) {
        arbore->nota = notaNoua;
        return arbore;
    }
    else {
        if (codStudent <= arbore->id) {
            return contestatie(arbore->stanga, codStudent, notaNoua);
        }
        else {
            return contestatie(arbore->dreapta, codStudent, notaNoua);
        }
    }
}

Student *parcurgere(Student* arbore, int* index, Student* buffer, int* size) {
    if (!arbore || *index >= 8 || *size <= 0) return arbore;

    parcurgere(arbore->stanga, index, buffer, size);

    if (*index < 8 && *size > 0) {
        buffer[*index].id = arbore->id;
        buffer[*index].nota = arbore->nota;
        buffer[*index].status = arbore->status;
        (*index)++;
        (*size)--;
    }

    parcurgere(arbore->dreapta, index, buffer, size);
}

Student* transmitere(Student* arbore, Student* rectorat, int* index, int* marker, int* size, int cond) {
    Student* buffer = malloc(sizeof(Student) * 8);
    Student* s = parcurgere(arbore, index, buffer, size);
    rectorat = nou(buffer[0].id, buffer[0].nota);
    for (int i = 1; i < *index; i++) {
        append(rectorat, buffer[i].id, buffer[i].nota,cond);
    }
    *marker = 0;
    free(buffer);
    while (*size > 0) {
        Student* buffer = malloc(sizeof(Student) * 8);
        *index = 0;
        parcurgere(s, index, buffer, size);



        // printf("\nAfisez din buffer (%d studenti):\n", *index);
        // for (int i = 0; i < *index; i++) {
        //     printf("codStudent:%d - nota:%d\n", buffer[i].id, buffer[i].nota);
        // }

        if (*marker == 1) {
            rectorat = nou(buffer[0].id, buffer[0].nota);
            for (int i = 1; i < *index; i++) {
                append(rectorat, buffer[i].id, buffer[i].nota,cond);
            }
            *marker = 0;
        } else {
            for (int i = 0; i < *index; i++) {
                append(rectorat, buffer[i].id, buffer[i].nota,cond);
            }
        }

        free(buffer);
    }

    return rectorat;
}

int main(void) {
    Student *arbore=nou(10,6);
    srand(time(NULL));
    int cod=0;
    int size=10;
    int admis=0;

    for (int i=0;i<size;i++) {
        int codStudent=rand()%100;
        if (verifCod(arbore,codStudent)) {
            i--;
            continue;
        }
        cod=codStudent;
        int notaNoua=rand()%10;
        int cond=0;

        if (notaNoua>5 && admis<LOCURI) {
            admis++;
            cond=1;
        }
        append(arbore,codStudent,notaNoua, cond);


    }
    size++;
    afisareSrd(arbore);
    Student *aux=contestatie(arbore, cod,6);
    printf("Am modificat nodul: %d %d",aux->id,aux->nota);
    printf("\nDupa modificare:\n");
    afisareSrd(arbore);

    int index=0,marker=1;
    Student *rectorat=NULL;
    rectorat=transmitere(arbore,rectorat,&index,&marker,&size,1);

    printf("\nRectorat:\n");
    afisareSrd(rectorat);

    eliberare(arbore);

    return 0;
}