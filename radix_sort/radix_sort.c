#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 60000l
#define MLD 1000000000.0
#define MDN 254 // długość słowa
#define AMAX 10000 // maksymalna ilość słów w słowniku

typedef struct dict {
  char* word;
  int length;
} dict;

/* metoda digit zwraca znak na i-tej pozycji */
/* albo 0 jeżeli długość łańcucha jest krótsza niż pożądany element */
int digit(dict *array, int elem_in_array, int offset){
  if(offset <= array[elem_in_array].length)
    return array[elem_in_array].word[offset - 1];
  else
    return 0;
}  

void counting_sort(dict* A, int a, int j, dict* B){
  int i;

  /* k to rozpiętność danych */
  int k = 256;

  int C[k];
  /* zmienna p przechowuje cyfrę  */
  int p;

  /* zerowanie tablicy pomocniczej */
  for(i = 0; i < k; i++)
    C[i] = 0;

  /* pierwszy krok counting_sort'u  */
  /* rozmiar tablicy a został zmiejszony, gdy był zwracany z metody read_strings */
  for(i = 0; i <= a; i++){
    p = digit(A, i, j);
    C[p] += 1;
  }

  /* drugi krok counting_sort'u */
  for(i = 1; i < k ; i++)
    C[i] += C[i-1];

  /* trzeci krok counting_sort'u */
  /* struktura pozwala na łatwiejsze operowanie danymi (moim zdaniem) */
  for(i = a ; i >= 0; i--){
    p = digit(A, i, j);
    B[C[p] - 1] = A[i];
    C[p] = C[p] - 1;
  }
}

void radix_sort(dict* A, int size, dict* B, int max){
  int j;
  dict* C;
  for(j = max - 1; j >= 0; j--){
    counting_sort(A, size, j, B);
    C = A;
    A = B;
    B = C;
  }
}

/* wczytuje łańcuchy o zmiennej długości do pamięci */
/* zapisuje długość łańcucha do struktury, i wylicza najdłuższy łańcuch */
int read_strings(FILE *fi, dict *A, int *max){
  char word[MDN];
  int i = 0;
  while(fscanf(fi, "%s", word) == 1){
    A[i].length = strlen(word);
    /* dodałem +1 bo znak \0 nie został policzny */
    A[i].word = (char*) malloc(sizeof(char)*(A[i].length + 1));
    strcpy(A[i].word, word);
    
    if(*max < A[i].length)
      *max = A[i].length;

    i++;
  }
  return i - 1;
}

/* zapisuje posortowane łańcuchy do pliku */
void write_strings(FILE *fo, dict *B, int size){
  int i = 0;
  while(i <= size){
    fprintf(fo, "%s\n", B[i].word);
    i++;
  }
}

int main(int argc, char **argv){
  struct timespec tp0, tp1;
  double sp;
  dict *A = (dict *) malloc(AMAX*sizeof(dict));  // tablica bazowa
  dict *B = (dict *) malloc(AMAX*sizeof(dict));  // tablica posortowanych elementów
  int max = 0;
  int size = 0;

  if(argc != 3){
    fprintf(stderr,"Spróbuj `radix_sort in.file out.file'\n");
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
  
  size = read_strings(fi, A, &max);

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

  radix_sort(A, size, B, max);

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);

  write_strings(fo, A, size);
  
  printf("PROCESS (radix_sort):\n");
  printf("start %12lu  %12lu \n",tp0.tv_sec, tp0.tv_nsec);
  printf("stop  %12lu  %12lu \n",tp1.tv_sec, tp1.tv_nsec);
  sp=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("czas   %3.5lf\n",sp);

  fclose(fi);
  fclose(fo);
  free(A);
  free(B);
  
  return 0;
}
