/*
 * Red Black Tree
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 60000l
#define MLD 1000000000.0


enum Kolors { RED = 0, BLACK = 1 };

#define SZER_EKR 120
#define IL_POZ   10

typedef struct TreeNode_
{
  int key;
  struct TreeNode_ *left;
  struct TreeNode_ *right;
  struct TreeNode_ *p;
  enum Kolors color;
} TreeNode;

typedef struct Tree_
{
  TreeNode* root;
} Tree;


/* wartownik */
static TreeNode* nil;

void left_rotate(TreeNode** T, TreeNode* x){
  TreeNode* y;
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
  return;
}

void right_rotate(TreeNode** T, TreeNode* x){
  TreeNode* y = x->left;

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

  return;
}

void rb_insert_fixup(TreeNode** T, TreeNode* z){
  TreeNode* y;
  while(z->p->color == RED){
    if(z->p == z->p->p->left){
      y = z->p->p->right;
      if(y->color == RED){
        z->p->color = BLACK;
        y->color = BLACK;
        z->p->p->color = RED;
        z = z->p->p;
      }
      else {
        if(z == z->p->right){
          z = z->p;
          left_rotate(T, z);
        }
        z->p->color = BLACK;
        z->p->p->color = RED;
        right_rotate(T, z->p->p);
      }
    }
    else {
      y = z->p->p->left;
      if(y->color == RED){
        z->p->color = BLACK;
        y->color = BLACK;
        z->p->p->color = RED;
        z = z->p->p;
      }
      else {
        if(z == z->p->left){
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
  return;
}

void rb_insert(TreeNode** T, TreeNode* z){
  TreeNode* y = nil;
  TreeNode* x = *T;
  while(x != nil){
    y = x;
    if(z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->p = y;
  if(y == nil)
    *T = z;
  else if(z->key < y->key)
    y->left = z;
  else
    y->right = z;
  
  z->left = nil;
  z->right = nil;
  z->color = RED;
  rb_insert_fixup(T, z);
  return;
}

void rb_transplant(TreeNode** T, TreeNode* u, TreeNode* v){
  if(u->p == nil)
    *T = u;
  else if(u == u->p->left)
    u->p->left = v;
  else
    u->p->right = v;
  v->p = u->p;
  return;
}

void rb_delete_fixup(TreeNode** T, TreeNode* x){
  TreeNode* w;
  while(x != *T && x->color == BLACK){
    if(x == x->p->left){
      w = x->p->right;
      if(w->color == RED){
        w->color = BLACK;
        x->p->color = RED;
        left_rotate(T, x->p);
        w = x->p->right;
      }
      if(w->left->color == BLACK && w->right->color == BLACK){
        w->color = RED;
        x = x->p;
      }
      else {
        if(w->right->color == BLACK){
          w->left->color = BLACK;
          w->color = RED;
          right_rotate(T, w);
          w = x->p->right;
        }
        w->color = x->p->color;
        x->p->color = BLACK;
        w->right->color = BLACK;
        left_rotate(T, x->p);
        x = *T;
      }
    }
    else {
      w = x->p->left;
      if(w->color == RED){
        w->color = BLACK;
        x->p->color = RED;
        right_rotate(T, x->p);
        w = x->p->left;
      }
      if(w->right->color == BLACK && w->left->color == BLACK){
        w->color = RED;
        x = x->p;
      }
      else if(w->left->color == BLACK){
        w->right->color = BLACK;
        w->color = RED;
        left_rotate(T, w);
        w = x->p->left;
      }
      w->color = x->p->color;
      x->p->color = BLACK;
      w->left->color = BLACK;
      right_rotate(T, x->p);
      x = *T;
    }
  }
  x->color = BLACK;
  return;
}

TreeNode* rb_minimum(TreeNode* T){
  TreeNode* x = T;
  while (x->left != nil)
    x = x->left;
  return x;
}

TreeNode* rb_maximum(TreeNode* T){
  TreeNode* x = T;
  while (x->right != nil)
    x = x->right;
  return x;
}


// void rb_delete(TreeNode** T, TreeNode* z){
//   TreeNode* y = z;
//   TreeNode* x;
//   enum Kolors y_original_color = y->color;
//   if(z->left == nil){
//     x = z->right;
//     rb_transplant(T, z, z->right);
//   }
//   else if(z->right == nil){
//     x = z->left;
//     rb_transplant(T, z, z->left);
//   }
//   else {
//     y = rb_minimum(z->right);
//     y_original_color = y->color;
//     x = y->right;
//     if(y->p == z)
//       x->p = y;
//     else {
//       rb_transplant(T, y, y->right);
//       y->right = z->right;
//       y->right->p = y;
//     }
//     rb_transplant(T, z, y);
//     y->left = z->left;
//     y->left->p = y;
//     y->color = z->color;
//   }
//   if(y_original_color == BLACK){
//     rb_delete_fixup(T, x);
//     puts("pułapka");
//   }
  
//   free(z);

//   return;
// }


void print_node(TreeNode* n) {
  printf("  %d", n->key);
  if (n->color == RED)
    printf(" (red)\n");
  else
    printf(" (black)\n");
  return;
}

void rb_inorder(TreeNode* p) {
  if (p != nil) {
    rb_inorder(p->left);
    print_node(p);
    rb_inorder(p->right);
  }
}

TreeNode* rb_new_node(int key) {
  TreeNode* x  = (TreeNode*) malloc(sizeof(TreeNode));
  if(x == NULL)
    fprintf(stderr, "x jest nullem\n");
  x->key = key;
  x->left = nil;
  x->right = nil;
  x->p = nil;
  return x;
}



int max_int(int a, int b){
  return a > b ? a : b;
}

int min_int(int a, int b){
  return a < b ? a : b;
}

int max_length_path(TreeNode* T, int max_value){
  int t1 = 0;
  int t2 = 0;

  if(T == nil || T->left == NULL || T->right == NULL)
    return max_value;
  else {
    t1 = max_length_path(T->left, max_value);
    t2 = max_length_path(T->right, max_value);
    int value = max_int(t1, t2) + 1;
    return max_int(max_value, value);
  }
}

int min_length_path(TreeNode* T, int min_value){
  int t1 = 0, t2 = 0;
  int value;
  if(T == nil || T->left == NULL || T->right == NULL)
    return min_value;
  else {
    t1 = min_length_path(T->left, min_value);
    t2 = min_length_path(T->right, min_value);
    value = min_int(t1, t2) + 1;
    /* if(min_value != 0) */
    /*   return min_int(min_value, value); */
    /* else */
      return value;
  }
}

void red_node(TreeNode* T, int* red_count){
  if(T == nil || T->left == NULL || T->right == NULL)
    return;

  if(T->color == RED)
    *red_count += 1;

  red_node(T->left, red_count);
  red_node(T->right, red_count);
}


/*
 * DRUKOWANIE
 */
char wydruk[IL_POZ+1][SZER_EKR];

void drukujost(TreeNode* w, int l, int p,int poziom){
  int srodek = (l+p)/2;
  if (w==nil)   return; 
  wydruk[poziom][srodek]='*';
}

void drukujwew(TreeNode* w, int l, int p,int poziom){
  int srodek = (l+p)/2;
  int i,dl;
  char s[9];
  if (w==nil)    return;
  if (w->color==BLACK)
    dl=sprintf(s,"%d",w->key);
  else
    dl=sprintf(s,"%+d",w->key);
  for (i=0;i<dl;i++)
    wydruk[poziom][srodek-dl/2+i]=s[i];
  if (++poziom<IL_POZ){
    drukujwew(w->left,l,srodek,poziom) ;
    drukujwew(w->right,srodek+1,p,poziom) ;
  }
  else {
    drukujost(w->left,l,srodek,poziom) ;
    drukujost(w->right,srodek+1,p,poziom) ;
  }
}

void drukuj(TreeNode* w){
  int j,i;
  for (i=0;i<=IL_POZ;i++)
    for (j=0;j<SZER_EKR;j++)
      wydruk[i][j] = ' ';
  drukujwew(w,0,SZER_EKR,0);
  for (i=0;i<=IL_POZ;i++){
    for (j=0;j<SZER_EKR;j++)
      putchar(wydruk[i][j]);
    printf("\n");
  }
}

int main(int argc, char** argv){
  nil = (TreeNode*) malloc(sizeof(TreeNode*));
  nil->color = BLACK;
  nil->p = nil;
  nil->right = nil;
  nil->left = nil;
  struct timespec tp0, tp1;
  double sp;
  TreeNode* T = (TreeNode*)malloc(sizeof(TreeNode*));
  
  T = nil;
  
  FILE *file = fopen (argv[1], "rb");

  if (file == NULL)
    {
      fprintf (stderr, "%s: Nie udało mi się otworzyć pliku: %s\n",
               argv[0], argv[1]);
      exit (2);
    }

  clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &tp0);
  

  int tmp;
  int size = 0;
  while (fscanf (file, "%d", &tmp) == 1 &&  size <= 1000)
    {
      rb_insert(&T, rb_new_node(tmp));
      drukuj(T);

      size++;
    }
  


  clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &tp1);

  printf ("PROCESS:\n");
  printf ("start %12lu  %12lu \n", tp0.tv_sec, tp0.tv_nsec);
  printf ("stop  %12lu  %12lu \n", tp1.tv_sec, tp1.tv_nsec);
  sp = (tp1.tv_sec + tp1.tv_nsec / MLD) - (tp0.tv_sec + tp0.tv_nsec / MLD);
  printf ("czas   %3.5lf\n", sp);

  int max_value = 0;
  int min_value = 0;
  int red_count = 0;

  printf("Maksymalna glębokość liści = %d\nMinimalna głębokość liści = %d\n", max_length_path(T, max_value), min_length_path(T, min_value));

  red_node(T, &red_count);

<<<<<<< HEAD
  printf("Liczba czerwonych węzłów = %d\n", red_count);
=======
  printf("Liczba czerwonych węzłów = %d\n", red_count); 
>>>>>>> c8c94b596719398fd834e86569663ba451d85603

  rb_inorder(T);

    
  return 0;
}
