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

int check(int *v, int size) {
    for(int i=0;i<size;i++) {
        if(v[i]!=1) {
            return i;
        }
    }
}

void dfs(int **v, int size, int *vizitat, int start, int *lungime) {
    vizitat[start]=1;
    *lungime+=1;
    printf("%d ",start);
    for(int i=0;i<size;i++) {
        if(!vizitat[i] && v[start][i]!=0) {

            dfs(v,size,vizitat,i,lungime);

        }
    }
}

int nrCompConexe(int **v, int *vizitat, int size, int *lungimeMax) {
    int count=0;

    for (int i=0;i<size;i++) {
        if(vizitat[i]!=1) {
            int lungime=0;
            dfs(v,size,vizitat,i,&lungime);
            count++;
            if(lungime>*lungimeMax) {
                *lungimeMax=lungime;
            }
        }
    }
    return count;
}

int main(int argc, char **argv) {
    int size=0;
    int **v=citire(&size,argv[1]);
    int *vizitat=(int*)calloc(size,sizeof(int));

    int len=0;
    //dfs(v,size,vizitat,0);
    int lungimeMax=0;
    printf("\nnr de comp conexe:%d\n",nrCompConexe(v,vizitat,size,&lungimeMax));
    printf("Lungimea maxima:%d\n",lungimeMax);
    //afisare(v,size);
    eliberare(v,size);
    return 0;
}