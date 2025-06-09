#include <stdio.h>
#include <stdlib.h>
#include "arborib.h"

Pagina *radacina;


int main()
{
	int i, n = 18;

	radacina = NULL;
	for (i = 1; i <= n; i++)
		radacina = insereaza(radacina, i, NULL);

	printf("Arborele-B initial:\n");
	afisareSdr(radacina, 1);
	printf("\n\n");

	// for (i = 1; i <= n; i++)
	// {
	// 	printf("Dupa stergerea lui %d:\n", i);
	// 	radacina = suprima(radacina, i, NULL);
	// 	afisare(radacina, 1);
	// 	printf("\n\n");
	// }

	printf("S-a gasit elementul %d: %d\n", 4, cautare(radacina,4));

	return 0;
}