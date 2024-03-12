#include <iostream>
#include "Profiler.h"

using namespace std;

Profiler profiler("average");

/*

The following project will contain functions that build a heap, mantain the heap property, and sort by the use of a heap (heapsort)
We will do 2 methods of implementing the "build" part of the heap, one that follows the bottom-up approach and one that follows the top-down approach
The bottom-up approach has a complexity of O(n) and the other has O(nlogn) so bottom-up strategy seems better.
Although, the top-down strategy has its own advantage, a huge one actually in particular cases, the one that it doesnt have constant size, so we can implement a priority queue using it


*/



/*
This function will mantain the heap property, having the max at the top
*/
void maxHeapify(int a[], int i,int size,Operation &comp,Operation &assig) {

	int l=i << 1 ;
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
		maxHeapify(a, maxx, size,comp,assig);
	}

}
/*

This function pushes one element after the other, and after that it is put in its right place by verifying until its parent is greater than it

*/
void pushHeap(int a[], int &size,int key,Operation &comp,Operation &assig) {
	assig.count();
	size++; // we need to increment the size as a new element is added
	assig.count();
	a[size] = key; // assign its key
	int i = size;
	comp.count();
	while (i>1 && a[i] > a[i / 2]) // verify wether it is greater than its parent or not
	{
		comp.count();
		assig.count(3);
		swap(a[i], a[i / 2]); // if so, swap them
		i = i / 2;
	}

}
/*

This function does the bottom-up strategy, more specificaly, it takes all the nodes from n/2 to 1 ( as the other half are considered as individual heaps )
and "heapifys" them, so that we create a bigger heap, leading to the final heap in the end

*/
void buildHeap(int a[], int size,Operation& comp,Operation& assig) {
	//Operation comp = profiler.createOperation("buildbu_comp", size);
	//Operation assig = profiler.createOperation("buildbu_assig", size);
	for (int i = size / 2; i >= 1; i--)
		maxHeapify(a, i, size,comp,assig);

}
/*

This function implements the top-down approach of the building strategy, this one pushes one element after another, at the end of the heap and afterwards it is "swam up" to the right position


*/
void buildHeapTopDown(int a[], int &size) {
	Operation comp = profiler.createOperation("buildtd_comp", size);
	Operation assig = profiler.createOperation("buildtd_assig", size);
	int size2 = 1;
	for (int i = 2; i <= size; i++)
	{
		pushHeap(a, size2, a[i],comp,assig);
	}
	size = size2;
}
/*

This function does the actual sort, which we can see its just building a heap, after that, swaps the first element with the last ( as the first one is always the max ) and puts it at the end
of the array and calls Heapify to mantain the heap property as it was broken, so in the end by doing this repeatedly, the array will be sorted

*/
void heapSort1(int a[], int size) {
	
	Operation comp = profiler.createOperation("heapsort_comp", size);
	Operation assig = profiler.createOperation("heapsort_assig", size);
	buildHeap(a, size,comp,assig);
	int size2 = size;
	while(size2>1) {
		assig.count(3);
		swap(a[1], a[size2]);
		size2--;
		maxHeapify(a, 1, size2,comp,assig);
	}

}


/*void demo() {

	int a[8] = { 0,1,2,4,3,1 }, i = 1, n = 5;
	cout << "initial array: ";
	for (i = 1; i <= n; i++)
		cout << a[i] << " ";
	cout << endl;
	buildHeap(a, n);
	cout << "after bottom-up strategy: ";
	for (i = 1; i <= n; i++)
		cout << a[i] << " ";
	int b[8] = { 0,1,2,4,3,1 }, m = 5;
	buildHeapTopDown(b, m);
	cout << endl<<"after top-down strategy: ";
	
	for (i = 1; i <= m; i++)
		cout << b[i] << " ";
	cout << endl;
	


}*/

void demoHeapsort() {

	int a[8] = { 0,1,2,4,3,1 }, i = 1, n = 5;
	heapSort1(a, n);
	cout << "after heapsort(initial array): ";
	for (i = 1; i <= n; i++)
		cout << a[i] << " ";
	cout << endl;
}

void perf(int casem) {
	int const MAX_S = 10000;
	int const step = 100;
	int v[MAX_S], w[MAX_S];
	if (casem == 0) {
		for (int j = 0; j < 5; j++)
		{
			for (int i = 100; i < MAX_S; i = i + step)
			{
				FillRandomArray(v, i, 10, 100000, false, UNSORTED);

				//CopyArray(w, v, i);

				heapSort1(v, i);
			}
		}
		profiler.divideValues("heapsort_assig", 5);
		//profiler.divideValues("buildtd_assig", 5);
		profiler.divideValues("heapsort_comp", 5);
		//profiler.divideValues("buildtd_comp", 5);
	}
	if (casem == 2)
	{
		for (int i = 100; i < MAX_S; i = i + step)
		{
			FillRandomArray(v, i, 10, 100000,true, DESCENDING);

			//CopyArray(w, v, i);

			heapSort1(v, i);
		}
	}
	if (casem == 1)
	{
		for (int i = 100; i < MAX_S; i = i + step)
		{
			FillRandomArray(v, i, 10, 100000, false, ASCENDING);

			//CopyArray(w, v, i);

			heapSort1(v, i);
		}
	}
		profiler.addSeries("heapsort_op", "heapsort_assig", "heapsort_comp");
		//profiler.addSeries("buildtd_op", "buildtd_assig", "buildtd_comp");
		//profiler.createGroup("op", "heapsort_op", "heapsort_op");
		//profiler.createGroup("assig", "heapsort_assig", "heapsort_assig");
		//profiler.createGroup("comp", "heapsort_comp", "heapsort_comp");
	

}

int main() {
	//demo();
	demoHeapsort();
	/*perf(0);
	profiler.reset();
	perf(1);
	profiler.reset();
	perf(2);
	profiler.showReport();*/


}