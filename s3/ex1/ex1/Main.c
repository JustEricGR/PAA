#include "Arbore.h"
#include <stdio.h>
#define CHUNK 10

TNode *citire(TNode* v, int* size, const char *input) {
	int index = 0;
	int crt_size = CHUNK;
	v = (TNode*)malloc(crt_size * sizeof(TNode));

	if (v == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}

	FILE* fin = NULL;
	if ((fin = fopen(input, "r")) == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}

	while (!feof(fin)) {
		if (index >= crt_size) {
			crt_size += CHUNK;
			v = (TNode*)realloc(v, sizeof(TNode));

		}
		fscanf(fin, "%hhu %hhu\n", &v[index].key, &v[index].parent);
		index++;
	}
	*size = index;

	return v;
}

void parcurgereInordine(TTree arbore, TNodeRef poz) {
	
	TNodeRef copil = firstChild(arbore, poz);

	
	if (copil != 0) parcurgereInordine(arbore, copil);
		
	printf("%d ", poz);
	while ((copil = rightSibling(arbore, copil)) != 0) {
		parcurgereInordine(arbore, copil);

	}
	
}

void parcurgerePostordine(TTree arbore, TNodeRef poz) {
	TNodeRef copil = firstChild(arbore, poz);

	if (copil != 0) {
		parcurgerePostordine(arbore, copil);
	}

	while ((copil = rightSibling(arbore, copil)) != 0) {
		parcurgerePostordine(arbore, copil);
	}
	
	printf("%d ", poz);
}

void parcurgerePreordine(TTree arbore, TNodeRef poz) {
	//TNodeRef radacina = getRoot(arbore);
	TNodeRef copil = firstChild(arbore, poz);

	printf("%d ", poz);
	//printNode(nodeByRef(arbore, poz), "");
	if (copil != 0) {
		parcurgerePreordine(arbore, copil);
	}
	while ((copil = rightSibling(arbore, copil)) != 0) {
		parcurgerePreordine(arbore, copil);
	}
	
}

void parcurg(TTree arbore) {
	printf("\nPreordine:");
	parcurgerePreordine(arbore, getRoot(arbore));
	printf("\nInordine:");
	parcurgereInordine(arbore, getRoot(arbore));
	printf("\nPostordine:");
	parcurgerePostordine(arbore, getRoot(arbore));
}

int main(int argc, char **argv) {
	TTree arbore;
	arbore = InitTree(arbore);

	int size = 0;
	/*TNode *noduri = NULL;
	noduri = citire(noduri, &size, argv[1]);*/

	FILE* fin = NULL;
	if ((fin = fopen(argv[1], "r")) == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	//arbore = InsertNode(arbore, 0, noduri[0].key);
	int n, m;
	while(fscanf(fin, "%d %d\n", &n, &m) == 2) {
		arbore = InsertNode(arbore, m, n);
	}

	printArray(arbore);
	parcurg(arbore);

}