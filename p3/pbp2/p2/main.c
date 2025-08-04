#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **citire(const char *in, int *size) {
    FILE *fin=NULL;
    if ((fin=fopen(in,"r"))==NULL) {
        printf("Eroare la deschidere\n");
        perror("fopen");
        exit(-1);
    }
    fscanf(fin,"%d",size);
    int **v=(int**)malloc(*size*sizeof(int*));
    for (int i=0;i<*size;i++) {
        v[i]=(int*)malloc(*size*sizeof(int));
        if (v[i]==NULL) {
            printf("Eroare la memoria\n");
            perror("calloc");
            exit(-1);
        }
        memset(v[i],0,*size*sizeof(int));
    }
    while (!feof(fin)) {
        int i=0,j=0;
        int cost=0;
        fscanf(fin,"%d%d%d",&i,&j,&cost);

        v[i][j]=cost;
        v[j][i]=cost;
    }
    fclose(fin);
    return v;
}

void afisare(int **v, int size) {
    for (int i=0;i<size;i++) {
        for (int j=0;j<size;j++) {
            printf("%d ",v[i][j]);
        }printf("\n");
    }printf("\n");
}

void eliberare(int **v, int size) {
    for (int i=0;i<size;i++) {
        free(v[i]);
    }
    free(v);
}

void printArray(int *v, int size) {
    for (int i=0;i<size;i++) {
        printf("%d ",v[i]);
    }printf("\n");
}

int *prim(int **v, int size, int start, int *suma) {
    int *drum=(int*)malloc(size*sizeof(int));
    int *cost=(int*)malloc(size*sizeof(int));

    int len=0;
    drum[len++]=start;
    for (int i=0;i<size;i++) {
        if (v[start][i]!=0) {
            cost[i]=v[start][i];
        }
        else {
            cost[i]=-1;
        }
    }
    cost[start]=0;

    for (int i=1;i<size;i++) {
        int u=0;
        int min=INT_MAX;
        for (int j=1;j<size;j++) {
            if (cost[j]<min && cost[j]>0) {
                u=j;
                min=cost[j];
            }
        }
        *suma+=min;
        drum[len++]=u;
        cost[u]=0;

        printf("Costurile cand adaug %d:\n",u);
        printArray(cost,size);
        for (int j=1;j<size;j++) {
            if ((cost[j]>v[u][j] || cost[j]!=0) && v[u][j]!=0) {
                cost[j]=v[u][j];
            }
        }


    }
    free(cost);
    return drum;
}

int main(int argc, char **argv) {
    int **v=NULL;
    int size=0;
    v=citire(argv[1],&size);
    //afisare(v,size);
    int suma=0;
    int *drum=prim(v,size,0, &suma);
    printArray(drum,size);
    printf("Cost total: %d\n",suma);

    free(drum);
    eliberare(v,size);
    return 0;
}