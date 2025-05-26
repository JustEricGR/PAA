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

int** floyd(int **a, int size) {
	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (a[i][k] + a[k][j] < a[i][j] && (a[i][k] + a[k][j] != 0)) {
					a[i][j] = a[i][k] + a[k][j];
				}
			}
		}
	}
	return a;
}

int main(int argc, char** argv) {
	int** v = NULL;
	int size = 0;
	v = citire(&size, argv[1]);
	afisare(v, size);
	printf("Dupa floyd:\n");
	
	v = floyd(v, size);
	afisare(v, size);

	eliberare(v, size);
}