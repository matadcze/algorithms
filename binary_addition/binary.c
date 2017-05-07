#include <stdio.h>

#define LENGTH 5

void binary_addition(int * a, int * b, int * c, int n){
  int i;
  for(i = 0 ; i < n; i++){
    c[i] += a[i] + b[i];
    if( c[i] / 2 == 1){
      c[i] %= 2;
      c[i + 1] += 1;
    }
  }
  return;
}

void zero_to_array(int * array, int length){
  int i;
  for(i = 0; i < length; i++)
    array[i] = 0;
  return;
}

void print_binary_numer(int * array, int length){
  int i;
  for(i = length; i >= 0; i--)
    printf("%d",array[i]);
  puts("");
  return;
}

int main(void){
  int a[] = {1, 1, 0, 0, 1};
  int b[] = {1, 1, 1, 1, 1};
  int c[LENGTH+1];

  zero_to_array(c, LENGTH);  
  binary_addition(a, b, c, LENGTH);
  print_binary_numer(c, LENGTH);
  
  return 0;
}
