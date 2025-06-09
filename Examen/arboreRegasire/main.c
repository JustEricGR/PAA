#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod {
    char c;
    struct nod *litere[26];
    int isWord;
}nod;

nod *nou(char c, int isWord) {
    nod *n = (nod *)malloc(sizeof(nod));
    n->c = c;
    for (int i = 0; i < 26; i++) {
        n->litere[i] = NULL;
    }
    n->isWord = isWord;
    return n;
}

void append(nod *arbore, char c, char secventa[20], int *start, int isWord) {
    if (arbore->c==secventa[*start] && *start==strlen(secventa)-1) {
        //arbore->litere[c-'a'] =
        arbore->litere[c-'a']=nou(c, isWord);
        *start=0;
    }
    else if (arbore->litere[secventa[*start]-'a']->c==secventa[*start]) {
        *start+=1;
        append(arbore->litere[secventa[*start]-'a'],c,secventa,start,isWord);
    }
}

void afisare(nod *n, char buffer[50], int *start) {
    //printf("%c ", n->c);
    buffer[*start]=n->c;
    for (int i = 0; i < 26; i++) {
        if (n->litere[i] != NULL) {
            afisare(n->litere[i],buffer,start);
        }
    }
}

int main(void) {
    nod *arbore=nou('a', 0);
    int start=0;
    append(arbore, 'b', "a" , &start,0);
    append(arbore, 'a', "a" , &start,0);
    append(arbore, 'z', "ab" , &start, 1);
    afisare(arbore);
    return 0;
}