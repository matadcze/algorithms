#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 3744
int hash_string(char* string, int M){
  int h = 1;
  int a = 111;
  for(int i = 0; i < strlen(string); i++)
    h =  (h + a*string[i]);
  return h % M;
}
int read_strings(char** string_table, FILE* in){
  char tmp[255];
  int i = 0;
  while(fscanf(in, "%s", tmp) == 1){
    string_table[i] = (char*) malloc(sizeof(char*) * (strlen(tmp) + 1));
    if(string_table[i] == NULL){
      fprintf(stderr, "Nie zaalokowano pamięci dla łańcucha.\n");
      exit(5);
    }
    strcpy(string_table[i], tmp);
    i++;
  }
  return i;
}
int read_ints(int* int_table, FILE* in){
  int i = 0;
  while(fscanf(in, "%d", &int_table[i]) == 1 && i != 513){
    i++;
  }
  return i;
}
int max(int* table, int size){
  int max = 0;
  for(int i = 0; i < size; i++)
    if(table[i] > max)
      max = table[i];
  return max;
} 
int zero(int* table, int size){
  int zero = 0;
  for(int i = 0; i < size; i++)
    if(table[i] == 0)
      zero++;
  return zero;
}
double mean(int* table, int size){
  int mean = 0;
  double amount = 0;
  for(int i = 0; i < size; i++){
    if(table[i] != 0){
      mean += table[i];
      amount += 1;
    } else
      continue;
  }
  return mean/amount;
}
int main(int argc, char** argv){
  FILE* s;
  FILE* p;
  char** strings = malloc(sizeof(char*) * SIZE);
  int* primes = malloc(sizeof(int) * SIZE);
  int amount_of_strings = 0;
  int amount_of_numbers = 0;
  if(strings == NULL){
    fprintf(stderr, "Nie zaalokowano pamięci dla stringów.\n");
    exit(4);
  }
  if(primes == NULL){
    fprintf(stderr, "Nie zaalokowano pamięci dla liczb.\n");
    exit(5);
  }
  if(argc == 3){
    s = fopen(argv[1], "r");
    p = fopen(argv[2], "r");
    if(s == NULL){
      fprintf(stderr, "Nie można otworzyć pliku %s\n", argv[1]);
      exit(1);
    }
    if(p == NULL){
      fprintf(stderr, "Nie można otworzyć pliku %s\n", argv[2]);
      exit(2);
    }
    amount_of_strings = read_strings(strings, s);
    amount_of_numbers = read_ints(primes, p);
    free(p);
    free(s);
  } else {
    exit(3);
  }
  printf("===============================================\n");
  for(int i = 0; i < amount_of_numbers; i++){
    int T[primes[i]];
    for(int k = 0; k < primes[i]; k++)
      T[k] = 0;
    for(int j = 0; j < amount_of_strings; j++){
      int key = hash_string(strings[j], primes[i]);
	T[key] += 1;
    }
    printf("liczba : %d\n", primes[i]);
    printf("ilość zerowych pozycji w tablicy T : %d\n", zero(T, primes[i]));
    printf("maksymalna wartość w T: %d\n", max(T, primes[i]));
    printf("średnia wartość pozycji niezerowych: %lf\n", mean(T, primes[i]));
    printf("===============================================\n");
  }
  return 0;
}
