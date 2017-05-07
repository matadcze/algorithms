#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 60000l
#define MLD 1000000000.0

void swap(int* a, int* b);
int partition(int* a, int p, int r);
void quicksort(int* a, int p, int r);

int main(int argc, char** argv){
  struct timespec tp0, tp1;
  double sp;
  int* dataset = (int*)malloc(sizeof(int)*1000000);
  int size = 0;
  if(argc != 3){
    fprintf(stderr,"Spróbuj `quicksort in.file out.file'\n");
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

   size -= 1;


  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

  quicksort(dataset, 0, size);

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
  
  printf("PROCESS (quicksort):\n");
  printf("start %12lu %12lu \n",tp0.tv_sec, tp0.tv_nsec);
  printf("stop %12lu %12lu \n",tp1.tv_sec, tp1.tv_nsec);
  sp=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("czas %3.5lf\n",sp);

  int i = 0;
  while(i <= size){
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

int partition(int* a, int p, int r){
  int x = a[r];
  int i = p - 1;
  int j;
  for(j = p; j <= r; j++){
    if(a[j] <= x){
      i++;
      swap(&a[i], &a[j]);
    }
  }
  if(i < r) return i;
  else return i - 1;
}

void quicksort(int* a, int p, int r){
  int q;
  if(p < r){
    q = partition(a, p, r);
    quicksort(a, p, q);
    quicksort(a, q + 1, r);
  }
}
