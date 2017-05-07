#include <stdio.h>
#include <stdlib.h>

typedef struct set {
	struct set * p; // ojciec
	int key; // klucz
	int rank;
} set;

typedef struct node {
	 int v;
	 struct node * next;
} node;

typedef struct list {
	node * head;
} list;

typedef struct graph {
	int V; // ilość wierzchołków
	list * array;	
} graph;


node * new_node(int value){
	node * tmp = (node*) malloc(sizeof(node));
	tmp->v = value;
	tmp->next = NULL;
	return tmp;
}

graph * init_graph(int V){
	graph * tmp = (graph *) malloc(sizeof(graph));
	tmp->V = V;
	tmp->array = (list *) malloc(V * sizeof(list));
	for (int i = 0; i < V; ++i)
	{
		tmp->array[i].head = NULL;
	}
	return tmp;
}

set * make_set(int k){
	set * x = (set*) malloc(sizeof(set));
	x->key = k;
	x->p = x;
	x->rank = 0;
	return x;
}

set * find_set(set * x){
	if(x != x->p)
		x->p = find_set(x->p);
	return x->p;
}

void link(set* x, set* y){
	if(x->rank > y->rank)
		y->p = x;
	else {
		x->p = y;
		if(x->rank == y->rank)
			y->rank++;
	}
}

void union_set(set* x, set * y){
	link(find_set(x), find_set(y));
}

void print_set(set * x){
	printf("key = %d\n", x->key);
}

void kruskal(void){

}

int main(int argc, char const *argv[])
{
	graph * graph = init_graph(10);

	return 0;
}