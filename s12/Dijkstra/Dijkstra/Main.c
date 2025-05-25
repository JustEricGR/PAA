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



int* djikstra(int** v, int size) {
	int* drum = (int*)malloc(size * sizeof(int));
	int* vizitat = (int*)calloc(size, sizeof(int));
	int* d = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)d[i] = -1;

	drum[0] = 0;
	vizitat[0] = 1;
	int len = 1;

	for (int i = 1; i < size; i++) {
		if (v[0][i] != 0) d[i] = v[0][i];
	}
	printf("Stare drumuri cand adaug 0\n");
	printArray(d, size);

	for (int k = 1; k < size; k++) {
		int min = INT_MAX;
		int u = -1;
		for (int i = 0; i < size; i++) {
			if (!vizitat[i] && d[i] < min && d[i] != -1) {
				min = d[i];
				u = i;
			}
		}
		if (u == -1)break;
		vizitat[u] = 1;
		drum[len++] = u;

		for (int j = 1; j < size; j++) {
			int flag = 0;
			if (d[j] == -1 && v[u][j] != 0) {
				d[j] = v[u][j];
				flag = 1;
			}
			if (v[u][j] != 0 && !vizitat[j]) {
				if(d[j] == -1 || flag || (d[j] > d[u] + v[u][j]))
					d[j] = d[u] + v[u][j];
			}
		}
		printf("Stare drumuri cand adaug %d\n", u);
		printArray(d, size);
		min = INT_MAX;
	}
	free(vizitat);
	free(d);
	return drum;
}


int main(int argc, char** argv) {
	int** v = NULL;
	int size = 0;

	v = citire(&size, argv[1]);
	//afisare(v, size);

	int* drum = djikstra(v, size);
	printArray(drum, size);

	eliberare(v, size);
	free(drum);
}