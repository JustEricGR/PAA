#include <stdio.h>
#include <stdlib.h>
#define INF 1000000

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

int *prim(int **v, int size, int start) {
    //int *vizitat = (int*)calloc(size, sizeof(int));
    int *costuri = (int*)malloc(size * sizeof(int));
    int *drum = (int*)malloc(size * sizeof(int));
    int len=0;
    drum[len++]=start;



    for (int i=0;i<size;i++) {
        if (v[start][i] != 0) {
            costuri[i] = v[start][i];
        }
        else {
            costuri[i] = -1;
        }
    }
    costuri[start] = 0;

    for (int i = 1; i < size; i++) {
        int min=INT_MAX;
        int u=0;
        for (int j = 1; j < size; j++) {
            if (costuri[j] < min && costuri[j] > 0) {
                min = costuri[j];
                u = j;
            }
        }
        printf("Costurile cand adaug %d:\n",u);
        printArray(costuri,size);
        costuri[u] = 0;
        drum[len++] = u;


        for (int j = 1; j < size; j++) {
            if (v[u][j] != 0 && costuri[j] != 0) {
                if (costuri[j] > v[u][j] || costuri[j] == -1) {
                    costuri[j] = v[u][j];
                }
            }
        }

    }
    free(costuri);
    return drum;
}

int find(int *parent, int x) {
    if (parent[x]!=x) parent[x] = find(parent,parent[x]);
    return parent[x];
}

void unite(int *parent, int x, int y) {
    int rx = find(parent,x);
    int ry = find(parent,y);
    if (rx!=ry) parent[rx] = ry;
}

void kruskal(int **v, int size) {
    Arc *arcuri=(Arc*)malloc((size-1) * sizeof(Arc));
    int *parent=(int*)malloc(size * sizeof(int));

    for (int i=0;i<size;i++) {
        parent[i]=i;
    }

    int len=0;

    while (len<size-1) {
        int u=0,w=0;
        int min=INT_MAX;
        for (int i=0;i<size;i++) {
            for (int j=0;j<size;j++) {
                if (min>v[i][j] && v[i][j] > 0 && find(parent,i) != find(parent,j)) {
                    u=i;
                    w=j;
                    min=v[i][j];
                }
            }
        }
        arcuri[len].start=u;
        arcuri[len].end=w;
        unite(parent,u,w);
        v[u][w]=-1;
        v[w][u]=-1;
        len++;
    }

    for (int i=0;i<len;i++) {
        printf("%d - %d\n",arcuri[i].start,arcuri[i].end);
    }
}

int *djikstra(int **v, int size, int start) {
    int *drum=(int*)malloc(size * sizeof(int));
    int *costuri=(int*)malloc(size * sizeof(int));
    int *vizitat=(int*)calloc(size, sizeof(int));
    int len=0;

    drum[len++]=start;
    for (int i=0;i<size;i++) {
        if (v[start][i] != 0) {
            costuri[i]=v[start][i];
        }
        else {
            costuri[i]=-1;
        }
    }

    for (int i=1;i<size;i++) {
        int u=0;
        int min=INT_MAX;
        for (int j=1;j<size;j++) {
            if (costuri[j] < min && costuri[j] > 0 && !vizitat[j]) {
                u=j;
                min = costuri[j];
            }
        }
        drum[len++] = u;
        vizitat[u]=1;
        for (int j=1;j<size;j++) {
            if (costuri[j] == -1 && v[u][j] != 0 && !vizitat[j]) {
                costuri[j] = v[u][j]+costuri[u];
            }
            if (v[u][j] != 0 && !vizitat[j] && costuri[j]>costuri[u]+v[u][j]) {
                costuri[j]=costuri[u]+v[u][j];
            }
        }
        printf("Costurile cand adaug %d:\n",u);
        printArray(costuri,size);
    }
    free(costuri);
    free(vizitat);
    return drum;
}

int **floyd(int **v, int size) {
    int **a=(int**)malloc(size * sizeof(int*));
    if (a==NULL) {
        printf("Eroare la alocare matrice\n");
        perror(NULL);
        exit(-1);
    }
    for (int i=0;i<size;i++) {
        a[i]=(int*)malloc(size * sizeof(int));
        if (a[i]==NULL) {
            printf("Eroare la alocare linie\n");
            perror(NULL);
            exit(-1);
        }
        for (int j=0;j<size;j++) {
            if (i==j) a[i][j]=0;
            else if (v[i][j]==0) a[i][j]=INF;
            else a[i][j]=v[i][j];
        }
    }

    for (int k=0;k<size;k++) {
        for (int i=0;i<size;i++) {
            for (int j=0;j<size;j++) {
                if (a[i][k] + a[k][j] < a[i][j]) {
                    a[i][j]=a[i][k]+a[k][j];
                }
            }
        }
    }

    return a;
}

int main(int argc, char **argv) {
    int **v=NULL;
    int size=0;
    v=citire(&size, argv[1]);
    //afisare(v, size);
    //int *drum=djikstra(v, size, 0);
    int **a=floyd(v, size);
    //kruskal(v, size);
    //printArray(drum, size);
    afisare(a,size);
    eliberare(v, size);
    eliberare(a,size);
    //free(drum);
    return 0;
}