#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#define IN "matrice.txt"

typedef struct {
	int start;
	int end;
}Arc;

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
	apropiat[0] = -1;
	costmin[0] = 0;
	//0 vizitat, -1 fara drum

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
			if (costmin[j] < min && costmin[j]>0) {//nu e nici vizitat nici fara drum
				min = costmin[j];
				k = j;
			}
		}
		drum[len++] = k;
		costmin[k] = 0;

		printf("Am adaugat arcul %d - %d\n", apropiat[k], k);

		for (int j = 1; j < size; j++) {
			if (v[k][j] != 0) {
				if (costmin[j] == -1 || costmin[j] > v[k][j]) {
					costmin[j] = v[k][j];
					apropiat[j] = k;
				}
			}
		}

		//printf("Costurile cand adaug %d\n", k);
		//printArray(costmin, size);
	}

	free(costmin);
	free(apropiat);
	return drum;
}


int* djikstra(int** v, int size) {
	int* drum = (int*)malloc(size * sizeof(int));
	int* d = (int*)malloc(size * sizeof(int));
	int* vizitat = (int*)calloc(size, sizeof(int));
	int len = 0;

	drum[len++] = 0;
	vizitat[0] = 1;
	d[0] = -1;

	for (int i = 1; i < size; i++) {
		if (v[0][i] != 0) {
			d[i] = v[0][i];
		}
		else
			d[i] = -1;
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
				if (flag || (d[j] > d[k] + v[k][j])) {
					d[j] = d[k] + v[k][j];
				}
			}
		}

		printf("Costurile cand adaug %d\n", k);
		printArray(d, size);
	}

	free(d);
	free(vizitat);
	return drum;
}

int find(int* parent, int x) {
	if (x != parent[x])parent[x] = find(parent, parent[x]);
	return parent[x];
}

void unite(int* parent, int x, int y) {
	int rx = find(parent, x);
	int ry = find(parent, y);
	if (rx != ry)
		parent[ry] = rx;
}


void krustal(int** v, int size) {
	Arc* arcuri = (Arc*)malloc((size - 1) * sizeof(Arc));
	int* parent = (int*)malloc(size * sizeof(int));
	int len = 0;

	for (int i = 0; i < size; i++)parent[i] = i;

	while (len < size - 1) {
		int min = INT_MAX;
		int u = 0, w = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (v[i][j] > 0 && min > v[i][j] && find(parent, i) != find(parent, j)) {
					min = v[i][j];
					u = i;
					w = j;
				}
			}
		}
		arcuri[len].start = u;
		arcuri[len].end = w;
		unite(parent, u, w);
		v[arcuri[len].start][arcuri[len].end] = -1;
		v[arcuri[len].end][arcuri[len].start] = -1;
		len++;
	}

	for (int i = 0; i < len; i++) {
		printf("Adaug arcul %d - %d\n", arcuri[i].start, arcuri[i].end);
	}

	free(arcuri);
	free(parent);
}


int main(int argc, char** argv) {
	int** v = NULL;
	int size = 0;
	v = citire(&size, argv[1]);
	//afisare(v, size);
	
	//int* drum = djikstra(v, size);
	//printArray(drum, size);

	//free(drum);

	krustal(v, size);

	eliberare(v, size);
}