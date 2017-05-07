#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX 60000l
#define MLD 1000000000.0

typedef struct node node;
struct node{
  int i;
  node *prev;
  node *next;
};

/* wartownik */
node* guard;
/* lista (właściwa) */
node* list;
/* tworzy nowy element */
node* newitem(int integer);
/* wstawia nowy element do listy */
void insert(node* Item, node* newItem);
/* funkcja search zwraca adres tylko */
/* pierwszego elementu znalezionego w  */
/* liście, pozostałe powtórzenia tej wartości */
/* zostają zignorowane */
node* search(node* Item, int integer);
/* kasuje pierwszy znaleziony element w liści */
void delete_item(node* Item, int integer);
void delete_all(node* Item);
bool empty(node* Item);
bool/* inicjalizacja listy */
void initialize(node* Item);
/* buduje listę poprzez wczytanie liczb z pliku */
void build_list(FILE *fi);
/* drukuje liste, od góry do dołu */
void print_list(node* A);

/* testowanie */
int main(int argc, char **argv){
  guard = (node*)malloc(sizeof(node));
  list  = (node*)malloc(sizeof(node));

  if(argc == 2){
    /* jeżeli podano plik z liczbami do wczytania, to  */
    /* na tej podstawie zbudujemy listę */
    FILE* fi = fopen(argv[1], "r");

    if(!fi){
      fprintf(stderr, "Nie moge otworzyć pliku %s\n", argv[1]);
      exit(2);
    }
    build_list(fi);
    fclose(fi);
  }
  else {
    /* w przeciwnum wypadku zainicjalizujemy pustą listę */
    initialize(list);
  }


  free(list);
  free(guard);
  
  return 0;
}
node* newitem(int integer){
  node *tmp = (node *) malloc(sizeof(node));
  if(tmp == NULL){
    fprintf(stderr, "Nie zaalakowano pamięci dla nowego elemetu.");
    return NULL;
  }
  tmp->i = integer;
  tmp->prev = NULL;
  tmp->next = NULL;
  return tmp;
}

void insert(node* Item, node* newItem){
  newItem->next = Item;
  if(Item != NULL){
    Item->prev = newItem;
  }
  list = newItem;
  return;
}

node* search(node* Item, int integer){
  node* p;
  for(p = Item; p->next != guard; p = p->next){
    if(p->i == integer)
      return p;
  }
  return NULL;
}

void delete_item(node* Item, int integer){
  node* p = search(Item, integer);
  if(p == NULL){
    fprintf(stderr, "(delete_item) Nie znaleziono elementu na liście %d.\n",integer);
    return;
  }
  else {
    if(p->prev == NULL){
      Item = p->next;
      Item->prev = NULL;
    }
    else {
      (p->prev)->next = p->next;
      (p->next)->prev = p->prev;
    }
    list = Item;
    free(p);
  }
}

void delete_all(node* Item){
  node* p = guard;
  for( ; p->prev != NULL; p = p->prev)
    free(p);
  Item->next = guard;
  return;
}

bool empty(node* Item){
  if(Item->next == guard)
    return true;
  else
    return false;
}

void initialize(node* Item){
  Item->prev = NULL;
  Item->next = guard;
  guard->prev = Item;
  return;
}

void build_list(FILE *fi){
  int tmp = 0;
  node *tmp_node = (node* )malloc(sizeof(node));
  initialize(tmp_node);
  while(fscanf(fi, "%d", &tmp) == 1){
    insert(tmp_node, newitem(tmp));
    tmp_node = list;
  }
  return;
}

void print_list(node* A){
  node *p;
  for(p = A ; p->next != guard; p = p->next){
    printf("%p - %d\n", p, p->i);
  }
  return;
}
