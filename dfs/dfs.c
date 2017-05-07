#include <stdio.h>
#include <stdlib.h>

int n = 10;

void zwiedzaj(int **G, int * V, int i){
  V[i] = 1;
  printf("%d ", i);
  for(int k = 0; k < n; k++){
    if(G[i][k] != 0){ // czy istnieje przejscie Adj
      if(V[k] == 0){
	printf("(%d, %d) ", i, k);
	zwiedzaj(G, V, k);
      }
    }
  }
}

void szukaj(int ** G, int * V){
  for(int i = 0; i < n; i++)
    V[i] = 0; // wierzchołek nie był badany
  for(int i = 0; i < n; i++)
    if(V[i] == 0){
      
      zwiedzaj(G, V, i);
     
    }

}

void read_graph(int ** G, char * file_name){
  FILE * fp = fopen(file_name, "r");

  if(fp == NULL)
    fprintf(stderr, "Nie można otwrzyć pliku: %s", file_name);


  char * sentence = (char*) malloc(sizeof(char) * n);

  fscanf(fp, "%d",&n);

  printf("%d\n", n);
  
  int i = 0;
  while(fscanf(fp, "%s", sentence) == 1){
    for(int j = 0; j < n; j++)
      G[i][j] = (int)sentence[j]-48;

    i++;
  }


}

void print_graph(int ** G){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      printf("%d ", G[i][j]);
    }
    puts("");
  }
  for(int i = 0; i < n; i++)
    printf("= ");
  puts("");
}

int main(void){
  int ** G = (int **) malloc( n * sizeof(int *));
  for(int i = 0; i < n; i++){
    G[i] = (int *) malloc(n * sizeof(int));
  }

  int * V = (int *) malloc(n * sizeof(int));

  read_graph(G, "graph.txt");
  print_graph(G);
  
  szukaj(G, V);

  puts("");

}
