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
	}
	printf("\n");
}

int* prim(int** v, int size) {
	int* drum = (int*)malloc(size * sizeof(int));
	int* costmin = (int*)malloc(size * sizeof(int));
	int* apropiat = (int*)malloc(size * sizeof(int));

	int len = 0;
	drum[len++] = 0;
	//0 vizitat; -1 fara drum curent
	costmin[0] = 0;

	for (int i = 1; i < size; i++) {
		if (v[0][i] != 0) {
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
			if (costmin[j] < min && costmin[j]>0) {
				min = costmin[j];
				k = j;
			}
		}

		drum[len++] = k;
		costmin[k] = 0;

		//recalculam distantele

		printf("Am adaugat muchia %d - %d\n", apropiat[k], k);

		for (int j = 1; j < size; j++) {
			if (v[k][j] != 0) {
				if (v[k][j] < costmin[j] || costmin[j] == -1) {
					costmin[j] = v[k][j];
					apropiat[j] = k;
				}
			}
		}

		//printf("Costurile minime dupa adaugarea %d\n", k);
		//printArray(costmin, size);
	}

	free(costmin);
	free(apropiat);
	return drum;
}

int* djikstra(int** v, int size) {
	int* drum = (int*)malloc(size * sizeof(int));
	int* vizitat = (int*)calloc(size, sizeof(int));
	int* d = (int*)malloc(size * sizeof(int));
	int len = 0;
	drum[len++] = 0;
	vizitat[0] = 1;
	d[0] = 0;

	for (int i = 0; i < size; i++) {
		if (v[0][i] != 0)d[i] = v[0][i];
		else d[i] = -1;
	}

	for (int i = 1; i < size; i++) {
		int min = INT_MAX;
		int k = 0;

		for (int j = 1; j < size; j++) {
			if (min > d[j] && !vizitat[j] && d[j] != -1) {
				min = d[j];
				k = j;
			}
		}

		drum[len++] = k;
		vizitat[k] = 1;

		for (int j = 1; j < size; j++) {
			int flag = 0;
			if (v[k][j] != 0 && d[j] == -1) {
				d[j] = v[k][j];
				flag = 1;
			}
			if (v[k][j] != 0 && !vizitat[j]) {
				if (d[j] == -1 || flag || d[j] > d[k] + v[k][j]) {
					d[j] = d[k] + v[k][j];
				}
			}
		}

		printf("Drumurile minime cand adaug %d\n", k);
		printArray(d, size);
	}
	free(d);
	free(vizitat);
	return drum;

}



int main(int argc, char** argv) {
	int** v = NULL;
	int size = 0;
	v = citire(&size, argv[1]);
	//afisare(v, size);
	
	int* drum = djikstra(v, size);
	printArray(drum, size);

	free(drum);

	eliberare(v, size);
}