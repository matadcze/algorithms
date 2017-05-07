// struktura wezla B-drzewa i przyklad zapisu i odczytu na plik
// budowanie B-drzewa o zadanej wysokosci i drukowanie w dwoch
// wersjch tekstowo i graficznie
//`                                     pmp@inf.ug.edu.pl 2007, 2013

#include <stdio.h>
#include <stdbool.h>
#define T 3			// stopien B-drzewa

typedef struct {
	short n;		//ilosc kluczy (-1 oznacza wezel usuniety)
	short leaf;		// czy lisc
	int k[2 * T - 1];	// klucze
	int c[2 * T];		// wskazniki do synow (pozycje w pliku: 0,1,2 ...)
	int info[2 * T - 1];	// wskazniki do informacji skojarzonej z kluczem
	// (pozycje w innym pliku); tutaj nie beda uzyte
} Wezel;

int rozmiarw = sizeof(Wezel);	// rozmiar wezla w bajtach
FILE *drzewo;			// plik drzewa (zawierajacy wezly)

void zapisz(int i, Wezel * w)
{
	// zapisuje *w jako i-ty zapis w pliku drzewa
	fseek(drzewo, (long)i * rozmiarw, SEEK_SET);
	fwrite(w, rozmiarw, 1, drzewo);
	//  printf("z%d ",i);
}

void odczytaj(int i, Wezel * w)
{
	// odczytuje i-ty zapis w pliku drzewa i wpisuje do *w
	fseek(drzewo, (long)i * rozmiarw, SEEK_SET);
	fread(w, rozmiarw, 1, drzewo);
	//  printf("o%d ",i);
}

void usun(int i)
{
	// usuwa i-ty zapis w pliku drzewa
	// w tej wersji nie wykorzystujemy usunietych pozycji,
	// tylko zaznaczamy jako usuniete
	Wezel w;
	odczytaj(i, &w);
	w.n = -1;
	zapisz(i, &w);
}

int budujB(int g, int n)
{
	// buduje B-drzewo o wysokosci g, w kazdym wezle jest n kluczy
	// wynikiem jest pozycja korzenia w pliku - jest to ostatni 
	// zapis w pliku, co jest wazne dla dalszych zapisow do pliku
	// ktore trzeba robic zaczynajac od kolejnej pozycji
	static int klucz = 0;	// kolejny klucz
	static int pozycja = 0;	// wolna pozycja w pliku
	Wezel w;
	w.n = n;
	int i;
	if (g == 0) {		// lisc
		for (i = 0; i < n; i++) {
			w.c[i] = -1;	// w lisc
			w.k[i] = klucz++;
		}
		w.c[n] = -1;
		w.leaf = 1;
	} else {		// wezel wewnetrzny
		for (i = 0; i < n; i++) {
			w.c[i] = budujB(g - 1, n);
			w.k[i] = klucz++;
		}
		w.c[n] = budujB(g - 1, n);;
		w.leaf = 0;
	}
	zapisz(pozycja++, &w);
	return pozycja - 1;
}

void drukujB(int r, int p)
{
	// drukuje B-drzewo o korzeniu r (pozycja w pliku)
	// wydruk przesuniety o p w prawo
	Wezel w;
	int i, j;
	odczytaj(r, &w);
	if (w.leaf) {
		for (i = 0; i < p; i++)
			printf(" ");
		for (i = 0; i < w.n; i++)
			printf("%d ", w.k[i]);
		printf("\n");
	} else {
		drukujB(w.c[w.n], p + 4);
		for (i = w.n - 1; i >= 0; i--) {
			for (j = 0; j < p; j++)
				printf(" ");
			printf("%d\n", w.k[i]);
			drukujB(w.c[i], p + 4);
		}
	}
	return;
}

void drukujBDot(int r)
{
	// przygotowuje wydruk graficzny B-drzewa o korzeniu r (pozycja w pliku)
	// tworzy plik bdrzewo.gv z danymi dla programu dot
	// instrukcja    dot -Tpdf -o bdrzewo.pdf bdrzewo.gv 
	// utworzy plik bdrzewo.pdf z graficzna reprezentacja drzewa
	FILE *plikwy;
	plikwy = fopen("bdrzewo.gv", "w");
	fprintf(plikwy, "graph bdrzewo{\n");
	fprintf(plikwy, "size = \"2,20\"");
	rekDrukujBDot(r, 0, plikwy);
	fprintf(plikwy, "}\n");
	fclose(plikwy);
	printf("utworzony plik bdrzewo.gv");
}

int rekDrukujBDot(int r, int z, FILE * plikwy)
{
	// pomocnicza funkcja dla drukujBDot()
	// drukuje B-drzewo o korzeniu r (pozycja w pliku)
	// z  - numer wezla
	// zwraca najwiekszy numer wezla w poddrzewie, ktorego jest korzeniem
	//d [shape=box, width=5.0,length=3, height=0.3]
	Wezel w;
	int nz, i;

	odczytaj(r, &w);

	fprintf(plikwy, "%d [shape=box, label=\"", z);

	for (i = 0; i < w.n; i++)
		fprintf(plikwy, "%d ", w.k[i]);

	fprintf(plikwy, "\"]\n");
	nz = z;
	if (!w.leaf) {
		for (i = 0; i <= w.n; i++) {
			fprintf(plikwy, "%d -- %d ;\n", z, nz + 1);
			nz = rekDrukujBDot(w.c[i], nz + 1, plikwy);
		}
	}
	return nz;
}

int main(void)
{
	int i;
	double sp;
	drzewo = fopen("bdrzewo", "w+");
	Wezel wezel;
	int root;

	root = budujB(2, 2);
	printf("\n");
	drukujB(root, 0);
	drukujBDot(root);
	fclose(drzewo);
}
