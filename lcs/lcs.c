#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lcs_length(char **b, int **c, char* string_1, char *string_2){
  int m = strlen(string_1);
  int n = strlen(string_2);
  int i, j;

  for(i = 0; i < m; i++){
    c[i][0] = 0;
    b[i][0] = '0';
  }
  for(j = 0; j < n; j++){
    c[0][j] = 0;
    b[0][j] = '0';
  }

  for(i = 1; i < m; i++)
    for(j = 1; j < n; j++){
      if(string_1[i] == string_2[i]){
        c[i][j] = c[i - 1][j - 1] + 1;
        b[i][j] = '\\';
      }
      else {
        if(c[i - 1][j] >= c[i][j - 1]){
          c[i][j] = c[i - 1][j];
          b[i][j] = '|';
        }
        else {
          c[i][j] = c[i][j - 1];
          b[i][j] = '-';
        }
      }
    }
  return c[m - 1][n - 1];
}

void print_lcs(char* string_1, char* string_2, char** b, int i, int j){
  if(i == 0 || j == 0)
    return;
  
  if(b[i][j] == '\\'){
    print_lcs(string_1, string_2, b, i - 1, j - 1);
    printf("%c", string_1[i]);
  } else {
    if(b[i][j] == '|')
      print_lcs(string_1, string_2, b, i - 1, j);
    else
      print_lcs(string_1, string_2, b, i, j - 1);
  }
}

int main(int argc, char** argv){
  char s1[] = "MAMA";
  char s2[] = "TATA";

  printf("%s\n", s1);
  printf("%s\n", s2);

  int** c = (int** )malloc(sizeof(int*) *4);
  char** b = (char** )malloc(sizeof(char*) * 4);

  int i;
  for(i = 0; i < 4; i++){
    c[i] = malloc(sizeof(int) * 4);
    b[i] = malloc(sizeof(char) * 4);
  }
  lcs_length(b, c, s1, s2);

  int j;
  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++)
      printf("%c", b[i][j]);
    puts(" ");
  }

  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++)
      printf("%d", c[i][j]);
    puts(" ");
  }
  print_lcs(s1, s2, b, strlen(s1) - 1, strlen(s2) - 1);
  puts("");
  return 0;
}
