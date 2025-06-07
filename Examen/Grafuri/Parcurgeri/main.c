#include <stdio.h>
#include <stdlib.h>

typedef struct nod {
    struct nod *urm;
    int cheie;
}nod;

typedef struct {
    nod *prim;
    nod *ultim;
}Coada;

int **citire(int *size, const char *in) {
    FILE *fin=NULL;
    if ((fin=fopen(in,"r"))==NULL) {
        printf("Erreur\n");
        perror("fopen");
        exit(1);
    }
    fscanf(fin,"%d",size);
    int **v=(int**)malloc(*size*sizeof(int*));
    if(v==NULL) {
        printf("Erreur\n");
        perror("malloc");
        exit(1);
    }
    for(int i=0;i<*size;i++) {
        v[i]=(int*)malloc(*size*sizeof(int));
        if(v[i]==NULL) {
            printf("Erreur\n");
            perror("malloc linie");
            exit(1);
        }
        for(int j=0;j<*size;j++) {
            fscanf(fin,"%d",&v[i][j]);
        }
    }
    return v;
}

void afisare(int **v, int size) {
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            printf("%d ",v[i][j]);
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
    printf("%d ",start);
    vizitat[start]=1;
    for(int i=0;i<size;i++) {
        if (v[start][i] != 0 && !vizitat[i]) {
            dfs(v,size,vizitat,i);
        }
    }
}

void coadaInit(Coada *coada) {
    coada->prim=NULL;
    coada->ultim=NULL;
}

nod *nod_nou(int cheie) {
    nod *n=malloc(sizeof(nod));
    if(n==NULL) {
        printf("Erreur\n");
        perror("malloc");
        exit(1);
    }
    n->cheie = cheie;
    n->urm=NULL;
    return n;
}

void push(Coada *coada, int cheie) {
    if (coada->prim==NULL) {
        coada->prim=coada->ultim=nod_nou(cheie);
    }
    else {
        nod *aux=nod_nou(cheie);
        coada->ultim->urm=aux;
        coada->ultim=aux;
    }
}

void pop(Coada *coada) {
    if (coada==NULL) {
        return;
    }
    nod *aux=coada->prim->urm;
    free(coada->prim);
    coada->prim=aux;
}

void afisareCoada(Coada coada) {
    for (nod *c=coada.prim; c!=NULL; c=c->urm) {
        printf("%d ",c->cheie);
    }
}

void eliberareCoada(Coada *coada) {
    nod *c=coada->prim;
    while(c!=NULL) {
        nod *aux=c->urm;
        free(c);
        c=aux;
    }
}

void bfs(Coada *rezultat, int **v, int size, int start, int *vizitat) {
    vizitat[start]=1;
    push(rezultat,start);
    Coada c;
    coadaInit(&c);
    push(&c,start);
    vizitat[start]=1;
    while (c.prim!=NULL) {
        start=c.prim->cheie;
        pop(&c);

        for(int i=0;i<size;i++) {
            if (v[start][i] != 0 && !vizitat[i]) {
                push(&c,i);
                push(rezultat,i);
                vizitat[i]=1;
            }
        }
    }
}


int main(int argc, char **argv) {
    int **v=NULL;
    int size=0;
    v=citire(&size,argv[1]);
    int *vizitat=(int*)calloc(size,sizeof(int));
    //afisare(v,size);
    //dfs(v,size,vizitat,0);

    Coada coada;
    coadaInit(&coada);
    bfs(&coada,v,size,0,vizitat);
    afisareCoada(coada);
    eliberareCoada(&coada);
    free(vizitat);
    eliberare(v,size);
    return 0;
}