#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// WKC

#define MAX 60000l
#define MLD 1000000000.0

#define RED     0
#define BLACK   1

typedef struct node node;

struct node {
  int key, color;
  node *p;
  node *left;
  node *right;
};

node *nil;

void left_rotate(node **T, node *x) {
  node *y;
  y = x->right;
  x->right = y->left;
  if (y->left != nil)
    y->left->p = x;
  y->p = x->p;
  if (x->p == nil)
    *T = y;
  else if (x == x->p->left)
    x->p->left = y;
  else
    x->p->right = y;
  y->left = x;
  x->p = y;
}

void right_rotate(node **T, node *x) {
  node *y;
  y = x->left;
  x->left = y->right;
  if (y->right != nil)
    y->right->p = x;
  y->p = x->p;
  if (x->p == nil)
    *T = y;
  else if (x == x->p->right)
    x->p->right = y;
  else
    x->p->left = y;
  y->right = x;
  x->p = y;
}


void insert_fixup(node **T, node *z) {
  node *y;

  while (z->p->color == RED) {
    if (z->p == z->p->p->left) {
      y = z->p->p->right;
      if (y->color == RED) {
        z->p->color = BLACK;
        y->color = BLACK;
        z->p->p->color = RED;
        z = z->p->p;
      } else {
        if (z == z->p->right) {
          z = z->p;
          left_rotate(T, z);
        }
        z->p->color = BLACK;
        z->p->p->color = RED;
        right_rotate(T, z->p->p);
      }
    } else {
      y = z->p->p->left;
      if (y->color == RED) {
        z->p->color = BLACK;
        y->color = BLACK;
        z->p->p->color = RED;
        z = z->p->p;
      } else {
        if (z == z->p->left) {
          z = z->p;
          right_rotate(T, z);
        }
        z->p->color = BLACK;
        z->p->p->color = RED;
        left_rotate(T, z->p->p);
      }
    }
  }
  (*T)->color = BLACK;
}

void insert(node **T, node *z) {
  node *x, *y;
  x = *T;
  y = nil;
  while (x != nil) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->p = y;
  if (y == nil)
    *T = z;
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
  z->left = z->right = nil;
  z->color = RED;
  insert_fixup(T, z);
}

void print_node(node *p) {
  printf("%d", p->key);
  if (p->color == RED)
    printf(" (czerwone)\n");
  else
    printf(" (czarne)\n");
}

void preorder(node *p) {
  if (p != nil) {
    print_node(p);
    preorder(p->left);
    preorder(p->right);
  }
}

void inorder(node *p) {
  if (p != nil) {
    inorder(p->left);
    print_node(p);
    inorder(p->right);
  }
}

void destroy(node *p) {
  if (p != nil) {
    destroy(p->left);
    destroy(p->right);
    free(p);
  }
}

node *new_node(int key) {
  node *n;
  n = malloc(sizeof(node));
  n->key = key;
  n->left = NULL;
  n->right = NULL;
  n->p = NULL;
  return n;
}


int main(int argc, char **argv) {
  node *tree;

  nil = malloc(sizeof(node));
  nil->color = BLACK;
  nil->p = nil->left = nil->right = nil;

  tree = nil;
  int i;
  struct timespec tp0, tp1;
  double sp;
  clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &tp0);
  for(i = 0; i < 100000; i++){
    insert(&tree, new_node(i));
  }
  clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &tp1);
    
  printf ("PROCESS:\n");
  printf ("start %12lu  %12lu \n", tp0.tv_sec, tp0.tv_nsec);
  printf ("stop  %12lu  %12lu \n", tp1.tv_sec, tp1.tv_nsec);
  sp = (tp1.tv_sec + tp1.tv_nsec / MLD) - (tp0.tv_sec + tp0.tv_nsec / MLD);
  printf ("czas   %3.5lf\n", sp);
  
  /* inorder(tree); */
  destroy(tree);
  free(nil);

  return 0;
}
