#include <stdio.h>
#include <stdlib.h>

typedef struct nod {
    int cheie;
    struct nod *urm;
}nod;

typedef struct {
    nod *prim;
    nod *ultim;
} Coada;

int **citire(const char *in, int *size) {
    FILE *fin=NULL;
    if ((fin=fopen(in,"r"))==NULL) {
        printf("Eroare la deschidere fisier\n");
        perror(NULL);
        exit(-1);
    }
    fscanf(fin,"%d",size);

    int **v=(int**)malloc(*size*sizeof(int*));
    if(v==NULL) {
        printf("Eroare la alocare matrice\n");
        perror(NULL);
        exit(-1);
    }
    for(int i=0;i<*size;i++) {
        v[i]=(int*)malloc(*size*sizeof(int));
        if(v[i]==NULL) {
            printf("Eroare la alocare rand\n");
            perror(NULL);
            exit(-1);
        }
        for(int j=0;j<*size;j++) {
            fscanf(fin,"%d",&v[i][j]);
        }
    }

    fclose(fin);
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

void coadaInit(Coada *coada) {
    coada->prim=NULL;
    coada->ultim=NULL;
}

nod *nou(int cheie) {
    nod *n=(nod*)malloc(sizeof(nod));
    if(n==NULL) {
        printf("Eroare la alocare nod\n");
        perror(NULL);
        exit(-1);
    }
    n->cheie = cheie;
    n->urm=NULL;
    return n;
}

void push(Coada *coada, int cheie) {
    if (coada->prim==NULL) {
        coada->prim=coada->ultim=nou(cheie);
    }
    else {
        nod *n=nou(cheie);
        coada->ultim->urm=n;
        coada->ultim=n;
    }

}

void pop(Coada *coada) {
    nod *aux=coada->prim->urm;
    free(coada->prim);
    coada->prim=aux;
}

void afisareCoada(Coada coada) {
    for (nod *n=coada.prim;n!=NULL;n=n->urm) {
        printf("%d ",n->cheie);
    }printf("\n");
}

void eliberareCoada(Coada *coada) {
    nod *n=coada->prim;
    while(n!=NULL) {
        nod *aux=n->urm;
        free(n);
        n=aux;
    }

}

void dfs(int **v, int size, int *vizitat, int start) {

    printf("%d ", start);
    vizitat[start]=1;
    for(int i=0;i<size;i++) {
        if(!vizitat[i] && v[start][i] != 0) {
            dfs(v,size,vizitat,i);
        }
    }
}

void bfs(Coada *coada, int **v, int size, int start) {
    int *vizitat=(int*)calloc(size, sizeof(int));
    vizitat[start]=1;
    int len=0;
    push(coada,start);
    Coada q;
    coadaInit(&q);
    push(&q,start);
    while(q.prim) {
        int aux=q.prim->cheie;
        pop(&q);

        for (int i=0;i<size;i++) {
            if(!vizitat[i] && v[aux][i] != 0) {
                push(&q,i);
                push(coada,i);
                vizitat[i]=1;
            }
        }
    }
}

int main(int argc, char **argv) {
    int **v=NULL;
    int size=0;
    v=citire(argv[1],&size);
    //afisare(v,size);

    int *vizitat=(int*)calloc(size, sizeof(int));
    //dfs(v,size,vizitat,0);
    Coada coada;
    coadaInit(&coada);
    bfs(&coada,v,size,0);
    afisareCoada(coada);
    eliberareCoada(&coada);

    free(vizitat);
    eliberare(v,size);
    return 0;
}