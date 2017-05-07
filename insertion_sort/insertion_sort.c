#include <stdio.h>

#define SIZE 6

void insertion_sort(int * array_of_integers, int amout_of_integers){
  int i, j, key;
  for(j = 1; j < amout_of_integers; j++){
    key = array_of_integers[j];
    i = j - 1;
    while(i >= 0 && array_of_integers[i] > key){
      array_of_integers[i + 1] = array_of_integers[i];
      i--;
    }
    array_of_integers[i + 1] = key;
  }
  return;
}

void insertion_sort_descending(int * array_of_integers, int amout_of_integers){
  int i, j, key;
  for(j = 1; j < amout_of_integers; j++){
    key = array_of_integers[j];
    i = j - 1;
    while(i >= 0 && array_of_integers[i] < key){
      array_of_integers[i + 1] = array_of_integers[i];
      i--;
    }
    array_of_integers[i + 1] = key;
  }
  return;
}

void print_array(int * array_of_integers, int amout_of_integers){
  int i;
  for(i = 0; i < amout_of_integers; i++)
    printf("%d ",array_of_integers[i]);
  puts("");
  return;
}

int main(void){
  // debugging
  int dataset[] = {5, 2, 4, 6, 1, 3};

  print_array(dataset, SIZE);

  insertion_sort(dataset, SIZE);

  print_array(dataset, SIZE);

  return 0;
}
