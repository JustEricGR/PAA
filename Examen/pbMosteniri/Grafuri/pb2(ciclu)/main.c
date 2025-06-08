#include <stdio.h>
#include <stdlib.h>


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


void dfs(int **v, int size, int *vizitat, int start, int current, int lungime, int *lungimeMax) {


    vizitat[current]=1;


    for(int i=0;i<size;i++) {
        if(v[current][i]!=0) {
            //printf("lungimeMax:%d\n ",*lungimeMax);
            //printf("i:%d - start:%d\n",i,start);
            if (lungime >= 3 && i==start) {
                if (lungime > *lungimeMax) {
                    *lungimeMax=lungime;

                }
            }
            else if (!vizitat[i]) {
                lungime+=1;
                dfs(v,size,vizitat,start,i,lungime,lungimeMax);
            }

        }
    }
    vizitat[current]=0;
}

int longest(int **v, int size) {

    int lungimeMax=0;

    for(int i=0;i<size;i++) {
        int *vizitat=(int*)calloc(size,sizeof(int));

        dfs(v,size,vizitat,i,i,0,&lungimeMax);
        free(vizitat);
    }
    return lungimeMax;
}

int main(int argc, char ** argv) {
    int size=0;
    int **v=citire(&size,argv[1]);
    //afisare(v,size);
    int lungimeMax=longest(v,size);

    printf("\nLungime:%d\n",lungimeMax);
    eliberare(v,size);
    return 0;
}