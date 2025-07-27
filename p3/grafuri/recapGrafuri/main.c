#include <stdio.h>
#include <stdlib.h>

typedef struct nod {
    int cheie;
    struct nod *urm;
}nod;

typedef struct {
    nod *prim;
    nod *ultim;
}Coada;

void coadaInit(Coada *coada) {
    coada->prim = NULL;
    coada->ultim = NULL;
}

nod *nou(int cheie) {
    nod *e=(nod *)malloc(sizeof(nod));
    if (e==NULL) {
        printf("Eroare alocare nod\n");
        perror("Erreur");
        exit(-1);
    }
    e->cheie = cheie;
    e->urm=NULL;
    return e;
}

void push(Coada *coada, int cheie) {
    nod *aux=nou(cheie);
    if (coada->prim==NULL) {
        coada->prim=aux;
        coada->ultim=aux;
    }
    else {
        coada->ultim->urm=aux;
        coada->ultim=aux;
    }
}

void pop(Coada *coada) {
    nod *aux=coada->prim->urm;
    free(coada->prim);
    coada->prim=aux;
}

void afisareCoada(Coada coada) {
    for (nod *aux=coada.prim; aux!=NULL; aux=aux->urm) {
        printf("%d ",aux->cheie);
    }printf("\n");
}

void eliberareCoada(Coada *coada) {

    while (coada->prim!=NULL) {
        nod *aux=coada->prim->urm;
        free(coada->prim);
        coada->prim=aux;
    }
}

int **citire(const char *in, int *size) {
    FILE *f = fopen(in, "r");
    fscanf(f, "%d", size);

    int **v=(int**)malloc(*size*sizeof(int*));
    if(v==NULL) {
        printf("Eroare alocare matrice\n");
        perror("Erreur");
        exit(-1);
    }
    for(int i=0;i<*size;i++) {
        v[i]=(int*)malloc(*size*sizeof(int));
        if(v[i]==NULL) {
            printf("Eroare alocare rand\n");
            perror("Erreur");
            exit(-1);
        }

        for(int j=0;j<*size;j++) {
            fscanf(f, "%d", &v[i][j]);
        }
    }
    fclose(f);
    return v;
}

void afisare(int **v, int size) {
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            printf("%d ", v[i][j]);
        }printf("\n");
    }printf("\n");
}

void eliberare(int **v, int size) {
    for(int i=0;i<size;i++) {
        free(v[i]);
    }
    free(v);
}

void dfs(int **v, int size, int *vizitat, int start) {
    printf("%d ", start);
    vizitat[start]=1;
    for (int i=0;i<size;i++) {
        if (!vizitat[i] && v[start][i] == 1) {
            dfs(v,size,vizitat,i);
        }
    }

}

void bfs(Coada *coada, int **v, int size, int start) {
    int *vizitat=(int*)calloc(size, sizeof(int));
    push(coada,start);
    vizitat[start]=1;
    Coada q;
    coadaInit(&q);
    push(&q,start);

    while (q.prim != NULL) {
        int aux=q.prim->cheie;
        //printf("%d\n",aux);
        pop(&q);
        for (int i=0;i<size;i++) {
            if (!vizitat[i] && v[aux][i] == 1) {
                //printf("%d\n", i);
                push(&q,i);
                vizitat[i]=1;
                push(coada,i);
            }
        }
    }
}

int main(int argc, char **argv) {
    int **v=NULL;
    int size=0;

    v=citire(argv[1], &size);
    //afisare(v, size);
    int *vizitat=(int*)calloc(size, sizeof(int));
    //dfs(v, size, vizitat, 0);

    Coada coada;
    coadaInit(&coada);
    bfs(&coada, v, size, 0);
    afisareCoada(coada);

    eliberareCoada(&coada);

    eliberare(v, size);
    return 0;
}