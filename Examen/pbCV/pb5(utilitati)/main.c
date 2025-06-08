#include <stdio.h>
#include <stdlib.h>

//djikstra

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

int **floyd(int **v, int size) {
    int **a=(int**)malloc(size*sizeof(int*));
    if(a==NULL) {
        printf("Erreur\n");
        perror("malloc");
        exit(1);
    }
    for(int i=0;i<size;i++) {
        a[i]=(int*)malloc(size*sizeof(int));
        if(a[i]==NULL) {
            printf("Erreur\n");
            perror("malloc linie");
            exit(1);
        }
        for(int j=0;j<size;j++) {
            if (i==j) {
                a[i][j]=0;
            }
            else if (v[i][j]==0) {
                a[i][j]=-1;
            }
            else {
                a[i][j]=v[i][j];
            }
        }
    }

    for (int k=0;k<size;k++) {
        for (int i=0;i<size;i++) {
            for (int j=0;j<size;j++) {
                if (a[i][k] != -1 && a[k][j] != -1 && a[i][k]+a[k][j] < a[i][j]) {
                    a[i][j]=a[i][k]+a[k][j];
                }
            }
        }
    }

    return a;
}

void printArray(int *v, int size) {
    for(int i=0;i<size;i++) {
        printf("%d ",v[i]);
    }printf("\n");
}

void djikstra(int **v, int size, int start) {
    int *drum=(int*)malloc(size*sizeof(int));
    int *vizitat=(int*)calloc(size,sizeof(int));
    int *d=(int*)malloc(size*sizeof(int));
    vizitat[start]=1;
    int len=0;
    d[0]=-1;
    drum[len++]=start;
    for(int i=0;i<size;i++) {
        if (v[start][i]!=0) {
            d[i]=v[start][i];
        }
        else {
            d[i]=-1;
        }
    }

    for (int i=1;i<size;i++) {
        int min=INT_MAX;
        int u=0;
        for (int j=1;j<size;j++) {
            if (d[j]<min && d[j]>0 && !vizitat[j]) {
                min=d[j];
                u=j;
            }
        }

        vizitat[u]=1;
        drum[len++]=u;

        for (int j=1;j<size;j++) {
            int flag=0;
            if (d[j]==-1 && v[u][j]!=0) {
                d[j]=v[u][j];
                flag=1;
            }
            if (v[u][j]!=0 && !vizitat[j]) {
                if (d[j]==-1 || flag || d[j]>d[u]+v[u][j]) {
                    d[j]=d[u]+v[u][j];
                }
            }
        }
        // printf("Costurile cand adaug %d:\n",u);
        // printArray(d,size);
    }
    printf("Costul pt apa a lui %d: %d\n",start,d[9]);
    printf("Costul pt electric a lui %d: %d\n",start,d[10]);
    printf("Costul pt gaz a lui %d: %d\n",start,d[11]);
    free(vizitat);
    free(d);
    free(drum);
}

void djikstraTotal(int **v, int size) {
    for (int i=0;i<size-3;i++) {
        djikstra(v,size,i);
    }
}

int main(int argc, char **argv) {
    int size=0;
    int **v=citire(&size,argv[1]);
    //afisare(v,size);

    djikstraTotal(v,size);

    eliberare(v,size);
    return 0;
}