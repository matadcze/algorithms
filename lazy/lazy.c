/*
 * I tried to make a sort algorithm which will work very slowly O(n^2).
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 60000l
#define MLD 1000000000.0

void swap(int* a, int* b);
void lazy_sort(int* A, int n);

int main(int argc, char** argv){
  struct timespec tp0, tp1;
  double sp;
  int* dataset = (int*)malloc(sizeof(int)*1000000);
  int size = 0;
  if(argc != 3){
    fprintf(stderr,"Spróbuj `lazy_sort in.file out.file'\n");
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
  
  while(fscanf(fi,"%d", &dataset[size]) == 1)
    size++;

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

  lazy_sort(dataset, size);

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
  
  printf("PROCESS (lazy_sort):\n");
  printf("start %12lu %12lu \n",tp0.tv_sec, tp0.tv_nsec);
  printf("stop %12lu %12lu \n",tp1.tv_sec, tp1.tv_nsec);
  sp=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("czas %3.5lf\n",sp);

  int i = 0;
  while(i < size){
    fprintf(fo, "%d\n", dataset[i]);
    i++;
  }
  
  fclose(fi);
  fclose(fo);
  free(dataset);
  
  return 0;
}

void swap(int* a, int* b){
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

void lazy_sort(int* A, int n){
  int i,j;
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      if(A[i] < A[j]){
	swap(&A[i], &A[j]);
      }
    }
  }
}
