#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//folosim un arbore binar

typedef enum {
    ECHIPA1,
    ECHIPA2
}Castigator;

typedef struct {
    int layer;
    int index;
}gameID;

typedef struct {
    int idEchipa;
    char nume[10];
    gameID *ID;
}Echipa;

typedef struct {
    Echipa echipa1;
    Echipa echipa2;
    Castigator castigator;
    gameID ID;
}Meci;

typedef struct {
    Meci *games;
    int layer;
}Meciuri;

int randomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void afisareMeciuri(Meciuri *meciuri) {
    for (int j=0;j<6;j++) {
        printf("Afisez meciurile de pe layer %d:\n",meciuri[j].layer);
        int size=(int)pow(2,5-meciuri[j].layer);
        for(int i=0;i<size;i++) {
            printf("%s - %s\t",meciuri[j].games[i].echipa1.nume,meciuri[j].games[i].echipa2.nume);
            if (meciuri[j].games[i].castigator == ECHIPA1) {
                printf("Castiga echipa %s\n",meciuri[j].games[i].echipa1.nume);
            }
            else {
                printf("Castiga echipa %s\n",meciuri[j].games[i].echipa2.nume);
            }
        }
    }

}

void tranzitii(Meciuri *meciuri) {
    int size=(int)pow(2,5-meciuri[0].layer);
    Echipa castigator;
    castigator.ID=(gameID*)malloc(6*sizeof(gameID));
    for (int i=0;i<6;i++) {

        int len=0;
        if (i==5) {
            if (meciuri[5].games[0].castigator==ECHIPA1) {

                strcpy(castigator.nume,meciuri[5].games[0].echipa1.nume);
                castigator.idEchipa=meciuri[5].games[0].echipa1.idEchipa;
                for (int i=0;i<6;i++) {
                    castigator.ID[i].layer=meciuri[5].games[0].echipa1.ID[i].layer;
                    castigator.ID[i].index=meciuri[5].games[0].echipa1.ID[i].index;
                }
                printf("Castiga campionatul %s\n",castigator.nume);
            }
            else {
                strcpy(castigator.nume,meciuri[5].games[0].echipa2.nume);
                castigator.idEchipa=meciuri[5].games[0].echipa2.idEchipa;
                for (int i=0;i<6;i++) {
                    castigator.ID[i].layer=meciuri[5].games[0].echipa2.ID[i].layer;
                    castigator.ID[i].index=meciuri[5].games[0].echipa2.ID[i].index;
                }
                printf("Castiga campionatul %s\n",castigator.nume);
            }

            break;
        }
        for (int j=0;j<size;j+=2) {
            if (meciuri[i].games[j].castigator == ECHIPA1) {
                meciuri[i+1].games[len].echipa1=meciuri[i].games[j].echipa1;
            }
            else {
                meciuri[i+1].games[len].echipa1=meciuri[i].games[j].echipa2;
            }
            if (meciuri[i].games[j+1].castigator == ECHIPA1) {
                meciuri[i+1].games[len].echipa2=meciuri[i].games[j+1].echipa1;
            }
            else {
                meciuri[i+1].games[len].echipa2=meciuri[i].games[j+1].echipa2;
            }
            meciuri[i+1].games[len].echipa1.ID[i+1].layer=meciuri[i+1].layer;
            meciuri[i+1].games[len].echipa1.ID[i+1].index=len;
            meciuri[i+1].games[len].echipa2.ID[i+1].layer=meciuri[i+1].layer;
            meciuri[i+1].games[len].echipa2.ID[i+1].index=len;
            meciuri[i+1].games[len].castigator=randomInt(0,1);
            len++;
            //printf("Am transferat echipe pana la %d\n",j);
        }
        size/=2;
    }

    //afisez adversarele castigatorului
    printf("Echipele invinse:\n");
    for (int j = 0; j < 6; j++) {
        int idx = castigator.ID[j].index;
        int layer = castigator.ID[j].layer;

        Meci meci = meciuri[layer].games[idx];

        if (strcmp(castigator.nume, meci.echipa1.nume) == 0) {
            printf("%s\t", meci.echipa2.nume);
        } else {
            printf("%s\t", meci.echipa1.nume);
        }
    }printf("\n");
}


int main(void) {
    Meciuri *meciuri=(Meciuri *)malloc(6*sizeof(Meciuri));
    for (int i=0;i<6;i++) {
        meciuri[i].games=(Meci *)malloc((int)pow(2,5-i)*sizeof(Meci));
        meciuri[i].layer=i;
    }

    char aux[10]="Echipa";
    srand(time(NULL));
    for (int i = 0; i < 64; i+=2) {
        Echipa echipa1;
        Echipa echipa2;
        echipa1.idEchipa = i;
        echipa2.idEchipa = i+1;
        sprintf(echipa1.nume, "%s%d", aux, i);
        sprintf(echipa2.nume, "%s%d", aux, i+1);
        echipa1.ID = (gameID*)malloc(7*sizeof(gameID));
        echipa2.ID = (gameID*)malloc(7*sizeof(gameID));
        echipa1.ID[0].layer = 0;
        echipa2.ID[0].layer = 0;
        echipa1.ID[0].index = i/2;
        echipa2.ID[0].index = i/2;

        meciuri[0].games[i/2].echipa1 = echipa1;
        meciuri[0].games[i/2].echipa2 = echipa2;
        meciuri[0].games[i/2].castigator = randomInt(0,1);
    }

    tranzitii(meciuri);
    afisareMeciuri(meciuri);
    return 0;
}
