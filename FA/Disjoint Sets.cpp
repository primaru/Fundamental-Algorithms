#include <iostream>
#include <algorithm>
#include "Profiler.h"

using namespace std;
Profiler profiler("average");
typedef struct Node {
	int key;
	Node* p;
	int rank;
};
typedef struct Edge {
	int x;
	int y;
	int weight;
};
Node* Make_Set(int key,Operation& comp,Operation& assig) {
	Node* x = new Node;
	assig.count(3);
	x->p = x;
	x->rank = 0;
	x->key = key;
	return x;
}

Node* Link(Node* x, Node* y,Operation& comp,Operation& assig) {
	if (x->rank > y->rank)
	{
		comp.count();
		assig.count();
		y->p = x;
		cout << "current node is:" << y->key << " "<<"linked to:"<<x->key;
		return x;
	}
	else 
	{
		assig.count();
		x->p = y;
		cout << "current node is:" << x->key << " " << "linked to:" << y->key<<" ";
		if (x->rank == y->rank)
		{
			comp.count();
			assig.count();
			y->rank++;
		}
		return y;
	}
}
Node* Find_Set(Node* x,Operation& comp,Operation& assig) {
	if (x->p != x)
	{
		comp.count();
		assig.count();
		x = Find_Set(x->p,comp,assig);
	}
	return x;

}
void Union(Node* x, Node* y,Operation& comp,Operation& assig) {
	Node* aux = new Node;
	assig.count(3);
	aux=Link(Find_Set(x,comp,assig), Find_Set(y,comp,assig),comp,assig);
	x->p = aux;
	y->p = aux;

}
bool comp(Edge* A, Edge* B)
{
	return A->weight < B->weight;
}
Edge** Kruskal(Edge** E, int n, int m) {
	Operation comp = profiler.createOperation("set_comp", n);
	Operation assig = profiler.createOperation("set_assig", n);
	int A[1000][1000] = { 0 };
	Edge** G = new Edge * [m];
	int k = 0;
	Node** vertices = new Node * [n];
	for (int i = 0; i < n; i++)
		vertices[i] = Make_Set(i,comp,assig);
	for (int i = 0; i < m; i++)
	{
		sort(E, E + m, comp);
	}
	for (int i = 0; i < m; i++)
	{
		if (Find_Set(vertices[E[i]->x],comp,assig) != Find_Set(vertices[E[i]->y],comp,assig))
		{
			A[E[i]->x][E[i]->y] = E[i]->weight;
			G[k] = new Edge;
			G[k] = E[i];
			k++;
			Union(vertices[E[i]->x], vertices[E[i]->y],comp,assig);
		}
	}
	cout << endl;
	/*for (int i = 0; i < m; i++)
	{for (int j = 0; j < m; j++)
		{
			cout << A[i][j] << " ";
		}
	cout << endl;*/
	for (int i = 0; i < k; i++)
		cout << "x=" << G[i]->x << " y=" << G[i]->y << " weight=" << G[i]->weight << endl;
	return G;

}
//void perf() {
//	int step = 100;
//	int MAX = 1000;
//	int j;
//	srand(time(NULL));
//	Edge** E = new Edge * [1000];
//	for (int i = step; i <= MAX; i += step) {
//		int min = i % 10;
//		int max = i % 50;
//		for (j = 0; j < i; j++)
//			E[j] = new Edge{ j,j + 1,rand() % 300 };
//		for (int k = 0; k < min + rand() % (max + 1 - min); k++)
//		{
//			int aux1 = rand() % i;
//			int aux2 = rand() % i - 1;
//			if (aux1 != aux2)
//			{
//				E[j] = new Edge{ aux1,aux2,rand() % (max + 1 - min) };
//				j++;
//			}
//		}
//
//	}
//}
int main() {
	int m = 8;
	int n = 8;
	/*Node* a = new Node;
	a->key = 1;
	Node* b = new Node;
	b->key = 2;
	Node* c = new Node;
	c->key = 3;
	Node* d = new Node;
	d->key = 4;
	a=Make_Set(1);
	b=Make_Set(2);
	Union(a, b);
	c=Make_Set(3);
	d=Make_Set(4);
	Union(c, d);
	Union(a, c);
	cout << c->p->key;
	cout << a->p->key;
	cout << b->p->key;
	cout << d->p->key;*/
	Edge** E = new Edge* [m];
	E[0] = new Edge;
	E[0]->x = 0;
	E[0]->y = 1;
	E[0]->weight = 10;
	E[1] = new Edge;
	E[1]->x = 0;
	E[1]->y = 2;
	E[1]->weight = 20;
	E[2] = new Edge;
	E[2]->x = 1;
	E[2]->y = 3;
	E[2]->weight = 50;
	E[3] = new Edge;
	E[3]->x = 1;
	E[3]->y = 4;
	E[3]->weight = 10;
	E[4] = new Edge;
	E[4]->x = 2;
	E[4]->y = 4;
	E[4]->weight = 33;
	E[5] = new Edge{ 4,3,20 };
	E[6] = new Edge{ 4,5,1 };
	E[7] = new Edge{ 3,5,2 };
	Kruskal(E, n, m);
	for (int i = 0; i < m; i++)
		cout << " weight=" << E[i]->weight;
}