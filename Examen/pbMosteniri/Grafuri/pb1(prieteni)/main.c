#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 9

typedef struct {
    int id;
    char nume[50];
    char gen; // 'M' sau 'F'
    char localitate[50];
    int index;
} Utilizator;

typedef struct nod {
    Utilizator utilizator;
    struct nod *urm;
}nod;

typedef struct {
    nod *prim;
    nod *ultim;
}Coada;

int **citire(int size, const char *in) {
    FILE *fin=NULL;
    if ((fin=fopen(in,"r"))==NULL) {
        printf("Erreur\n");
        perror("fopen");
        exit(1);
    }

    int **v=(int**)malloc(size*sizeof(int*));
    if(v==NULL) {
        printf("Erreur\n");
        perror("malloc");
        exit(1);
    }
    for(int i=0;i<size;i++) {
        v[i]=(int*)malloc(size*sizeof(int));
        if(v[i]==NULL) {
            printf("Erreur\n");
            perror("malloc linie");
            exit(1);
        }
        for(int j=0;j<size;j++) {
            fscanf(fin,"%d",&v[i][j]);
        }
    }
    fclose(fin);
    return v;
}

void afisare(int **v, int size, Utilizator *utilizator) {
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            if (v[i][j] != 0) {
                printf("%s(%d) e prieten cu %s(%d)\n", utilizator[i].nume, utilizator[i].index, utilizator[j].nume,
                       utilizator[j].index);
            }
        }
    }
}

void eliberare(int **v, int size) {
    for (int i=0;i<size;i++) {
        free(v[i]);
    }
    free(v);
}

void coadaInit(Coada *coada) {
    coada->prim=NULL;
    coada->ultim=NULL;
}

nod *nou(Utilizator utilizator) {
    nod *nou=(nod*)malloc(sizeof(nod));
    if(nou==NULL) {
        printf("Erreur\n");
        perror("malloc");
        exit(1);
    }
    nou->utilizator=utilizator;
    nou->urm=NULL;
    return nou;
}

void push(Coada *coada, Utilizator utilizator) {
    if (coada->prim==NULL) {
        coada->prim=coada->ultim=nou(utilizator);
    }
    else {
        nod *aux=nou(utilizator);
        coada->ultim->urm=aux;
        coada->ultim=aux;
    }
}

void pop(Coada *coada) {
    if (coada->prim==NULL) {
        free(coada);
    }
    else {
        nod *aux=coada->prim->urm;
        free(coada->prim);
        coada->prim=aux;
    }
}

void afisareCoada(Coada coada) {
    for (nod *c=coada.prim;c!=NULL;c=c->urm) {
        printf("%s(%d)\n",c->utilizator.nume,c->utilizator.index);
    }
}

void coadaEliberare(Coada *coada) {
    nod *c=coada->prim;
    while (c!=NULL) {
        nod *aux=c->urm;
        free(c);
        c=aux;
    }
}

void bfs(int **v, int size, Utilizator *utilizator, Utilizator *prieteni, int sizePrieteni, int **vizitat) {
    *vizitat[prieteni[0].index]=1;

}

void friends(int **v, int size, int id, Utilizator *utilizator) {
    int *vizitat=(int*)calloc(size,sizeof(int));
    Utilizator *prieteni=(Utilizator*)malloc(size*sizeof(Utilizator));

    int len=0;

    int start=0;
    for (int i=0;i<size;i++) {
        if (utilizator[i].id==id) {
            start=utilizator[i].index;
            break;
        }
    }
    vizitat[start]=1;
    for (int i=0;i<size;i++) {
        if (v[start][i] != 0) {
            prieteni[len++]=utilizator[i];
            vizitat[i]=1;
        }
    }


    Utilizator *rez=(Utilizator*)malloc(3*sizeof(Utilizator));
    int flag=0;
    while (flag<3) {

        for (int i=0;i<len;i++) {
            if (flag==3)break;
            int indexPrieten=prieteni[i].index;
            for (int j=0;j<size;j++) {
                if (!vizitat[j] && v[indexPrieten][j] != 0) {
                    rez[flag++]=utilizator[j];
                    vizitat[j]=1;
                }
            }
        }
    }


    for (int i=0;i<3;i++) {
        printf("%s(%d) e prieten cu %s(%d)\n", utilizator[start].nume, start, utilizator[i].nume,
                       utilizator[i].index);
    }

    free(vizitat);
    free(prieteni);

}

int main(int argc, char **argv) {
    Utilizator utilizatori[N] = {
        {1, "Ana Popescu", 'F', "Bucuresti", 0},
        {2, "Ion Ionescu", 'M', "Cluj", 1},
        {3, "Maria Vasilescu", 'F', "Iasi", 2},
        {4, "George Enescu", 'M', "Brasov", 3},
        {5, "Elena Georgescu", 'F', "Constanta", 4},
        {6, "Andrei Marinescu", 'M', "Timisoara", 5},
        {7, "Ioana Stan", 'F', "Oradea", 6},
        {8, "Vlad Iliescu", 'M', "Pitesti", 7},
        {9, "Cristina Dobre", 'F', "Sibiu", 8}

    };

    int **v=citire(N, argv[1]);

    //afisare(v, N, utilizatori);
    friends(v, N, 4, utilizatori);

    eliberare(v,N);
    return 0;
}
