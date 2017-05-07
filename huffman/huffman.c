#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define parent(x) (((x) >> 1))
#define left_son(x) (((x) << 1) + 1)
#define right_son(x) ((((x) << 1) + 2))

typedef struct HuffNode {
  char sign;
  int freq;
  char* code;
  struct HuffNode * left;
  struct HuffNode * right;
} HuffNode;

int pos = 0;

int minimum(HuffNode** array){
  return array[0]->freq;
}

void swap(HuffNode** a, HuffNode** b){
  HuffNode* temp = *a;
  *a = *b;
  *b = temp;
  return;
}

void min_heapify(HuffNode** array, int heap_size, int i){
  int l = left_son(i);
  int r = right_son(i);
  int largest;

  if((l < heap_size) && (array[l]->freq < array[i]->freq))
    largest = l;
  else
    largest = i;

  if((r < heap_size) && (array[r]->freq < array[largest]->freq))
    largest = r;
  
  if(largest != i){
    swap(&array[largest], &array[i]);
    min_heapify(array, heap_size, largest);
  }
  return;
}

HuffNode* extract_min(HuffNode** array, int heap_size){
  HuffNode* min = array[0];
  array[0] = array[heap_size - 1];
  heap_size -= 1;
  min_heapify(array, heap_size, 0);
  return min;
}

void heap_increase_key(HuffNode** array, int i, HuffNode* key){
  if(key->freq > array[i]->freq){
    fprintf(stderr, "nowy klucz jest wiekszy niz aktualny klucz\n");
    return;
  }
  array[i] = key;
  while(i > 0 && array[parent(i)]->freq > array[i]->freq){
    swap(&array[i], &array[parent(i)]);
    i = parent(i);
  }
  return;
}

HuffNode* newNode(char sign, int freq){
  HuffNode* tmp = (HuffNode *) malloc(sizeof(HuffNode));
  tmp->sign = sign;
  tmp->freq = freq;
  tmp->code = malloc(255 * sizeof(char));
  return tmp;
}

void insert(HuffNode** array, int heap_size, HuffNode* key){
  array[heap_size] = newNode('\'', 123456789);
  heap_increase_key(array, heap_size, key);
  return;
}

void build_min_heap(HuffNode** array, int size){
  int i;
  for(i = parent(size)-1; i >= 0; i--)
    min_heapify(array, size, i);
  return;
}

HuffNode* huffman(HuffNode** dataset, int dataset_size, int* size){
  for(int i = 0 ; i < dataset_size - 1; i++){
    HuffNode * z = newNode('*', 0);

    HuffNode * x = extract_min(dataset, *size);
    *size -= 1;

    printf("x -> %c - %d\n", x->sign, x->freq);

    HuffNode * y = extract_min(dataset, *size);
    *size -= 1;

    printf("y -> %c - %d\n", y->sign, y->freq);


    z->left = x;
    strcat(x->code, "0");
    z->right = y;
    strcat(y->code, "1");
    z->freq = x->freq + y->freq;
    
    insert(dataset, *size, z);
    *size += 1;
  }
  return extract_min(dataset, *size);
}

void order(HuffNode * node){
  if (node != NULL) {
    order (node->left);
    printf ("%p - %c - %d - %s\n", (void *)node, node->sign, node->freq, node->code);
    order (node->right);
  }
  return;
}

void print_code(HuffNode *node, char * table, int depth)
{
  if(node->left == NULL){
    printf("%c > ", node->sign);
    puts(table);
  }
  else {
    table[depth] = '0';
    table[depth+1] = '\0';
    print_code(node->left, table, depth + 1);
    table[depth] = '1';
    table[depth+1] = '\0';
    print_code(node->right, table, depth + 1);
  }
}

void save_code(HuffNode** array, HuffNode *node, char * table, int depth) {
  if(node->left == NULL){
    array[pos]->sign = node->sign;
    strcpy(array[pos]->code, table);
    pos++;
  }
  else {
    table[depth] = '0';
    table[depth+1] = '\0';

    save_code(array , node->left, table, depth + 1);
    table[depth] = '1';
    table[depth+1] = '\0';

    save_code(array, node->right, table, depth + 1);
  }
}

void clean_string(char* array, int size){
  for(int i = 0; i < size; i++){
    array[i] = '\0';
  }
}

int search_sign(HuffNode ** saved_codes, int total_amout_of_letters, char ci){
  for (int i = 0; i < total_amout_of_letters; ++i)
    {
      if(saved_codes[i]->sign == ci){
	return i;
      }
    }
  return 0;
}

int main(void){
  int size;
  HuffNode* dataset[128];
  FILE *fp = fopen("article.txt", "r");

  if(fp == NULL){
    fprintf(stderr, "Nie udało otworzyć się pliku %s\n", "sample2.txt");
  }


  long int frequency[128];

  for (int i = 0; i < 128; ++i)
    frequency[i] = 0;
  

  char ci;
  while((ci = fgetc(fp)) != EOF)
    frequency[(int)ci]++;
  

  int j = 0;
  for (int i = 0; i < 128; ++i)
    if (frequency[i] != 0)
      dataset[j++] = newNode(i, frequency[i]);
  size = j - 1;
  
  int total_amout_of_letters = 0;
  int sum = 0;
  for (int i = 0; i < 128; ++i)
    if (frequency[i] != 0){
      sum += frequency[i];
      total_amout_of_letters++;
    }

  total_amout_of_letters -= 1;
  
  //printf("%d %d\n", sum, total_amout_of_letters);

  build_min_heap(dataset, size);

  HuffNode* tree = huffman(dataset, size, &size);
  
  char c[128];
  clean_string(c, 128);

  HuffNode ** saved_codes = (HuffNode**) malloc(128 * sizeof(HuffNode*));

  for (int i = 0; i < 128; i++)
    {
      saved_codes[i] = newNode('\\', 0);
      saved_codes[i]->code = (char *) malloc(128 * sizeof(char));
    }

  print_code(tree, c, 0);

  for(int i = 0; i < 128; i++){
    c[i] = '\0';
  }

  save_code(saved_codes, tree, c, 0);

  order(tree);

  for (int i = 0; i < total_amout_of_letters; ++i)
    {
      printf("%d - %c - %ld - %s\n", i, saved_codes[i]->sign, frequency[(int)saved_codes[i]->sign], saved_codes[i]->code);
    }

  int summa = 0;
  for (int i = 0; i < total_amout_of_letters; ++i)
    {
      summa += frequency[(int)saved_codes[i]->sign] * strlen(saved_codes[i]->code);
    }


  printf("Stosunek kodowanego tekstu do pierwotnego wynosi: %3.2lf.\n", (double) summa / (sum * 8));

  FILE * fw = fopen("kodowany.txt", "w");

  if (fw == NULL)
    {
      fprintf(stderr, "Nie można otworzyć pliku: %s\n", "kodowany.txt");
    }

  fseek(fp, 0, 0);
  while((ci = fgetc(fp)) != EOF){
    int x = search_sign(saved_codes, total_amout_of_letters, ci);
    fprintf(fw, "%s", saved_codes[x]->code);
  }

  fclose(fw);
  fclose(fp);

  return 0;
}
