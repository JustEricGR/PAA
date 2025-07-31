#include <stdio.h>
#include <stdlib.h>
#define INF 100000

int** citire(int* nrMaxPermisiuni, int* size, const char* in) {
    FILE* fin = NULL;
    if ((fin = fopen(in, "r")) == NULL) {
        printf("Eroare la deschidere fisier\n");
        perror(NULL);
        exit(-1);
    }

    fscanf(fin, "%d", nrMaxPermisiuni);
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

int check(int **v, int size, int indice) {
    for (int i = 0; i < size; i++) {
        if (v[i][indice])return 1;
    }
    return 0;
}



void dfs(int **v, int size, int start, int stop, int *vizitat, int *drum) {
    vizitat[start]=1;

    if (start == stop) {
        *drum+=1;
        return;
    }

    printf("%d ", start);
    for (int i = start+1; i < size; i++) {
        if (v[i][start] != 0 && !vizitat[i]) {
            *drum+=1;

            dfs(v, size, i, stop, vizitat, drum);
        }
    }

}

//int permisiuni(int **v, int size, )

int **floyd_warshall(int** v, int size) {
    int **a=(int**)malloc(size * sizeof(int*));
    if (a==NULL) {
        printf("Eroare alocare matrice\n");
        perror(NULL);
        exit(-1);
    }
    for (int i = 0; i < size; i++) {
        a[i] = (int*)malloc(size * sizeof(int));
        if (a[i] == NULL) {
            printf("Eroare la alocare linie\n");
            perror(NULL);
            exit(-1);
        }
        for (int j = 0; j < size; j++) {
            if (i==j)a[i][j]=0;
            else if (v[i][j]==0)a[i][j]=INF;
            else {
                a[i][j]=v[i][j];
            }
        }
    }

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (a[i][k] + a[k][j] < a[i][j]) {
                    a[i][j]=a[i][k] + a[k][j];
                }
            }
        }
    }
    return a;
}

int main(int argc, char **argv) {
    int **v=NULL;
    int size=0, nrMaxPermisiuni=0;;

    v=citire(&nrMaxPermisiuni, &size, argv[1]);

    //afisare(v,size);
    int drum=0;
    int *vizitat=(int*)calloc(size, sizeof(int));
    // dfs(v, size, 0, 4, vizitat, &drum);
    // printf("\nnr permisiuni:%d\n", drum);
    int **a=NULL;
    a=floyd_warshall(v, size);
    afisare(a,size);
    eliberare(v,size);
    free(vizitat);
}