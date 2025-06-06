#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nume[20];
    char email[20];
} Student;

typedef struct nod{
    struct nod *stanga;
    struct nod *dreapta;
    int ID;
    char numeCurs[30];
    char numeProf[20];
    int nrStudenti;
    Student *studenti;
} nod;

nod *nou(int ID, char numeCurs[30], char numeProf[20], Student *studenti, int size) {
    nod *nou = (nod *)malloc(sizeof(nod));
    if (nou == NULL) {
        printf("Erreur\n");
        exit(1);
    }
    nou->ID = ID;
    strcpy(nou->numeCurs, numeCurs);
    strcpy(nou->numeProf, numeProf);
    nou->studenti=(Student*)malloc(size*sizeof(Student));
    for (int i = 0; i < size; i++) {
        strcpy(nou->studenti[i].nume, studenti[i].nume);
        strcpy(nou->studenti[i].email, studenti[i].email);
    }
    nou->nrStudenti = size;
    nou->stanga = NULL;
    nou->dreapta = NULL;
    return nou;
}

void adaugaCurs(nod *arbore, int ID, char numeCurs[30], char numeProf[20], Student *studenti, int size) {
    if (ID < arbore->ID) {
        if (arbore->stanga == NULL) {
            arbore->stanga=nou(ID, numeCurs, numeProf, studenti, size);
        }
        else {
            adaugaCurs(arbore->stanga,ID, numeCurs, numeProf, studenti, size);
        }
    }
    else {
        if (arbore->dreapta == NULL) {
            arbore->dreapta = nou(ID, numeCurs, numeProf, studenti, size);
        }
        else {
            adaugaCurs(arbore->dreapta,ID, numeCurs, numeProf, studenti, size);
        }
    }
}

void afisareElement(nod *element) {
    printf("%d;  ", element->ID);
    printf("%s;  ", element->numeCurs);
    printf("%s;  ", element->numeProf);
    for (int i = 0; i < element->nrStudenti; i++) {
        printf("%s; ", element->studenti[i].nume);
        printf("%s; ", element->studenti[i].email);
    }printf("\n");
}

void listareCursuriDupaID(nod *arbore) {
    if (arbore == NULL) {
        return;
    }
    listareCursuriDupaID(arbore->stanga);
    afisareElement(arbore);
    listareCursuriDupaID(arbore->dreapta);
}


void eliberare(nod *arbore) {
    if (arbore==NULL)return;
    if (arbore->stanga == NULL && arbore->dreapta == NULL) {
        free(arbore->studenti);
        free(arbore);
    }
    else {
        eliberare(arbore->stanga);
        eliberare(arbore->dreapta);
    }

}


int main(void) {
    nod *radacina = NULL;

    // Grup 1 de studenți
    Student studenti1[] = {
        {"Ana", "ana@gmail.com"},
        {"Ion", "ion@yahoo.com"}
    };

    // Grup 2
    Student studenti2[] = {
        {"Maria", "maria@cs.ro"}
    };

    // Grup 3
    Student studenti3[] = {
        {"George", "geo@gmail.com"},
        {"Radu", "radu@yahoo.com"},
        {"Elena", "elena@upb.ro"}
    };

    // Grup 4
    Student studenti4[] = {
        {"Vlad", "vlad@unibuc.ro"},
        {"Simona", "simona@gmail.com"}
    };

    // Grup 5
    Student studenti5[] = {
        {"Dan", "dan@student.ro"}
    };

    // Adăugăm mai multe cursuri în arbore
    radacina=nou(101, "Structuri de date", "Popescu", studenti1, 2);
    adaugaCurs(radacina, 55, "Algoritmi", "Ionescu", studenti2, 1);
    adaugaCurs(radacina, 220, "Programare C", "Georgescu", studenti3, 3);
    adaugaCurs(radacina, 80, "Baze de date", "Dumitrescu", studenti4, 2);
    adaugaCurs(radacina, 150, "Retele", "Marinescu", studenti5, 1);

    printf("Cursuri (in ordine crescatoare dupa ID):\n");
    listareCursuriDupaID(radacina);

    eliberare(radacina);
    return 0;
}

