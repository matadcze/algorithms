#include <stdio.h>
#include <stdlib.h>
    
void merge(int* array_of_integers, int p, int q, int r);
void merge_sort(int* array_of_integers, int p, int r);
int max(int* array_of_integers, int amout_of_integers);
int add_infinity_to_array(int* array_of_integers, int number_of_loaded_elements, int infinity);

int mediana(int* a, int size_a, int k){
  int maximum = max(a, size_a);
  int infinity = maximum + 1;
  int new_size_a = add_infinity_to_array(a, size_a, infinity);

  int medians[new_size_a/5];
  int i,j;
 
  for(i = 0; i < new_size_a/5; i++)
    merge_sort(a,5*i, 5*(i+1));
   
  for(i = 2, j = 0; j < new_size_a/5; i += 5, j++)
    medians[j] = a[i];

  int me = medians[new_size_a/10];
  
  /* for(i = 0; i < 5;i++) */
  /*   printf("%d ",medians[i]); */

  int a_less_size = 0;
  int a_more_size = 0;
  int a_less[1000];
  int a_more[1000];

  
  for(i = 0; i < new_size_a; i++){
    if(a[i] < me)
      a_less[a_less_size++] = a[i];
    if(a[i] > me)
      a_more[a_more_size++] = a[i];
  }
  
  printf("== %d %d %d\n",me,a_more_size, a_less_size);
  //k = (new_size_a + 1)/2;
  
  if(k < a_less_size + 1){
    return mediana(a_less, a_less_size, k);
  }
  if(a_less_size + 1 == k){
    return me;
  }
  if(k > a_less_size + 1){
      return mediana(a_more, a_more_size, k - a_less_size - 1);
    } 
}


int main(int argc,char** argv){
  int a[1000];
  int me;
  int size = 0;

  if(argc != 2){
    fprintf(stderr,"Spróbuj `heapsort in.file'\n");
    exit(1);
  }

  FILE* fi = fopen(argv[1], "r");

  if(!fi){
    fprintf(stderr, "Nie moge otworzyć pliku %s\n", argv[1]);
    exit(2);
  }
  
  while(fscanf(fi,"%d", &a[size]) == 1)
    size++;

  me =  mediana(a, size, (size+1)/2);
  printf("Me = %d\n", me);
  fclose(fi);

  return 0;
}
    
void merge(int* array_of_integers, int p, int q, int r){
  int n1 = q - p + 1;
  int n2 = r - q; 
  int i, j, k;
  int left_array[n1+1];
  int right_array[n2+1];
  
  left_array[n1] = 123456798;
  right_array[n2] = 123456798;
  
  for(i = 0; i < n1; i++)
    left_array[i] = array_of_integers[p + i];
  for(j = 0; j < n2; j++)
    right_array[j] = array_of_integers[q + j + 1];

  i = 0;
  j = 0;
  
  for(k = p; k <= r; k++){
    if(left_array[i] <= right_array[j]){
      array_of_integers[k] = left_array[i];
      i++;
    } else {
      array_of_integers[k] = right_array[j];
      j++;
    }
  }
}

void merge_sort(int* array_of_integers, int p, int r){
  if(p < r){
    int q = (p+r)/2;
    merge_sort(array_of_integers, p, q);
    merge_sort(array_of_integers, q + 1, r);
    merge(array_of_integers, p, q, r);
  }
}
    
int max(int* array_of_integers, int amout_of_integers){
  int max = array_of_integers[0];
  int i = 1;
  while(i < amout_of_integers){
    if(max < array_of_integers[i]){
      max = array_of_integers[i];
    }
    i++;
  }
  return max;
}

int add_infinity_to_array(int* array_of_integers, int number_of_loaded_elements, int infinity){
  int modulo = 5 - (number_of_loaded_elements % 5);
  int i = 0;
  while(modulo != 5 && i <= modulo){
    array_of_integers[number_of_loaded_elements + i] = infinity;
    i++;
  }
  if(modulo != 5)
    return (number_of_loaded_elements + modulo);
  else
    return number_of_loaded_elements;
}

