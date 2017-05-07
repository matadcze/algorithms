#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void naive_string_matcher(char* text, char* pattern){
  int n = strlen(text) - 1;
  int m = strlen(pattern) - 1;
  int offset;

  for (int s = 0; s < n - m; s++)
  {
    offset = 0;
    for(int i = 0; i < m; i++) {
      if(pattern[i] == text[s+i])
        offset++;
      if(offset == m)
        printf("Wzorzec występuje w przesunięciem %d.\n", s);
    }

  }
}

void rabin_karp_matcher(char* text, char * pattern, int d, int q){
  int n = strlen(text) - 1;
  int m = strlen(pattern) - 1;

  int offset;
  int h = 1;
  
  for(int i = 0; i < m - 1; i++){
    h = (h * d) % q;
  }

  int p = 0;
  int t = 0;

  for (int i = 0; i < m; i++)
  {
    p = (d*p + pattern[i]) % q;
    t = (d*t + text[i]) % q;
  }


  for(int s = 0; s < n - m; s++){
    offset = 0;
    if(p == t){
      for(int i = 0; i < m; i++){
        if(text[s+i] == pattern[i]){
          offset++;
        }
        if(offset == m){
          printf("Wzorzec występuje w przesunięciem %d.\n", s);
        }
      }
    }
    t = (d*(t - text[s]*h) + text[s + m]) % q;
    
    if(t < 0)
     t = t + q;
 }
}

int * compute_prefix_function(char * pattern){
  int m = strlen(pattern) - 1;
  int * pi = (int *) malloc(m * sizeof(int));
  int k = 0;
  pi[0] = k;
  for (int q = 1; q < m; q++)
  {
    while(k > 0 && (pattern[k+1] != pattern[q])){
      k = pi[k];
      if(pattern[k+1] == pattern[q])
        k++;
      pi[q] = k;
    }
  }
  return pi;
}

void kmp_matcher(char *text, char * pattern){
  int n = strlen(text) - 1;
  int m = strlen(pattern) - 1;

  int * pi = compute_prefix_function(pattern);
  int q = 0;

  for(int i = 0; i < n; i++){
    while(q > 0 && (pattern[q + 1] != text[i]))
      q = pi[q];
    
    if(pattern[q + 1] == text[i])
      q = q + 1;

    if(q == m - 1){
      printf("Wzorzec występuje w przesunięciem %d.\n", i - m + 1);
      q = pi[q];
    }

  }
}


char * read_file(char * file_name){
  FILE * file = fopen(file_name, "r");

  fseek(file, 0, SEEK_END);
  long fsize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *string = malloc(fsize + 1);
  fread(string, fsize, 1, file);
  fclose(file);

  string[fsize] = '\0';

  return string;
}

int main(int argc, char const *argv[])
{
  char * text = read_file("tekst.txt");
  char * pattern = read_file("wzorzec.txt");


  printf("Naiwny algorytm: \n");
  naive_string_matcher(text, pattern);

  printf("Algorytm Rabina-Karpa: \n");
  rabin_karp_matcher(text, pattern, 256, 7919);

  printf("Algorytm Knutha-Morrisa-Pratta: \n");
  kmp_matcher(text, pattern);

  return 0;
}