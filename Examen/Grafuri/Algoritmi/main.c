#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#define IN "matrice.txt"

typedef struct {
    int start;
    int end;
}Arc;

int** citire(int* size, const char* in) {
    FILE* fin = NULL;
    if ((fin = fopen(in, "r")) == NULL) {
        printf("Eroare la deschidere fisier\n");
        perror(NULL);
        exit(-1);
    }

    fscanf(fin, "%d", size);
    int** v = (int**)malloc(*size * sizeof(int*));
    if (v == NULL) {
        printf("Eroare alocare matrice\n");
        perror(NULL);
        exit(-1);
    }

    for (int i = 0; i < *size; i++) {
        v[i] = (int*)malloc(*size * sizeof(int));
        if (v[i] == NULL) {
            printf("Eroare la alocare linie\n");
            perror(NULL);
            exit(-1);
        }
        for (int j = 0; j < *size; j++) {
            if (fscanf(fin, "%d", &v[i][j]) != 1) {
                printf("Eroare la citirea elementului [%d][%d]\n", i, j);
            }
        }
    }

    return v;
}

void afisare(int** v, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", v[i][j]);
        }printf("\n");
    }
}

void eliberare(int** v, int size) {
    for (int i = 0; i < size; i++)
        free(v[i]);
    free(v);
}

void printArray(int* v, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", v[i]);
    }printf("\n");

}


int *prim(int **v, int size) {
    int *drum = (int*)malloc(size * sizeof(int));
    int *apropiat = (int*)malloc(size * sizeof(int));
    int *d=(int*)malloc(size * sizeof(int));
    //in d va fi -1 pt cele care nu au niciun drum si 0 pt cele vizitate
    int len=0;
    drum[len++]=0;
    d[0]=0;
    for (int i = 0; i < size; i++) {
        if (v[0][i]!=0) {
            d[i]=v[0][i];
            apropiat[i]=0;
        }
        else {
            d[i]=-1;
        }
    }

    for (int i=1;i<size;i++) {
        int min=INT_MAX;
        int u=0;
        for (int j=1;j<size;j++) {
            if (d[j]<min && d[j]>0) {
                min=d[j];
                u=j;
            }
        }
        drum[len++]=u;
        d[u]=0;

        printf("Am adaugat arcul: %d - %d\n",apropiat[u],u);

        for (int j=1;j<size;j++) {
            if (v[u][j] != 0 && d[j] != 0) {
                if (d[j] == -1 || d[j] > v[u][j]) {
                    d[j]=v[u][j];
                    apropiat[j]=u;
                }
            }
        }

    }

    free(d);
    free(apropiat);
    return drum;
}

int find(int *parent, int x) {
    if (parent[x] != x) parent[x] = find(parent, parent[x]);
    return parent[x];
}

void unite(int *parent, int x, int y) {
    int rx=find(parent, x);
    int ry=find(parent, y);
    if (rx!=ry) {
        parent[rx]=ry;
    }
}


void kruskal(int **v, int size) {
    Arc *arcuri=(Arc*)malloc((size-1) * sizeof(Arc));
    int *parent=(int*)malloc(size * sizeof(int));

    int len=0;
    for (int i = 0; i < size; i++) {
        parent[i]=i;
    }

    while (len < size-1) {
        int min=INT_MAX;
        int u=0;
        int w=0;
        for (int i=0;i<size;i++) {
            for (int j=0;j<size;j++) {
                if (v[i][j]>0 && v[i][j] < min && find(parent, i) != find(parent, j)) {
                    min=v[i][j];
                    u=i;
                    w=j;
                }
            }
        }

        v[u][w]=-1;
        v[w][u]=-1;
        unite(parent, u, w);
        arcuri[len].start=u;
        arcuri[len].end=w;
        len++;
    }
    for (int i=0;i<len;i++) {
        printf("%d - %d\n",arcuri[i].start,arcuri[i].end);
    }

}


int *djikstra(int **v, int size) {
    int *drum=(int*)malloc(size * sizeof(int));
    int *vizitat=(int*)calloc(size, sizeof(int));
    int *d=(int*)malloc(size * sizeof(int));
    int len=0;
    drum[len++]=0;
    d[0]=0;
    vizitat[len]=0;
    for (int i=0;i<size;i++) {
        if (v[0][i] != 0) {
            d[i]=v[0][i];
        }
        else {
            d[i]=-1;
        }
    }

    for (int i=1;i<size;i++) {
        int min=INT_MAX;
        int u=0;
        for (int j=1;j<size;j++) {
            if (min>d[j] && !vizitat[j] && d[j] > 0) {
                min=d[j];
                u=j;
            }
        }
        drum[len++]=u;
        vizitat[u]=1;

        for (int j=1;j<size;j++) {
            int flag=0;
            if (!vizitat[j] && d[j] == -1 && v[u][j] != 0) {
                d[j]=v[u][j];
                flag=1;
            }
            if (!vizitat[j] && v[u][j] != 0) {
                if (flag || d[j]>v[u][j]+d[u]) {
                    d[j]=v[u][j]+d[u];
                }
            }
        }
        printf("Distantele cand adaug %d\n",u);
        printArray(d,size);
    }
    free(d);
    free(vizitat);
    return drum;
}

int **floyd(int **v, int size) {
    int **a=(int**)malloc(size * sizeof(int*));
    if (a == NULL) {
        printf("Errore alocare matrice\n");
        exit(-1);
    }
    for (int i = 0; i < size; i++) {
        a[i]=(int*)malloc(size * sizeof(int));
        if (a[i] == NULL) {
            printf("Eroare la alocare linie\n");
            perror(NULL);
            exit(-1);
        }
        for (int j = 0; j < size; j++) {
            if (v[i][j]!=0)
                a[i][j]=v[i][j];
            else if (i==j) {
                a[i][j]=0;
            }
            else {
                a[i][j]=-1;
            }
        }
    }

    for (int k=0;k<size;k++) {
        for (int i=0;i<size;i++) {
            for (int j=0;j<size;j++) {
                if (a[i][k]!=-1 && a[k][j]!=-1 && a[i][k]+a[k][j] < a[i][j]) {
                    a[i][j]=a[i][k]+a[k][j];
                }
            }
        }
    }

    return a;
}

int main(int argc, char** argv) {
    int** v = NULL;
    int size = 0;
    v = citire(&size, argv[1]);
    //afisare(v, size);

    // int *drum = djikstra(v, size);
    // printArray(drum, size);

    //kruskal(v,size);
    //free(drum);
    int **a=floyd(v, size);
    afisare(a, size);
    eliberare(a, size);
    eliberare(v, size);
}