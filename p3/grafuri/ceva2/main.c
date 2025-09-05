#include <stdio.h>
#include <stdlib.h>

#define INF 10000

typedef struct {
    int start;
    int end;
}Arc;

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

void printArray(int *v, int size) {
    for(int i=0;i<size;i++) {
        printf("%d ",v[i]);
    }printf("\n");
}

int *prim(int **v, int size, int start) {
    int *drum=(int*)malloc(size*sizeof(int));
    int *cost=(int*)malloc(size*sizeof(int));
    for(int i=0;i<size;i++) {
        if (v[start][i] != 0) {
            cost[i]=v[start][i];
        }
        else {
            cost[i]=-1;
        }
    }
    int len=0;
    drum[len++]=start;
    cost[start]=0;
    for(int i=1;i<size;i++) {
        int u=0;
        int min=INT_MAX;
        for(int j=1;j<size;j++) {
            if(cost[j]<min && cost[j]>0) {
                u=j;
                min=cost[j];
            }
        }
        drum[len++]=u;
        cost[u]=0;
        for (int j=1;j<size;j++) {
            if (cost[j]!=0 && v[u][j] && (v[u][j]<cost[j] || cost[j] == -1)) {
                cost[j]=v[u][j];
            }
        }
        printf("costurile cand adaug: %d\n",u);
        printArray(cost,size);

    }
    free(cost);
    return drum;
}

int find(int *parent, int x) {
    if (parent[x]!=x)parent[x]=find(parent,parent[x]);
    return parent[x];
}

void unite(int *parent, int x, int y) {
    int rx=find(parent,x);
    int ry=find(parent,y);
    if(rx!=ry) {
        parent[rx]=ry;
    }
}

void kruskall(int **v, int size) {
    Arc *arcuri=(Arc*)malloc((size-1)*sizeof(Arc));
    int *parent=(int*)malloc(size*sizeof(int));

    for(int i=0;i<size;i++) {
        parent[i]=i;
    }
    int len=0;

    while (len<size-1) {
        int min=INT_MAX;
        int u=0,w=0;
        for (int i=0;i<size;i++) {
            for (int j=0;j<size;j++) {
                if (v[i][j]>0 && v[i][j]<min && find(parent,i) != find(parent,j)) {
                    min=v[i][j];
                    u=i;
                    w=j;
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
    int *drum=(int*)malloc(size*sizeof(int));
    int *vizitat=(int*)calloc(size,sizeof(int));
    int *cost=(int*)malloc(size*sizeof(int));
    int len=0;
    for(int i=0;i<size;i++) {
        if (v[start][i]!=0) {
            cost[i]=v[start][i];
        }
        else {
            cost[i]=-1;
        }
    }
    drum[len++]=start;
    cost[start]=0;
    vizitat[start]=1;
    for(int i=1;i<size;i++) {
        int min=INT_MAX;
        int u=0;
        for(int j=1;j<size;j++) {
            if (cost[j] > 0 && cost[j] < min && !vizitat[j]) {
                min=cost[j];
                u=j;
            }
        }
        drum[len++]=u;
        vizitat[u]=1;
        for (int j=1;j<size;j++) {
            if (cost[j] == -1 && v[u][j] != 0) {
                cost[j]=v[u][j]+cost[u];
            }
            if (!vizitat[j] && cost[j] > cost[u] + v[u][j] && v[u][j] != 0) {
                cost[j]=cost[u] + v[u][j];
            }
        }
        printf("costurile cand adaug: %d\n",u);
        printArray(cost,size);
    }
    free(vizitat);
    free(cost);
    return drum;
}

int **floyd(int **v, int size) {
    int **a=(int**)malloc(size*sizeof(int*));
    for(int i=0;i<size;i++) {
        a[i]=(int*)malloc(size*sizeof(int));
    }
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            if (i==j) {
                a[i][j]=0;
            }
            else if (v[i][j]==0) {
                a[i][j]=INF;
            }
            else {
                a[i][j]=v[i][j];
            }
        }
    }

    for (int k=0;k<size;k++) {
        for (int i=0;i<size;i++) {
            for (int j=0;j<size;j++) {
                if (a[i][k]+a[k][j]<a[i][j]) {
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
    v=citire(&size,argv[1]);
    //afisare(v,size);
    // int *drum=djikstra(v,size,0);
    // printArray(drum,size);
    // free(drum);
    int **a=floyd(v,size);
    afisare(a,size);
    //kruskall(v,size);
    eliberare(v,size);
    return 0;
}