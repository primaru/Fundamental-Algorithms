#include "Profiler.h"

#include <iostream>
using namespace std;
Profiler profiler("average");

typedef struct Node {
	int value = 0;
	Node* left = NULL;
	Node* right = NULL;
	Node* parent = NULL;
	int size = 0;
};

Node* build(Node* root, int l, int r, int a[]) {
	if (l <= r)
	{
		int mij = (l + r) / 2;
		root->left = new Node;
		root->right = new Node;
		root->size = r - l + 1;
		root->value = a[mij];
		if (root->left != NULL)
			root->left->parent = root;
		if (root->right != NULL)
			root->right->parent = root;
		root->left = build(root->left, l, mij - 1, a);
		root->right = build(root->right, mij + 1, r, a);
		return root;
	}
	return NULL;


}
void inorderIterative(Node* root,int size) {
	Operation op = profiler.createOperation("inorder_op", size);
	if (root) {
		int dir = 1;
		while (root->parent || dir != 3) {
			//cout << " dir=" << dir << "val=" << root->value<<" "<<"parent="<<root->parent->value<<" ";
			if (dir == 1)
			{
				if (root->left)
					root = root->left;
				else
					dir = 2;
			}
			else if (dir == 2)
			{
				op.count();
				cout << root->value << " ";
				if (root->right)
				{
					root = root->right;
					dir = 1;
				}
				else
					dir = 3;
			}
			else if (dir == 3)
			{
				if (root == root->parent->left)
				{
					dir = 2;
					root = root->parent;
				}

				else if (root == root->parent->right)
				{
					dir = 3;
					root = root->parent;
				}


			}
		}
	}
	else cout << "invalid input";
}
Node* inorder(Node* root,int size) {
	//Operation op = profiler.createOperation("inorderIterative_op", size);
	if (root == NULL)
		return NULL;
	if (root->left != NULL)
		inorder(root->left,size);
	//op.count();
	cout << root->value<<" ";
	if (root->right != NULL)
		inorder(root->right,size);

}
int partition(int A[], int l, int r, Operation& comp, Operation& assig) {
	int x;
	x = A[r];
	int i = l - 1;
	for (int j = l; j <= r - 1; j++) {
		comp.count();
		if (A[j] <= x) {
			i++;
			assig.count(3);
			swap(A[i], A[j]);
		}
		//a=a+3;
	}
	assig.count(3);
	swap(A[i + 1], A[r]);

	return i + 1;


}
void InsertionSort(int A[], int n,Operation& comp,Operation& assig) {
	int i, j, nr;
	for (int i = 1; i < n; i++) {
		assig.count();
		nr = A[i];
		j = i - 1;
		while (j >= 0 && A[j] > nr) {
			comp.count();
			assig.count();
			A[j + 1] = A[j];
			j--;
		}
		assig.count();
		A[j + 1] = nr;
	}
}
int enhPartition(int A[], int l, int r, int casee, Operation& comp, Operation& assig) {
	int i;
	if (casee == 2)
		return partition(A, l, r, comp, assig);
	else if (casee == 1)
	{
		i = (l + r) / 2;
	}
	else if (casee == 0)
	{
		i = rand() % (l + r);
	}
	assig.count(3);
	swap(A[r], A[i]);
	return partition(A, l, r, comp, assig);


}

void quickSortRand(int A[], int p, int r, int casee, int size) {

	Operation comp = profiler.createOperation("quicksort_comp", size);
	Operation assig = profiler.createOperation("quicksort_assig", size);
	int q;
	if (p < r) {
		q = enhPartition(A, p, r, casee, comp, assig);
		quickSortRand(A, p, q - 1, casee, size);
		quickSortRand(A, q + 1, r, casee, size);
	}

}
void quickSortH2(int A[], int p, int r, int casee, int size) {
	Operation comp = profiler.createOperation("Hybrid_comp", size);
	Operation assig = profiler.createOperation("Hybrid_assig", size);
	int q;
	int th = 30;
	int size2 = r - p + 1;
	if (p < r) {
		if (size2 > th)
		{
			q = enhPartition(A, p, r, casee, comp, assig);
			quickSortH2(A, p, q - 1, casee, size);
			quickSortH2(A, q + 1, r, casee, size);
		}
		else
			InsertionSort(A + p, size2, comp, assig);
	}

}
void quickSortH3(int A[], int p, int r, int casee,int th, int size) {
	Operation comp = profiler.createOperation("Hybrid_comp", size);
	Operation assig = profiler.createOperation("Hybrid_assig", size);
	int q;
	int size2 = r - p + 1;
	if (p < r) {
		if (size2 > th)
		{
			q = enhPartition(A, p, r, casee, comp, assig);
			quickSortH3(A, p, q - 1, casee, th,size);
			quickSortH3(A, q + 1, r, casee, th,size);
		}
		else
			InsertionSort(A + p, size2, comp, assig);
	}

}

