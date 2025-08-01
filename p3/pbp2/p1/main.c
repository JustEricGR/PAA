#include <stdio.h>
#include <stdlib.h>
#define CHUNK 5

typedef struct {
    int cheie;
    int parinte;
}nod;

typedef struct {
    nod *noduri;
    int size;
} Arbore;



void citire(Arbore *arbore, const char *in) {
    FILE *fin=NULL;
    if ((fin=fopen(in,"r"))==NULL) {
        printf("Errore deschidere fisier\n");
        perror(NULL);
        exit(-1);
    }
    char cod[17]="";
    fscanf(fin,"%s",cod);
    int index=0, crt_size=CHUNK;
    arbore->noduri=(nod *)malloc(crt_size*sizeof(nod));
    arbore->size=0;
    while(!feof(fin)) {
        if (index>=crt_size) {
            crt_size+=CHUNK;
            arbore->noduri=(nod *)realloc(arbore->noduri,crt_size*sizeof(nod));
        }
        fscanf(fin,"%d,%d",&arbore->noduri[index].cheie,&arbore->noduri[index].parinte);
        index++;
    }
    arbore->size=index;
}

void rsd(Arbore *arbore, int start) {
    printf("%d ",start);
    for(int i=start;i<arbore->size;i++) {
        if (start == arbore->noduri[i].parinte) {
            rsd(arbore, arbore->noduri[i].cheie);
        }
    }
}

void afisare(Arbore *arbore) {
    printf("Chei:\n");
    for(int i=0;i<arbore->size;i++) {
        printf("%d ",arbore->noduri[i].cheie);
    }printf("\n");

    printf("Parinti:\n");
    for(int i=0;i<arbore->size;i++) {
        printf("%d ",arbore->noduri[i].parinte);
    }printf("\n");
}

int check(Arbore arbore, int cheie) {
    for (int i=0;i<arbore.size;i++) {
        if (arbore.noduri[i].parinte == cheie) {
            return 1;
        }
    }
    return 0;
}

void calculareNivel(Arbore *arbore, int start, int stop, int crtLevel, int *level) {
    if (start == stop) {
        *level = crtLevel;
        return;
    }
    for (int i=0;i<arbore->size;i++) {
        if (arbore->noduri[i].parinte == start) {
            calculareNivel(arbore, arbore->noduri[i].cheie, stop, crtLevel+1, level);
        }
    }
}

void commandChain(Arbore *arbore, int start, int stop) {
    if (start == stop) {
        return;
    }
    printf("%d ",start);
    for (int i=0;i<arbore->size;i++) {
        if (arbore->noduri[i].parinte == start) {
            commandChain(arbore, arbore->noduri[i].cheie, stop);
        }
    }
}

void calculFinal(Arbore *arbore) {
    for (int i=0;i<arbore->size;i++) {
        int crtLevel=0;
        int level=0;
        calculareNivel(arbore, 1, arbore->noduri[i].cheie, crtLevel, &level);
        printf("Nivel pt nodul %d: %d\n", arbore->noduri[i].cheie, level);
    }
}

int main(int argc, char **argv) {
    Arbore arbore;
    citire(&arbore,argv[1]);

    afisare(&arbore);
    printf("\nRsd: ");
    rsd(&arbore,1);

    int level=0;
    int final=0;
    calculFinal(&arbore);
    commandChain(&arbore, 1, 2);
    free(arbore.noduri);
    return 0;
}