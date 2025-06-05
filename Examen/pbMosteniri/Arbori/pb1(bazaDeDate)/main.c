#include <stdio.h>
#include <stdlib.h>
#include "arborib.h"
#include<time.h>

Pagina *radacina;




int main()
{

	const char* nume[50] = {
		"Andrei", "Maria", "Ioana", "Alexandru", "Elena",
		"Stefan", "Gabriela", "Vlad", "Ana", "Mihai",
		"Daria", "Cristian", "Radu", "Irina", "George",
		"Alina", "Cosmin", "Larisa", "Paul", "Diana",
		"Ionut", "Roxana", "Florin", "Teodora", "David",
		"Bianca", "Robert", "Anca", "Lucian", "Andreea",
		"Victor", "Georgiana", "Daniel", "Delia", "Sebastian",
		"Alexandra", "Sorin", "Ilinca", "Eduard", "Camelia",
		"Denis", "Adriana", "Petru", "Monica", "Claudiu",
		"Carmen", "Razvan", "Lavinia", "Tudor", "Nicoleta"
	};

	int i, n = 18;
	srand(time(NULL));
	radacina = NULL;
	for (i = 1; i <= n; i++)
		radacina = insereaza(radacina, rand()%1000, nume[rand()%50], NULL);

	printf("Introduceti o data: ");
	int data=0;
	scanf("%d",&data);
	printf("Arborele-B initial:\n");
	afisare(radacina, 1, data);
	printf("\n\n");

	// for (i = 1; i <= n; i++)
	// {
	// 	printf("Dupa stergerea lui %d:\n", i);
	// 	radacina = suprima(radacina, i, NULL);
	// 	afisare(radacina, 1);
	// 	printf("\n\n");
	// }

	return 0;
}