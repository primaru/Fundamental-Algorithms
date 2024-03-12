#include <iostream>;
#include "Profiler.h";

Profiler profiler("average");

using namespace std;

int partition(int A[],int l,int r,Operation& comp,Operation& assig) {
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

int enhPartition(int A[],int l,int r,int casee,Operation& comp,Operation& assig,int size) {
	int i;
	if (casee == 2)
		return partition(A, l, r, comp, assig);
	else if (casee == 1)
	{
		i = (l + r) / 2;
	}
	else if (casee == 0)
	{
		i = rand() % (l + r + 1);
	}
	assig.count(3);
	swap(A[r], A[i]);
	return partition(A, l, r, comp, assig);


}

void quickSortRand(int A[],int p,int r,int casee,int size) {
	
	Operation comp = profiler.createOperation("quicksort_comp", size);
	Operation assig = profiler.createOperation("quicksort_assig", size);
	int q;
	if (p < r) {
		q = enhPartition(A, p, r,casee,comp,assig,size);
		quickSortRand(A, p, q - 1,casee,size);
		quickSortRand(A, q + 1, r,casee,size);
	}

}

/*void quickSort(int A[], int p, int r) {
	int q;
	if (p < r) {
		q = partition(A, p, r);
		quickSort(A, p, q - 1);
		quickSort(A, q + 1, r);
	}

}*/
void maxHeapify(int a[], int i, int size, Operation& comp, Operation& assig) {

	int l = i << 1;
	int r = (i << 1) + 1;
	// Initialise the left and right child
	int maxx;
	comp.count();
	if (l <= size && a[l] > a[i]) // search if one of the children is greater ( this violates the heap property )
	{
		maxx = l;
	}
	else
	{
		maxx = i;
	}
	comp.count();
	if (r <= size && a[r] > a[i])
	{
		maxx = r;
	}
	if (maxx != i) // if a child has found to be greater than its parent, swap them and repeat for above
	{
		//A=A+3
		assig.count(3);
		swap(a[i], a[maxx]);
		maxHeapify(a, maxx, size, comp, assig);
	}

}

void buildHeap(int a[], int size,Operation& comp,Operation& assig) {
	
	for (int i = size / 2; i >= 1; i--)
		maxHeapify(a, i, size, comp, assig);

}
/*

This function does the actual sort, which we can see its just building a heap, after that, swaps the first element with the last ( as the first one is always the max ) and puts it at the end
of the array and calls Heapify to mantain the heap property as it was broken, so in the end by doing this repeatedly, the array will be sorted

*/
void heapSort1(int a[], int size) {
	int size2 = size;
	Operation comp = profiler.createOperation("heapsort_comp", size);
	Operation assig = profiler.createOperation("heapsort_assig", size);
	buildHeap(a, size,comp,assig);
	while (size2 > 1) {
		swap(a[1], a[size2]);
		size2--;
		maxHeapify(a, 1, size2, comp, assig);
	}

}

void perf(int casee) {
	int const MAX_S = 10000;
	int const step = 100;
	int v[MAX_S], w[MAX_S];
	if (casee == 0) {
		for (int j = 0; j < 5; j++)
		{
			for (int i = 100; i < MAX_S; i = i + step)
			{
				FillRandomArray(v, i, 10, 100000, false, UNSORTED);

				CopyArray(w, v, i);

				heapSort1(w, i);
				quickSortRand(v, 0, i - 1, casee,i);

				
			}
		}
		profiler.divideValues("heapsort_comp", 5);
		profiler.divideValues("heapsort_assig", 5);
		profiler.divideValues("quicksort_comp", 5);
		profiler.divideValues("quicksort_assig", 5);
	}
	else if (casee == 2)
	{
		for (int i = 100; i < MAX_S; i = i + step)
		{
			FillRandomArray(v, i, 10, 100000, false, ASCENDING);

			CopyArray(w, v, i);

			heapSort1(w, i);
			quickSortRand(v, 0, i - 1, casee,i);
		}
	}
	else if (casee == 1)
	{
		for (int i = 100; i < MAX_S; i = i + step)
		{
			FillRandomArray(v, i, 10, 100000, false, ASCENDING);
			FillRandomArray(w, i, 10, 100000, false, DESCENDING);

			heapSort1(w, i);
			quickSortRand(v, 0, i - 1, casee,i);
		}
	}

	profiler.addSeries("heapsort_op", "heapsort_comp", "heapsort_assig");
	profiler.addSeries("quicksort_op", "quicksort_comp", "quicksort_assig");
	profiler.createGroup("op", "quicksort_op", "heapsort_op");
	profiler.createGroup("assig", "quicksort_assig", "heapsort_assig");
	profiler.createGroup("comp", "quicksort_comp", "heapsort_comp");


}
void demoHeapsort() {

	int a[8] = { 0,1,2,4,3,1 }, i = 1, n = 5;
	heapSort1(a, n);
	cout << "after heapsort(initial array): ";
	for (i = 1; i <= n; i++)
		cout << a[i] << " ";
	cout << endl;
}


int main() {
	int A[10] = {1,4,2,5,3}, n = 5;
	quickSortRand(A, 0, n - 1,2,0);
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	//perf(1);
	//profiler.reset();
	/*perf(2);
	profiler.reset();
	/*perf(0);
	profiler.showReport();*/
}