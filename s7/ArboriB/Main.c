#include <stdio.h>
#include <stdlib.h>
#include "arborib.h"
#define path "randomNumbers.txt"
#define CHUNK 100

Pagina *radacina;

void citire(int v[], int *size) {
	int crt_size = CHUNK;
	//v = (int*)malloc(crt_size * sizeof(int));

	FILE* fin = fopen(path, "r");
	int i = 0;
	while(fscanf(fin, "%d", &v[i]) == 1) {
		i++;
	}

	*size = i;
	fclose(fin);
}

void afisareVect(int v[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", v[i]);
		if (i % 10 == 0)printf("\n");
	}
}


int main()
{
	int i, n = 18;
	int scindari = 0;

	int v[10000];
	int size = 0;
	citire(v, &size);
	afisareVect(v, size);

	radacina = NULL;
	for (i = 1; i <= n; i++)
		radacina = insereaza(radacina, i, NULL, &scindari);

	printf("Arborele-B initial:\n");
	afisare(radacina, 1);
	printf("\n\n");
	printf("Nr scindari: %d\n\n", scindari);

	for (i = 1; i <= n; i++)
	{
		printf("Dupa stergerea lui %d:\n", i);
		radacina = suprima(radacina, i, NULL);
		afisare(radacina, 1);
		printf("\n\n");
	}

	return 0;
}