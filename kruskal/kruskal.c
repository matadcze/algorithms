#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct set {
	struct set * p; // ojciec
	int key; // klucz
	int rank;
} set;

typedef struct edge {
	int u, v, w;
} edge;


edge * init_edges(int E){
	return (edge *) malloc(E * sizeof(edge));
}

set ** init_vertices(int V){
	set ** tmp = (set **) malloc(V * sizeof(set *));
	return tmp;
}

void add_edge(edge * edge, int i, int u, int v, int w){
	edge[i].u = u;
	edge[i].v = v;
	edge[i].w = w;
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

void sort(edge* e, int E){
	edge temp;
	for(int i = 0; i< E -1; i++){
		for(int j = i + 1; j< E; j++){
			if(e[j].w < e[i].w)
			{
				temp = e[j];
				e[j] = e[i];
				e[i] = temp;
			}
		}
	}
}

bool * kruskal(edge * edges, int E, set ** vertices, int V){
	bool * A = (bool *) malloc(E * sizeof(bool));

	for (int i = 0; i < V; ++i)
		vertices[i] = make_set(i);

	sort(edges, E);

	for (int i = 0; i < E; ++i)
	{
		if(find_set(vertices[edges[i].u]) != find_set(vertices[edges[i].v])){
			union_set(vertices[edges[i].u], vertices[edges[i].v]);
			A[i] = true;
		} else {
			A[i] = false;
		}
	}

	return A;
}

void print_edges(edge * edges, int E){
	for(int i = 0; i < E; i++){
		printf("e = (%d, %d) w = %d\n", edges[i].u, edges[i].v, edges[i].w);
	}
}

void print_solution(edge * edges, int E, bool * A){
	for(int i = 0; i < E; i++){
		if(A[i] == true){
			printf("e = (%d, %d) w = %d\n", edges[i].u, edges[i].v, edges[i].w);
		}
	}
}

int main(int argc, char const *argv[])
{
	int V = 6;
	int E = 6;

	edge * edges = init_edges(E);
	set ** vertices = init_vertices(V);

	//add_edge(i, u, v, w);

	add_edge(edges, 0, 1, 2, 5);
	add_edge(edges, 1, 1, 3, 3);
	add_edge(edges, 2, 2, 3, 4);
	add_edge(edges, 3, 3, 4, 10);
	add_edge(edges, 4, 3, 5, 11);
	add_edge(edges, 5, 4, 5, 2);

	//print_edges(edges, E);

	bool * A = kruskal(edges, E, vertices, V);
	
	//print_edges(edges, E);


	print_solution(edges, E, A);



	return 0;
}