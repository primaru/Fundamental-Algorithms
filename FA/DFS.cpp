#include <iostream>
#include <list>
#include <stack>
using namespace std;
typedef struct Node {
	int key=0;
	Node* parent=NULL;
	int color=0;
	Node** adj;
	int adjSize=0;
	bool inStack=0;
	int index = 0;
	int comp = 0;
	int lowlink = 0;
};

Node* createNode(int key)
{
	Node* aux = new Node;
	aux->key = key;
	aux->parent = NULL;
	aux->color = 0;
	aux->adjSize = 0;
	aux->inStack = 0;
	aux->adj = (Node**)malloc(10 * sizeof(Node*));
	return aux;
}
void createEdge(Node* x, Node* y) {
	x->adj[x->adjSize]=y;
	x->adjSize++;
}

void DFS(Node* x) {
	x->color = 1;
    cout << x->key<<" ";
	for (int i = 0; i < x->adjSize; i++)
	{
		if (x->adj[i]->color == 0)
		{
			x->adj[i]->parent = x;
			DFS(x->adj[i]);
		}
	}
	x->color = 2;

}
void StrongConnect(Node** G, Node* u,int *index,stack<Node*> *s,int nrComp) {
	u->index = u->lowlink = *index;
	(* index)++;
	(*s).push(u);
	u->inStack = true;
	for (int i = 0; i < u->adjSize;i++) {
		Node* v = u->adj[i];
		if (v->index == -1)
		{
			StrongConnect(G, v, index, s,nrComp);
			u->lowlink = min(u->lowlink, v->lowlink);
		}
		else if (v->inStack) {
			u->lowlink = min(u->lowlink, v->index);
		}
	}
	if (u->lowlink == u->index) {
		nrComp++;
		Node* v;
		do {
			v = (*s).top();
			cout << v->key<<" ";
			(*s).pop();
			v->inStack = false;
			v->comp = nrComp;
		} while (u != v);
		cout << endl;
	}

}
void Tarjan(Node** G, Node* x,int size) {
	int index = 0;
	stack<Node*> s;
	int nrComp = 0;
	int sizeAux = size;
	while (size > 1) {
		Node* u = G[size-1];
		u->index = u->lowlink = -1;
		u->inStack = false;
		u->comp = 0;
		size--;

	}
	while (sizeAux > 1) {
		Node* u = G[sizeAux-1];
		if (u->index == -1) {
			StrongConnect(G, u, &index, &s, nrComp);

		}
		sizeAux--;
	}
	if (s.size()) {
		cout << s.top()<<" ";
		s.pop();
	}


}
void TOPSORT(Node* x,Node** G,int *size) {
		x->color = 1;
		//cout << x->key << " ";
		for (int i = 0; i < x->adjSize; i++)
		{
			if (x->adj[i]->color == 0)
			{
				x->adj[i]->parent = x;
				TOPSORT(x->adj[i], G,size);
			}
		}
		x->color = 2;
		G[*size] = x;
		(*size)++;

	
}

void demo() {
	Node** F = new Node * [10];
	int n = 8;
	for (int i = 1; i <= n; i++)
		F[i] = createNode(i);
	createEdge(F[2], F[1]);
	createEdge(F[1], F[3]);
	createEdge(F[3], F[2]);
	createEdge(F[2], F[4]);
	createEdge(F[3], F[4]);
	createEdge(F[3], F[5]);
	createEdge(F[4], F[6]);
	createEdge(F[6], F[4]);
	createEdge(F[5], F[6]);
	createEdge(F[5], F[7]);
	createEdge(F[7], F[5]);
	createEdge(F[7], F[8]);
	createEdge(F[6], F[8]);

	//cout << n1->adj[0]->key;
	Node** G = new Node * [10];
	Node** G2 = new Node * [10];
	int size = 0;
	cout << "Graph before DFS:" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << F[i]->key << " ";
		for (int j = 0; j < F[i]->adjSize; j++)
		{
			cout << F[i]->adj[j]->key<<" ";
			
		}
		cout << endl;
	}
	cout << "Graph after DFS:" << endl;
	DFS(F[1]);
	cout << endl;
	cout << "Connected components after Tarjan:" << endl;
	Tarjan(F, F[1], n+1);
}
void demo2() {
	Node** F = new Node * [10];
	int n = 6;
	for (int i = 1; i <= n; i++)
		F[i] = createNode(i);
	createEdge(F[1], F[2]);
	createEdge(F[1], F[3]);
	createEdge(F[2], F[3]);
	createEdge(F[2], F[5]);
	createEdge(F[5], F[4]);
	createEdge(F[1], F[6]);
	//cout << n1->adj[0]->key;
	Node** G = new Node * [10];
	cout << "Graph before:" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << F[i]->key << " ";
		for (int j = 0; j < F[i]->adjSize; j++)
		{
			cout << F[i]->adj[j]->key << " ";

		}
		cout << endl;
	}
	int size = 0;
	//DFS(aux);
	cout << endl;

	TOPSORT(F[1], G, &size);
	
	size--;
	while (size>=0) {
		cout << G[size]->key << " ";
		size--;
	}
	cout << endl;
	
}
int main() {
	demo();
	demo2();
}