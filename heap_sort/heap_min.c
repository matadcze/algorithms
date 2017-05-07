#include <stdio.h>
#include <stdlib.h>

#define parent(x) (((x) >> 1))
#define left_son(x) (((x) << 1) + 1)
#define right_son(x) ((((x) << 1) + 2))

void swap(int* , int* );
void min_heapify(int* , int , int );
void build_min_heap(int* , int );
void heapsort(int* , int );
int heap_extract_min(int* , int );
void heap_increase_key(int* , int , int );
void min_heap_insert(int* , int , int);

int main(int argc, char** argv){

  int size = 9;
  int dataset[36] = {2,5,8,9,6,3,1,4,7};
  int i;


  build_min_heap(dataset, size);
  // heapsort(dataset, size+1);
  for(i = 0; i < size; i++)
    fprintf(stdout, "%d\n", dataset[i]);
  puts("===============================");
  
  heap_extract_min(dataset, size);
  size -= 1;
  for(i = 0; i < size; i++)
    fprintf(stdout, "%d\n", dataset[i]);
  puts("===============================");
  
    heap_extract_min(dataset, size);
  size -= 1;
  for(i = 0; i < size; i++)
    fprintf(stdout, "%d\n", dataset[i]);
  puts("===============================");

    heap_extract_min(dataset, size);
  size -= 1;
  for(i = 0; i < size; i++)
    fprintf(stdout, "%d\n", dataset[i]);
  puts("===============================");

  // heap_increase_key(dataset, 0, -21);
  // for(i = 0; i < size; i++)
  //   fprintf(stdout, "%d\n", dataset[i]);
  // puts("===============================");

  // min_heap_insert(dataset, size, -366);
  // size += 1;
  // for(i = 0; i < size; i++)
  //   fprintf(stdout, "%d\n", dataset[i]);
  // puts("===============================");

  // min_heap_insert(dataset, size, 36);
  // size += 1;
  // for(i = 0; i < size; i++)
  //   fprintf(stdout, "%d\n", dataset[i]);
  // puts("===============================");

  // min_heap_insert(dataset, size, 26);
  // size += 1;
  // for(i = 0; i < size; i++)
  //   fprintf(stdout, "%d\n", dataset[i]);
  // puts("===============================");

  return 0;
}


int heap_minimum(int* array){
  return array[0];
}

int heap_extract_min(int* array, int heap_size){
  int min = array[0];
  array[0] = array[heap_size - 1];
  heap_size -= 1;
  min_heapify(array, heap_size, 0);
  return min;
} 

void heap_increase_key(int* array, int i, int key){
  if(key > array[i]){
    fprintf(stderr, "nowy klucz jest wiekszy niz aktualny klucz\n");
    return;
  }
  array[i] = key;
  while(i > 0 && array[parent(i)] > array[i]){
    swap(&array[i], &array[parent(i)]);
    i = parent(i);
  }
  return;
}

void min_heap_insert(int* array, int heap_size, int key){
  array[heap_size] = 123456789;
  heap_increase_key(array, heap_size, key);
  return;
}


void swap(int* a, int* b){
  int temp = *a;
  *a = *b;
  *b = temp;
  return;
}

void min_heapify(int* array, int heap_size, int i){
  int l = left_son(i);
  int r = right_son(i);
  int largest;

  if((l <= heap_size) && (array[l] < array[i]))
    largest = l;
  else
    largest = i;

  if((r <= heap_size) && (array[r] < array[largest]))
    largest = r;
  
  if(largest != i){
    swap(&array[largest], &array[i]);
    min_heapify(array, heap_size, largest);
  }
  return;
}

void build_min_heap(int* array, int size){
  int i;
  for(i = parent(size)-1; i >= 0; i--)
    min_heapify(array, size, i);
  return;
}

void heapsort(int* array, int array_size){
  int heap_size = array_size;
  build_min_heap(array, array_size);
  int i;
  for(i = array_size; i > 0 ; i--){
    swap(&array[i], &array[0]);
    heap_size--;
    min_heapify(array, heap_size, 0);
  }
  return;
}
