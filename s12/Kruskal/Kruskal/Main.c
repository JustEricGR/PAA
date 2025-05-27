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
	}printf("\n");
}

int check(int* v, int size) {
	for (int i = 0; i < size; i++) {
		if (!v[i])return 0;
	}
	return 1;
}

int find(int* parent, int x) {
	if (parent[x] != x)parent[x] = find(parent, parent[x]);
	return parent[x];
}

void unite(int* parent, int x, int y) {
	int rx = find(parent, x);
	int ry = find(parent, y);
	if (rx != ry)
		parent[ry] = rx;
}

void kruskal(int** v, int size) {
	int compConexe = size;
	Arc* arcuri = (Arc*)malloc((size-1) * sizeof(Arc));
	int* parent = (int*)malloc(size * sizeof(int));
	int len = 0;

	for (int i = 0; i < size; i++)parent[i] = i;

	
	while (len < size - 1) {
		int min = INT_MAX;
		int u = -1, w = -1;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (min > v[i][j] && v[i][j] > 0 && find(parent, i) != find(parent, j)) {
					min = v[i][j];
					u = i;
					w = j;
					
				}
			}
		}
		
		if (u == -1 || w == -1) {
			printf("Nu mai exista arcuri valide de adaugat.\n");
			break;
		}
		arcuri[len].start = u;
		arcuri[len].end = w;
		unite(parent, u, w);
		v[arcuri[len].start][arcuri[len].end] = -1;
		v[arcuri[len].end][arcuri[len].start] = -1;
		len++;

		//compConexe--;
		
	}
	printf("Lungimea: %d\n", len);
	
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
	kruskal(v, size);

	eliberare(v, size);
	//free(drum);
}