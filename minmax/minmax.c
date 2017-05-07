#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ll long long

#define MAX 60000l
#define MLD 1000000000.0

void minmax(ll* A, ll n, ll* min, ll* max){
  ll i = 0;
  
  if(n % 2 == 0){
    if(A[0] < A[1]){
      *max = A[1];
      *min = A[0];
    }
    else {
      *max = A[0];
      *min = A[1];
    }

    for(i = 2 ; i < n; i += 2){
      ll j = i + 1;
      if(A[i] < A[j]){
	if(A[i] < *min)
	  *min = A[i];
	if(A[j] > *max)
	  *max = A[j];
      }
      else {
	if(A[i] > *max)
	  *max = A[i];
	if(A[j] < *min)
	  *min = A[j];
      }
    }
  } 
  else {
    *min = A[0];
    *max = A[0];
    for(i = 1 ; i < n; i += 2){
      ll j = i + 1;
      if(A[i] < A[j]){
	if(A[i] < *min)
	  *min = A[i];
	if(A[j] > *max)
	  *max = A[j];
      }
      else {
	if(A[i] > *max)
	  *max = A[i];
	if(A[j] < *min)
	  *min = A[j];
      }
    }
  }
  return;
} 

int main(int argc, char** argv){
  struct timespec tp0, tp1;
  double sp;
  ll* A = (ll*)malloc(sizeof(ll)*1000001);
  ll size = 0;
  if(argc != 2){
    fprintf(stderr,"Spróbuj `minmax in.file'\n");
    exit(1);
  }

  FILE* fi = fopen(argv[1], "r");

  if(!fi){
    fprintf(stderr, "Nie moge otworzyć pliku %s\n", argv[1]);
    exit(2);
  }
  
  while(fscanf(fi,"%lld", &A[size]) == 1)
    size++;

  ll min = 0;
  ll max = 0;

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

  minmax(A, size, &min, &max);

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
  
  printf("PROCESS:\n");
  printf("start %12lu  %12lu \n",tp0.tv_sec, tp0.tv_nsec);
  printf("stop  %12lu  %12lu \n",tp1.tv_sec, tp1.tv_nsec);
  sp=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("czas   %3.5lf\n",sp);
  printf("Min: %lld\nMax: %lld\n", min, max);
  
  fclose(fi);
  free(A);
  
  return 0;
}
