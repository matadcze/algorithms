#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ll long long
#define parent(x) (((x) >> 1))
#define left_son(x) (((x) << 1) + 1)
#define right_son(x) ((((x) << 1) + 2))
#define MAX 60000l
#define MLD 1000000000.0

void swap(ll* a, ll* b);
void max_heapify(ll* array, ll heap_size, int i);
void build_max_heap(ll* array, ll size);
void heapsort(ll* array, ll array_size);

int main(int argc, char** argv){
  struct timespec tp0, tp1;
  double sp;
  ll* dataset = (ll*)malloc(sizeof(ll)*10222111);
  ll size = 0;
  if(argc != 3){
    fprintf(stderr,"Spróbuj `heapsort in.file out.file'\n");
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
  
  while(fscanf(fi,"%lld", &dataset[size]) == 1)
    size++;

   size -= 1;


clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

  heapsort(dataset, size);

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
  
  printf("PROCESS:\n");
  printf("start %12lu  %12lu \n",tp0.tv_sec, tp0.tv_nsec);
  printf("stop  %12lu  %12lu \n",tp1.tv_sec, tp1.tv_nsec);
  sp=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("czas   %3.5lf\n",sp);

  ll i = 0;
  while(i <= size){
    fprintf(fo, "%lld\n", dataset[i]);
    i++;
  }
  
  fclose(fi);
  fclose(fo);
  free(dataset);
  
  return 0;
}

void swap(ll* a, ll* b){
  ll temp = *a;
  *a = *b;
  *b = temp;
}

void max_heapify(ll* array, ll heap_size, int i){
  ll l = left_son(i);
  ll r = right_son(i);
  ll largest;

  if((l <= heap_size) && (array[l] > array[i]))
    largest = l;
  else
    largest = i;

  if((r <= heap_size) && (array[r] > array[largest]))
    largest = r;
  
  if(largest != i){
    swap(&array[largest], &array[i]);
    max_heapify(array, heap_size, largest);
  }

}

void build_max_heap(ll* array, ll size){
  int i;
  for(i = parent(size)-1; i >= 0; i--)
    max_heapify(array, size, i);
}

void heapsort(ll* array, ll array_size){
  ll heap_size = array_size;
  build_max_heap(array, array_size);
  int i;
  for(i = array_size; i > 0 ; i--){
    swap(&array[i], &array[0]);
    heap_size--;
    max_heapify(array, heap_size, 0);
  }
}
