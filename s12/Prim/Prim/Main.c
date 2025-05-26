#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#define IN "matrice.txt"

int** citire(int* size, const char* in) {
	FILE* fin = NULL;
	if ((fin = fopen(in, "r")) == NULL) {
		printf("Eroare la deschidere fisier\n");
		perror(NULL);
		exit(-1);
	}

	fscanf(fin, "%d", size);
	int** v = (int**)malloc(*size * sizeof(int*));
	if (v == NULL) {
		printf("Eroare alocare matrice\n");
		perror(NULL);
		exit(-1);
	}

	for (int i = 0; i < *size; i++) {
		v[i] = (int*)malloc(*size * sizeof(int));
		if (v[i] == NULL) {
			printf("Eroare la alocare linie\n");
			perror(NULL);
			exit(-1);
		}
		for (int j = 0; j < *size; j++) {
			if (fscanf(fin, "%d", &v[i][j]) != 1) {
				printf("Eroare la citirea elementului [%d][%d]\n", i, j);
			}
		}
	}

	return v;
}

void afisare(int** v, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", v[i][j]);
		}printf("\n");
	}
}

void eliberare(int** v, int size) {
	for (int i = 0; i < size; i++)
		free(v[i]);
	free(v);
}

void printArray(int* v, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", v[i]);
	}printf("\n");
}

int* prim(int** v, int size) {
	int* costmin = (int*)malloc(size * sizeof(int));
	int* drum = (int*)malloc(size * sizeof(int));
	int* apropiat = (int*)malloc(size * sizeof(int));
	int len = 0;

	costmin[0] = 0;
	drum[len++] = 0;
	//daca un nod este vizitat pun in vectorul de cod indicele lui pe 0
	//daca un nod nu este vizitat si pana la un moment dat nu s-a gasit niciun drum posibil catre el atunci pun -1


	for (int i = 1; i < size; i++) {
		if (v[0][i] > 0) {
			costmin[i] = v[0][i];
			apropiat[i] = 0;
		}
		else
			costmin[i] = -1;
	}

	for (int i = 1; i < size; i++) {
		int min = INT_MAX;
		int k = 0;
		for (int j = 1; j < size; j++) {
			if (costmin[j] < min && costmin[j] != -1 && costmin[j] != 0) {
				min = costmin[j];
				k = j;
			}
		}
		drum[len++] = k;
		costmin[k] = 0;
		printf("Am parcurs muchia %d - %d\n", apropiat[k], k);

		for (int j = 1; j < size; j++) {
			if (v[k][j] != 0) {
				if (v[k][j] < costmin[j] || costmin[j] == -1) {
					costmin[j] = v[k][j];
					apropiat[j] = k;
				}
			}
			
		}
		/*printf("Costuri minime cand se adauga %d\n", k);
		printArray(costmin, size);*/
	}
	free(apropiat);
	free(costmin);
	return drum;
}



int main(int argc, char** argv) {
	int** v = NULL;
	int size = 0;

	v = citire(&size, argv[1]);
	//afisare(v, size);

	int* drum = prim(v, size);
	printArray(drum, size);

	eliberare(v, size);
	//free(drum);
}