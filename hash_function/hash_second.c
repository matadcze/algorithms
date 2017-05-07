/* Wariant  [S + OL] */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX 60000l
#define MLD 1000000000.0

typedef long long ll;
typedef struct node node;

struct node
{
  int amount;
  char *surname;
};

ll
string2int (char *v)
{
  unsigned long long h = 0;
  int a = 111;
  for (; *v != '\0'; v++)
    h = a * h + *v;
  return h;
}

ll
hash_mul (char *surname, int m)
{
  int k = string2int (surname);
  return (ll) (fabs (m * (fmod (k * (sqrt (5) - 1) / 2.0, 1))));
}

int
linear (int k, int i, int m)
{
  return (k + i) % m;
}

int
hash_insert (node ** T, node * item, int m)
{
  int i = 0, j;
  int key = hash_mul (item->surname, m);
  do
    {
      key = linear (key, i, m);
      j = key;
      if (T[j] == NULL)
	{
	  T[j] = item;
	  return j;
	}
      i++;
    }
  while (i != m - 1);
  fprintf (stderr, "Hash table overflow\n");
  exit (1);
}

int
hash_search (node ** T, char *surname, int m)
{
  int i = 0;
  int key = hash_mul (surname, m);
  int j;
  do
    {
      key = linear (key, i, m);
      j = key;
      if (T[j] == NULL)
	{
	  i++;
	  continue;
	}
      if (!strcmp (T[j]->surname, surname))
	{
	  fprintf (stdout,
		   "Ilość prób: %d przy wyszukiwaniu nazwiska: %s.\n", i,
		   surname);
	  return j;
	}
      i++;
    }
  while (i != m - 1);

  fprintf (stderr, "Nie znaleziono nazwiska: %s w tablicy.\n", surname);
  return -1;
}

node *
new_item (int i, char *s)
{
  node *tmp = (node *) malloc (sizeof (node));
  tmp->surname = (char *) malloc (sizeof (char) * (strlen (s) + 1));
  tmp->amount = i;
  strcpy (tmp->surname, s);

  return tmp;
}

void
error (char *msg)
{
  fprintf (stderr, msg);
  return;
}

int
main (int argc, char **argv)
{
  struct timespec tp0, tp1;
  double sp;

  FILE *fi = fopen (argv[1], "r");
  if (argc != 3)
    {
      error ("Nie podano argumentów.\n");
      exit (3);
    }
  if (!fi)
    {
      fprintf (stderr, "Nie mogę otworzyć pliku %s.\n", argv[1]);
      exit (2);
    }
  long M = atoi (argv[2]);
  node **T = (node **) malloc (sizeof (node *) * M);
  int N = M * 0.8;		// wypełniam tablicę tylko do 80%
  if(N == 0)
    exit(32);
  int i = 0;
  int tmp_int;
  char tmp_string[255];
  /* wczytaj dane do tablicy */

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
  while (fscanf (fi, "%d %s", &tmp_int, tmp_string) == 2 && i != N)
    {
      node *tmp = (node *) malloc (sizeof (node));
      tmp->amount = tmp_int;
      tmp->surname =
	(char *) malloc (sizeof (char) * (strlen (tmp_string) + 1));
      strcpy (tmp->surname, tmp_string);
      hash_insert (T, tmp, M);
      i++;
    }

  hash_insert (T, new_item (3, "J"), M);
  /* hash_insert (T, new_item (31, "Ja"), M); */
  /* hash_insert (T, new_item (314, "Jan"), M); */
  /* hash_insert (T, new_item (3141, "Jane"), M); */
  /* hash_insert (T, new_item (31415, "Janek"), M); */


  hash_search (T, "Merkel", M);
  /* hash_search (T, "Ja", M); */
  /* hash_search (T, "Jan", M); */
  /* hash_search (T, "Jane", M); */
  /* hash_search (T, "Janek", M); */
  /* hash_search (T, "Janeko", M); */
  /* hash_search (T, "Janekow", M); */
  /* hash_search (T, "Janekows", M); */
  /* hash_search (T, "Janekowsk", M); */




  int nulls = 0;
  int j;
  for (j = 0; j < M; j++)
    {
      if (T[j] == NULL)
  	{
  	  nulls++;
  	  continue;
  	}
      /* debugowanie */
      /* else */
      /* { */
      /*   printf ("%d - %d - %s\n", j, T[j]->amount, T[j]->surname); */
      /* } */
    }
  printf ("M: %ld; N: %d; nulls: %d \n", M, N, nulls);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
  
  printf("PROCESS:\n");
  printf("start %12lu  %12lu \n",tp0.tv_sec, tp0.tv_nsec);
  printf("stop  %12lu  %12lu \n",tp1.tv_sec, tp1.tv_nsec);
  sp=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("czas   %3.5lf\n",sp);

  free(fi);

  return 0;
}
