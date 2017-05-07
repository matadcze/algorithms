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
/* lista (właściowa) */
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
/* kasuję pierwszy znaleziony element w liści */
void delete_item(node* Item, int integer);
void delete_all(node* Item);
bool empty(node* Item);
/* buduje listę po przez wczytanie liczb z pliku */

void initialize(node* Item){
  Item->prev = NULL;
  Item->next = guard;
}

void build_list(FILE *fi);
/* drukuje liste, od góry do dołu */
void print_list(node* A);

void scal(node* ItemA, node* ItemB){


}



/* testowanie */
int main(int argc, char **argv){
  struct timespec tp0, tp1;
  double sp;

  guard = (node*)malloc(sizeof(node));
  list  = (node*)malloc(sizeof(node));

  if(argc == 2){
    /* jeżeli podano plik z liczbami do wczytania to  */
    /* na tej podstawie zbudujemy listę */
    FILE* fi = fopen(argv[1], "r");

    if(!fi){
      fprintf(stderr, "Nie moge otworzyć pliku %s\n", argv[1]);
      exit(2);
    }
    build_list(fi);
    fclose(fi);
  } else if(argc == 3){
    FILE* fi = fopen(argv[1], "r");
    FILE* fo = fopen(argv[2], "r");
    if(!fi){
      fprintf(stderr, "Nie moge otworzyć pliku %s\n", argv[1]);
      exit(3);
    }
    if(!fo){
      fprintf(stderr, "Nie moge otworzyć pliku %s\n", argv[2]);
      exit(4);
    }
    build_list(fi);
    fclose(fi);
    fclose(fo);
  } 
  else {
    /* w przeciwnum wypadku zainicjalizujemy pustą listę */
    initialize(list);
  }



  /* initialize(list); */


  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);



  print_list(list);
  printf("=====================================\n");

  insert(list, newitem(123));
  insert(list, newitem(314));
  insert(list, newitem(14654165));

  
  print_list(list);

  printf("=====================================\n");


  int liczba = 314;
  node* tmp = search(list, liczba);

  if(tmp == NULL)
    fprintf(stderr, "Nie znaleziono węzła z wartością %d\n", liczba);
  else
    printf("Węzeł o adresie %p, przechowuje wartość %d\n", tmp, tmp->i);

  printf("=====================================\n");
  delete_item(list, 123); // ?
  delete_item(list, 1);
  delete_item(list, 12);
  delete_item(list, 10); // ?
  delete_item(list, 9);
  delete_item(list, 8);
  delete_item(list, 7);
  delete_item(list, 2);
  delete_item(list, 3);
  delete_item(list, 314); // ?
  delete_item(list, 123);

  printf("=====================================\n");

  print_list(list);

  printf("====================================\n");
  
  if(empty(list))
    printf("Lista jest pusta\n");
  else
    printf("Lista nie jest pusta\n");

  delete_all(list);

  printf("====================================\n");
  
  if(empty(list))
    printf("Lista jest pusta\n");
  else
    printf("Lista nie jest pusta\n");

  printf("=====================================\n");

  print_list(list);

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);

  
  printf("PROCESS (linked_list):\n");
  printf("start %12lu  %12lu \n",tp0.tv_sec, tp0.tv_nsec);
  printf("stop  %12lu  %12lu \n",tp1.tv_sec, tp1.tv_nsec);
  sp=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("czas   %3.5lf\n",sp);

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
  // @global list
  // ustawiam nowy 'head' do listy
  list = newItem;
}


/* funkcja search zwraca adres tylko */
/* pierwszego elementu znalezionego w  */
/* liście, pozostałe powtórzenia tej wartości */
/* zostają zignorowane */
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
  return;
}

void delete_all(node* Item){
  node* p = Item;
  for( ; p->next != guard; p = p->next)
    ;

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

void build_list(FILE *fi){
  int tmp = 0;
  node *tmp_node = (node* )malloc(sizeof(node));
  
  initialize(tmp_node);

  while(fscanf(fi, "%d", &tmp) == 1){
    insert(tmp_node, newitem(tmp));
    tmp_node = list;
    /* list = tmp_node; */
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
