#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ll long long
#define MAX 60000l
#define MLD 1000000000.0

void counting_sort(ll* A, int a, ll* B, ll* C, ll k);

int main(int argc, char** argv){
  struct timespec tp0, tp1;
  double sp;
  ll* A = (ll*)malloc(sizeof(ll)*10000);
  ll* C = (ll*)malloc(10000*sizeof(ll));
  ll* B = (ll*)malloc(10000*sizeof(ll));
  ll size = 0;
  if(argc != 3){
    fprintf(stderr,"Spróbuj `counting_sort in.file out.file'\n");
    exit(1);
  }

  FILE* fi = fopen(argv[1], "r");
  FILE* fo = fopen(argv[2], "w");

  if(!fi){
    fprintf(stderr, "Nie moge otworzyć pliku %s\n", argv[1]);
    exit(2);
  }
  
  if(!fo){
    fprintf(stderr, "Nie moge otworzyć pliku %s\n", argv[2]);
    exit(3);
  }
  
  while(fscanf(fi,"%lld", &A[size]) == 1)
    size++;

  size -= 1; // zmiejszam zakres danych

   int k = 9997; // zakres danych ( 1..20 to 20 - 1 + 1 = 20)
clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

 counting_sort(A, size, B, C, k);

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
  
  printf("PROCESS:\n");
  printf("start %12lu  %12lu \n",tp0.tv_sec, tp0.tv_nsec);
  printf("stop  %12lu  %12lu \n",tp1.tv_sec, tp1.tv_nsec);
  sp=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("czas   %3.5lf\n",sp);

  ll i = 0;
  while(i <= size){
    fprintf(fo, "%lld\n", B[i]);
    i++;
  }
  
  fclose(fi);
  fclose(fo);
  free(A);
  free(B);
  free(C);
  
  return 0;
}

void counting_sort(ll* A, int a, ll* B,ll* C, ll k){
  int i = 0;
  for(i = 0; i < k; i++) // zerowanie tablicy pomocniczej 
    C[i] = 0;

  for(i = 0; i <= a; i++)
    C[A[i]] += 1;       // tworzymy wektor (binarny o ile wszystkie liczby są unikalne)

  for(i = 1; i <= k ; i++)
    C[i] = C[i] + C[i-1];

  for(i = a ; i >= 0; i--){ // a == size ale w main() zmiejszyłem juz ilosc elementow size wiec a jest git
    B[C[A[i]] - 1] = A[i];
    C[A[i]] = C[A[i]] - 1;
  }
  return;
}
