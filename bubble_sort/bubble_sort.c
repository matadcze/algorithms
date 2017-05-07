#include <stdio.h>

#define SIZE 6

void swap(int * array_of_integers, int a, int b){
  int temp = array_of_integers[a];
  array_of_integers[a] = array_of_integers[b];
  array_of_integers[b] = temp;
  return;
}

void bubble_sort(int * array_of_integers, int amout_of_integers){
  int i, j;
  for(i = 0; i <= amout_of_integers; i++)
    for(j = amout_of_integers; j >= i + 1; j--)
      if(array_of_integers[j] < array_of_integers[j-1])
	swap(array_of_integers, j, j - 1);
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

  bubble_sort(dataset, SIZE - 1);

  print_array(dataset, SIZE);

  return 0;
}
