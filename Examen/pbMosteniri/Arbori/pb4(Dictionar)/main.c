#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TrieNode {
    struct TrieNode *parinte;
    struct TrieNode *copii[26];
    char litera;
    int index;
    int esteCuvant;
} TrieNode;

void initTrie(TrieNode *root) {
    root->parinte = NULL;
    root->litera = 0;
    root->index = 0;
    root->esteCuvant = 0;
    for (int i = 0; i < 26; i++) {
        root->copii[i] = NULL;
    }
}

TrieNode *newTrieNode(TrieNode *parinte, char litera, int index, int esteCuvant) {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    if (node == NULL) {
        printf("Erreur\n");
        perror(NULL);
        exit(1);
    }
    node->litera = litera;
    node->index = index;
    node->esteCuvant = esteCuvant;
    for (int i = 0; i < 26; i++) {
        node->copii[i] = NULL;
    }
    return node;
}

void append(TrieNode *root, const char *secventa, char litera, int index, int esteCuvant) {
    TrieNode *current = root;
    for (int i = 0; secventa[i]; i++) {
        int idx = secventa[i] - 'a';
        if (current->copii[idx] == NULL) {
            current->copii[idx] = newTrieNode(current, secventa[i], 0, 0);
        }
        current = current->copii[idx];
    }

    int idx = litera - 'a';
    if (current->copii[idx] == NULL) {
        current->copii[idx] = newTrieNode(current, litera, index, esteCuvant);
    }
}



void parcurgereRSD(TrieNode *nod) {
    if (nod == NULL) return;

    // R: procesez rădăcina (litera curentă)
    if (nod->parinte != NULL) { // evit să printez rădăcina goală
        printf("%c ", nod->litera);
    }

    // SD: parcurg toți copiii de la 'a' la 'z'
    for (int i = 0; i < 26; i++) {
        if (nod->copii[i] != NULL) {
            parcurgereRSD(nod->copii[i]);
        }
    }
}


int main(void) {
    TrieNode *root=NULL;

    root = newTrieNode(NULL, 'a', 0, 0);
    int start=0;
    append(root,'b',"a",1,0);
    //start=0;
    append(root,'c',"a",2,0);
    //start=0;
    append(root, 'a',"ab",3,0);
    append(root, 'z',"ac",4,0);

    parcurgereRSD(root);

    //printf("%c ", root->litera);

    free(root);
    return 0;
}