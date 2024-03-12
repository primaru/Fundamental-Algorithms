#include <iostream>;
#include "Profiler.h";

Profiler profiler("average");

using namespace std;

int partition(int A[], int l, int r, Operation& comp, Operation& assig) {
	int x;

	x = A[r]; // take the last element as pivot
	int i = l - 1;
	for (int j = l; j <= r - 1; j++) {
		comp.count();
		if (A[j] <= x) { // swap any smaller element in the right side
			i++;
			assig.count(3);
			swap(A[i], A[j]);
		}

	}
	assig.count(3);
	swap(A[i + 1], A[r]);

	return i + 1;


}

int enhPartition(int A[], int l, int r, int casee, Operation& comp, Operation& assig, int size) {
	// this function selects the case for the partition ( best/average/worst )
	int i;
	if (casee == 2)
		return partition(A, l, r, comp, assig);
	else if (casee == 1 || casee == 0)
	{
		i = (l + r) / 2;
		swap(A[r], A[i]);
		return partition(A, l, r, comp, assig);
	}


}

void quickSortRand(int A[], int p, int r, int casee, int size) {

	Operation comp = profiler.createOperation("quicksort_comp", size);
	Operation assig = profiler.createOperation("quicksort_assig", size);

	int q;
	if (p < r) {
		q = enhPartition(A, p, r, casee, comp, assig, size); // get the partition done
		quickSortRand(A, p, q - 1, casee, size); // quicksort in left-side
		quickSortRand(A, q + 1, r, casee, size); // quicksort in right-side
	}

}
void maxHeapify(int a[], int i, int size, Operation& comp, Operation& assig) {

	int l = i << 1;
	int r = (i << 1) + 1;
	// Initialise the left and right child
	int maxx;
	
	if (l <= size) // search if one of the children is greater ( this violates the heap property )
	{
		if(a[l] > a[i])
		comp.count();
		maxx = l;
	}
	else
	{
		maxx = i;
	}
	
	if (r <= size)
	{
		
		if(a[r] > a[i])
		comp.count();
		maxx = r;
	}
	if (maxx != i) // if a child has found to be greater than its parent, swap them and repeat for above
	{
		
		assig.count(3);
		swap(a[i], a[maxx]);
		maxHeapify(a, maxx, size, comp, assig);
	}

}
void buildHeap(int a[], int size, Operation& comp, Operation& assig) {
	
	for (int i = size / 2; i >= 1; i--)
		maxHeapify(a, i, size, comp, assig);

}
void heapSort1(int a[], int size) {

	Operation comp = profiler.createOperation("heapsort_comp", size);
	Operation assig = profiler.createOperation("heapsort_assig", size);
	buildHeap(a, size, comp, assig);
	int i = size;
	for (i = size - 1; i > 1;i--) {
		assig.count(3);
		swap(a[1], a[i]);
		
		maxHeapify(a, 1, i, comp, assig);
	}

}
int quickSelect(int a[], int l,int r,int i,int size) {
	Operation comp = profiler.createOperation("uselessc", size);
	Operation assig = profiler.createOperation("uselessa", size);
	if (l == r) // base case
		return a[l];
	int q = partition(a, l, r, comp,assig);
	int k = q - l + 1;
	if (i == k) { // if the position was found
		return a[q];
	}
	else if (i < k) { // if it is in the left-side,search there
		return quickSelect(a, l, q - 1, i, size);
	}
	else // same for right, but "shift" i by k
		return quickSelect(a, q + 1, r, i - k, size);


}
void perf(int casee) {

	int const MAX_S = 5000;
	int const step = 100;
	int v[MAX_S], w[MAX_S];
	if (casee == 0)
	{
		for (int j = 0; j < 5; j++) {
			for (int i = 100; i < MAX_S; i += step) {
				FillRandomArray(v, i, 10, 10000, 0, UNSORTED);
				CopyArray(w, v, i);
				quickSortRand(v, 0, i - 1, casee, i);
				heapSort1(w, i);


			}
		}
		profiler.divideValues("quicksort_assig", 5);
		profiler.divideValues("quicksort_comp", 5);
		profiler.divideValues("heapsort_assig", 5);
		profiler.divideValues("heapsort_comp", 5);
	}
	else if (casee == 1)
	{
		for (int i = 100; i < MAX_S; i += step) {
			FillRandomArray(v, i, 10, 10000, 0, ASCENDING);
			//CopyArray(w, v, i);
			quickSortRand(v, 0, i - 1, casee, i);


		}
	}
	else if (casee == 2)
	{
		for (int i = 100; i < MAX_S; i += step) {
			FillRandomArray(v, i, 10, 10000, 0, ASCENDING);
			//bubbleso(v, i);
			//CopyArray(w, v, i);
			quickSortRand(v, 0, i - 1, casee, i);


		}
	}
	profiler.addSeries("quicksort_op", "quicksort_assig", "quicksort_comp");
	profiler.addSeries("heapsort_op", "heapsort_assig", "heapsort_comp");
	profiler.createGroup("op", "quicksort_op", "heapsort_op");
	profiler.createGroup("comp", "quicksort_comp", "heapsort_comp");
	profiler.createGroup("assig", "quicksort_assig", "heapsort_assig");

}
void demoQuickSort() {
	int A[7] = { 1,3,2,4,5,1,8 }, m = 7;
	cout << "Initial array: ";
	for (int i = 0; i < m; i++)
		cout << A[i] << " ";
	cout << endl;
	// 1 1 2 3 4 5 8
	cout << "After quickSort: ";
	quickSortRand(A, 0, m - 1, 0, m);
	for (int i =0; i < m; i++)
		cout << A[i] << " ";
	cout << endl;
}
void demoQuickSelect() {
	int A[7] = { 1,3,2,4,5,1,8 }, m = 7;
	int pos = 3;
	// 1 1 2 3 4 5 8
	int b=quickSelect(A, 0, m - 1, pos, m);
	cout << "The element at position " << pos << " is: " << b << endl;
	
}
int main() {
	demoQuickSort();
	demoQuickSelect();
	/*perf(1);
	profiler.reset();
	perf(0);
	profiler.reset();
	perf(2);
	profiler.showReport();*/
}