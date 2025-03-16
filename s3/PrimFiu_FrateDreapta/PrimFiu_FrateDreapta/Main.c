#include "Arbore.h"
#include<stdio.h>




void parcurgerePreordine(TTree arbore, TNodeRef poz) {
	
	if (poz == 0)return;
	printf("%d ", arbore.nodes[poz].key);
	TNodeRef copil = arbore.nodes[poz].primFiu;

	
	while (copil != 0) {
		parcurgerePreordine(arbore, copil);
		copil = arbore.nodes[copil].frateDreapta;
		
	}

}

void parcurgereInordine(TTree arbore, TNodeRef poz) {
	
	TNodeRef copil = arbore.nodes[poz].primFiu;

	if (copil != 0) parcurgereInordine(arbore, copil);
	printf("%d ", poz);

	while ((copil=arbore.nodes[copil].frateDreapta) != 0) {
		parcurgereInordine(arbore, copil);
	}


}

void parcurgerePostordine(TTree arbore, TNodeRef poz) {
	TNodeRef copil = arbore.nodes[poz].primFiu;

	if (copil != 0) {
		parcurgerePostordine(arbore, copil);
	}

	while ((copil = arbore.nodes[copil].frateDreapta) != 0) {
		parcurgerePostordine(arbore, copil);
	}

	printf("%d ", poz);
}

void parcurg(TTree arbore) {
	
	printf("\nPreordine:");
	parcurgerePreordine(arbore, getRoot(arbore));
	printf("\nInordine:");
	parcurgereInordine(arbore, getRoot(arbore));
	printf("\nPostordine:");
	parcurgerePostordine(arbore, getRoot(arbore));
}

int main(int argc, char** argv) {
	TTree arbore = { 0,0 };
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
	while (fscanf(fin, "%d %d\n", &n, &m) == 2) {
		arbore = InsertNode(arbore, m, n);
	}

	printArray(arbore);
	parcurg(arbore);

	fclose(fin);
}