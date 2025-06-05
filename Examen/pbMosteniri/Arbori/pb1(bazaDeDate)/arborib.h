#define N   2
#define NN (N*2)

typedef int TipCheie;

struct Nod
{
	char nume[30];
	int cheie;
	struct Pagina* p;
	int contor;
};
typedef struct Nod Nod;

struct Pagina
{
	int m;
	struct Pagina* p0;
	Nod e[NN + 1];
};
typedef struct Pagina Pagina;
Pagina* insereaza(Pagina *pag, int x, char nume[30], Nod *nod);
void afisare(Pagina *arbore, int nivel, int data);
Pagina* suprima(Pagina *pag, int x, Nod *nod);