void qsTime(int A[], int p,int r,int casee,int size) {
	profiler.startTimer("normal_time", size);
	for (int i = 0; i < 20; i++) {
		quickSortRand(A,p,r,casee,size);
	}
	profiler.stopTimer("normal_time", size);
}
void qsHTime(int A[], int p, int r, int casee, int size) {
	profiler.startTimer("hybrid_time", size);
	for (int i = 0; i < 20; i++) {
		quickSortH2(A, p, r, casee, size);
	}
	profiler.stopTimer("hybrid_time", size);
}
void perf() {
	int step = 100;
	int MAX = 10000;
	int a[10001];
	for (int i = 100; i <= MAX; i += step)
	{
		Node* root = new Node;
		for (int j = 0; j < i; j++)
			a[j] = j+1;
		root->value = a[i / 2];
		build(root, 0, i - 1, a);
		inorder(root,i);
		cout << endl;
		inorderIterative(root,i);
		cout << endl;

	}
}
void perf2() {
	int step = 100;
	int MAX = 5000;
	int A[10001];
	int B[10001];
	for (int j = 0; j < 5; j++)
	{
		for (int i = 100; i <= MAX; i += step) {
			FillRandomArray(A, i, 0, 1000, false, 0);
			CopyArray(B, A, i);
			quickSortRand(A, 0, i - 1, 1, i);
			CopyArray(A,B, i);
			qsTime(A, 0, i - 1, 1, i);
			CopyArray(A, B, i);
			qsHTime(A, 0, i - 1, 1, i);
			quickSortH2(B, 0, i - 1, 1, i);
		}
	}
	profiler.divideValues("Hybrid_comp", 5);
	profiler.divideValues("Hybrid_assig", 5);
	profiler.divideValues("quicksort_comp", 5);
	profiler.divideValues("quicksort_assig", 5);
	profiler.addSeries("Hybrid_op", "Hybrid_comp", "Hybrid_assig");
	profiler.addSeries("quicksort_op", "quicksort_comp", "quicksort_assig");
	profiler.createGroup("op", "Hybrid_op", "quicksort_op");
	profiler.createGroup("comp", "Hybrid_comp", "quicksort_comp");
	profiler.createGroup("assig", "Hybrid_assig", "quicksort_assig");
	profiler.createGroup("time", "hybrid_time", "normal_time");
}
void perf3() {
	int step = 1;
	int MAX = 100;
	int A[100];
	int B[100];
	FillRandomArray(A, MAX, 100, 1000, false, 0);
	for (int i = 1; i <= MAX; i += step) {
		CopyArray(B, A, MAX);
		quickSortH3(B, 0, MAX - 1, 1, i, i);
	}
	profiler.addSeries("Hybrid_op", "Hybrid_comp", "Hybrid_assig");

}
void perf4() {
	int step = 1;
	int MAX = 100;
	int A[100];
	int B[100];
	FillRandomArray(A, MAX, 100, 1000, false, 0);
	/*for (int i = 1; i <= 30; i++)
	{
		CopyArray(B, A, MAX);
		quickSortH3(A, 0, MAX - 1, 1, i, i);
		
	}*/
	CopyArray(B, A, MAX);
	quickSortH3(B, 0, MAX - 1, 1, 30, 1);
	CopyArray(B, A, MAX);
	quickSortH3(B, 0, MAX - 1, 1, 35, 2);
	profiler.addSeries("Hybrid_op", "Hybrid_comp", "Hybrid_assig");
}
void demo() {
	Node* root = new Node;
	int a[] = { 1,2,3,4,5,6,7,8,9,10 };
	int n = 10;
	root->value = a[n / 2];
	build(root, 0, n - 1, a);
	inorder(root,0);
	cout << endl;
	inorderIterative(root,0);
}
int main() {
	int A[] = { 5,7,1,6,2,3,4,8,13,21,45,0 };
	int n = 12;
	//quickSort(A,0,n-1, n);
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
	demo();
	//perf();
	//perf2();
	//perf3();
	//perf3();
	//profiler.showReport();
	


}