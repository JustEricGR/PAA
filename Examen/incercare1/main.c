#include <stdio.h>
#include <stdlib.h>

int **citire(int *size, const char *fileName) {
    FILE *fin=NULL;
    if ((fin=fopen(fileName, "r"))==NULL) {
        printf("Eroare la deschidere\n");
        perror(NULL);
        exit(-1);
    }

    fscanf(fin, "%d", size);

    int **v=(int **)malloc(*size*sizeof(int *));
    if (v==NULL) {
        printf("Eroare la alocare matrice\n");
        perror(NULL);
        exit(-1);
    }

    for (int i=0;i<*size;i++) {
        v[i]=(int *)malloc(*size*sizeof(int));
        if (v[i]==NULL) {
            printf("Eroare la alocare linie\n");
            perror(NULL);
            exit(-1);
        }
        for (int j=0;j<*size;j++) {
            fscanf(fin, "%d", &v[i][j]);
        }
    }

    return v;
}

void afisare(int** v, int size) {
    for (int i=0;i<size;i++) {
        for (int j=0;j<size;j++) {
            printf("%d ", v[i][j]);
        }printf("\n");
    }printf("\n");
}

void eliberare(int** v, int size) {
    for (int i=0;i<size;i++) free(v[i]);
    free(v);
}

void printArray(int *v, int size) {
    for (int i=0;i<size;i++) {
        printf("%d ", v[i]);
    }printf("\n");
}

void dfs(int **v, int size, int *vizitat, int *rez, int *len, int start) {
    vizitat[start] = 1;
    rez[*len] = start;
    *len+=1;
    for (int i=0;i<size;i++) {
        if (!vizitat[i] && v[i][start]!=0) {
            dfs(v, size, vizitat, rez , len, i);
        }
    }
}

int main(int argc, const char * argv[]) {
    int **v=NULL;

    int size=0;
    v=citire(&size,argv[1]);

    int *parcurgere=(int *)malloc(size * sizeof(int));
    int *vizitat=(int *)calloc(size, sizeof(int));
    int len=0;

    dfs(v,size,vizitat,parcurgere,&len,0);
    printArray(parcurgere,len);
    free(parcurgere);
    free(vizitat);
    //afisare(v,size);
    eliberare(v,size);
    return 0;
}