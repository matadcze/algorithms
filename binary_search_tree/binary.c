#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX 60000l
#define MLD 1000000000.0

typedef struct BiTreeNode_
{
  int key;
  struct BiTreeNode_ *left;
  struct BiTreeNode_ *right;
  struct BiTreeNode_ *parent;
  int b;			// ilość powtórzeń węzła
} BiTreeNode;

typedef struct BiTree_
{
  BiTreeNode *root;
} BiTree;

void
bitree_init (BiTree * x)
{
  x->root = NULL;
  return;
}

void
inorder_tree_walk (BiTreeNode * x)
{
  if (x != NULL)
    {
      inorder_tree_walk (x->left);
      printf ("%p - %d - %d\n", x, x->key, x->b);
      inorder_tree_walk (x->right);
    }
  return;
}

void
postorder_tree_walk (BiTreeNode * x)
{
  if (x != NULL)
    {
      printf ("%p - %d - %d\n", x, x->key, x->b);
      inorder_tree_walk (x->left);
      inorder_tree_walk (x->right);
    }
  return;
}

void
preorder_tree_walk (BiTreeNode * x)
{
  if (x != NULL)
    {
      inorder_tree_walk (x->left);
      inorder_tree_walk (x->right);
      printf ("%p - %d - %d\n", x, x->key, x->b);
    }
  return;
}

/* tree_search
 * return BiTreeNode if found k
 * otherwise NULL
 */

BiTreeNode *
tree_search (BiTreeNode * x, int k)
{
  if (x == NULL || k == x->key)
    return x;
  if (k < x->key)
    return tree_search (x->left, k);
  else
    return tree_search (x->right, k);
}

BiTreeNode *
iterative_tree_search (BiTreeNode * x, int k)
{
  while (x != NULL && k != x->key)
    {
      if (k < x->key)
	x = x->left;
      else
	x = x->right;
    }
  return x;
}

BiTreeNode *
tree_minimum (BiTreeNode * x)
{
  while (x->left != NULL)
    x = x->left;
  return x;
}

BiTreeNode *
tree_maximum (BiTreeNode * x)
{
  while (x->right != NULL)
    x = x->right;
  return x;
}

BiTreeNode *
tree_successor (BiTreeNode * x)
{
  if (x->right != NULL)
    return tree_minimum (x->right);
  BiTreeNode *y = x->parent;
  while (y != NULL && x == y->right)
    {
      x = y;
      y = y->parent;
    }
  return y;
}

BiTreeNode *
tree_predecessor (BiTreeNode * x)
{
  if (x->left != NULL)
    return tree_maximum (x->left);
  BiTreeNode *y = x->parent;
  while (y != NULL && x == y->left)
    {
      x = y;
      y = y->parent;
    }
  return y;
}

BiTreeNode *
new_node (int k)
{
  BiTreeNode *tmp = (BiTreeNode *) malloc (sizeof (BiTreeNode));
  tmp->key = k;
  tmp->left = NULL;
  tmp->right = NULL;
  tmp->parent = NULL;
  tmp->b = 0;
  return tmp;
}


void
tree_switch (void)
{
  return;
}

void
tree_insert (BiTree * T, BiTreeNode * z)
{
  BiTreeNode *y = NULL;
  BiTreeNode *x = T->root;
  while (x != NULL)
    {
      y = x;			// na poczet przyszlych obliczen root
      if (z->key < x->key)
	x = x->left;
      else
	{
	  if (z->key == x->key)
	    {
	      x->b++;
	      return;
	    }
	  else
	    x = x->right;
	}
    }
  z->parent = y;		// rodzic z jest ustawiony na korzeń drzewa T
  if (y == NULL)
    T->root = z;		// tree T was empty
  else if (z->key < y->key)
    y->left = z;
  else
    {
      if (z->key == y->key)
	{
	  y->b++;
	  return;
	}
      else
	y->right = z;
    }
  return;
}

void
transplant (BiTree * T, BiTreeNode * u, BiTreeNode * v)
{
  if (u->parent == NULL)
    T->root = v;
  else if (u == (u->parent)->left)
    (u->parent)->left = v;
  else
    (u->parent)->right = v;

  if (v != NULL)
    v->parent = u->parent;

  return;
}

void
tree_delete (BiTree * T, BiTreeNode * z)
{
  if (z->left == NULL)
    transplant (T, z, z->right);
  else if (z->right == NULL)
    transplant (T, z, z->left);
  else
    {
      BiTreeNode *y = tree_minimum (z->right);
      if (y->parent != z)
	{
	  transplant (T, y, y->right);
	  y->right = z->right;
	  (y->right)->parent = y;
	}
      transplant (T, z, y);
      y->left = z->left;
      (y->left)->parent = y;
    }

  return;
}

int
main (int argc, char **argv)
{
  struct timespec tp0, tp1;
  double sp;

  BiTree *tree = (BiTree *) malloc (sizeof (BiTree));

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
  while (fscanf (file, "%d", &tmp) == 1 && size <= 10000)
    {
      tree_insert (tree, new_node (tmp));
      size++;
    }

  clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &tp1);

  printf ("PROCESS:\n");
  printf ("start %12lu  %12lu \n", tp0.tv_sec, tp0.tv_nsec);
  printf ("stop  %12lu  %12lu \n", tp1.tv_sec, tp1.tv_nsec);
  sp = (tp1.tv_sec + tp1.tv_nsec / MLD) - (tp0.tv_sec + tp0.tv_nsec / MLD);
  printf ("czas   %3.5lf\n", sp);

  return 0;
}
