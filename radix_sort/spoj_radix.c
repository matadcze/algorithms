#include <stdio.h>
#include <stdlib.h>

typedef struct dict {
  int num[3];
  int length;
} dict;

void counting_sort(dict* A, int a, int j, dict* B){
  int i, k = 256, p;
  int C[k];
  for(i = 0; i < k; i++)
    C[i] = 0;
  for(i = 0; i <= a; i++){
    p = digit(A, i, j);
    C[p] += 1;
  }
  for(i = 1; i < k ; i++)
    C[i] += C[i-1];
  for(i = a ; i >= 0; i--){
    p = digit(A, i, j);
    B[C[p] - 1] = A[i];
    C[p] = C[p] - 1;
  }
  return;
}

void radix_sort(dict* A, int size, dict* B, int max){
  int j; dict* C;
  for(j = max - 1; j >= 0; j--){
    counting_sort(A, size, j, B);
    C = A; A = B; B = C;
  }
}

int main(void){
  dict *A = (dict *) malloc(AMAX*sizeof(dict));
  dict *B = (dict *) malloc(AMAX*sizeof(dict));
  int max = 0, size = 0, t;
  scanf("%d",&t);
  while(t--){
    int a, b, c
    scanf("%d %d %d", dict.num[0], , &c);
    
  }
  radix_sort(A, size, B, 3);
  return 0;
}
