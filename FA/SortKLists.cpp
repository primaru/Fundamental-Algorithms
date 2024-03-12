#include <list>
#include <iostream>
#include "Profiler.h"
/*

In this project, we will merge k lists using an algorithm based on a min-heap
Using this min-heap, we will keep track of the minimum from all the lists ( top of the lists ), and also by being a heap
it stores the minimum out of those minimums, which will be the top of the heap
using push(), we push each element from the top to another list which will be our final sorted list
By doing this approach, we will have a complexity of nlog(k)

*/

using namespace std;
Profiler profiler("average");

void generateList(int n, list<int>& my_list) { // this generates a list with random sorted elements
	int dummy_arr[10000];
	FillRandomArray(dummy_arr, n, 1, 20, false, ASCENDING);
	for (int i = 0; i < n; i++) {
		my_list.push_back(dummy_arr[i]);
	}

}
void minHeapify(list<int> a[], int i, int size, Operation& comp, Operation& assig) {

	int l = i << 1;
	int r = (i << 1) + 1;
	// Initialise the left and right child
	int minn=i;

	if (l <= size)
	{
		comp.count();
		if (a[l].front() < a[i].front())// search if one of the children is greater ( this violates the heap property )
		{
			minn = l;
		}
	}
	if (r <= size)
	{
		comp.count();
		if (a[r].front() < a[minn].front())
		{
			minn = r;
		}
	}
	if (minn != i) // if a child has found to be greater than its parent, swap them and repeat for above
	{
		assig.count(3);
		swap(a[i], a[minn]);
		minHeapify(a, minn, size, comp, assig);
	}

}
void buildHeap(list<int> a[], int size, Operation& comp, Operation& assig) {

	for (int i = size / 2; i >= 1; i--)
		minHeapify(a, i, size, comp, assig);

}
void generateRandomLists(int n, list<int> H[],int &k,int k2) { // this generates k random sorted lists
	int i = 1;
	srand(time(NULL));
	int r = 0;
	while (k2 > 0 && n>0) {
		if (k2 > 1)
		{
			if (n > 1)
				r = (rand() % (n / 2)) + 1;
			else
				r = 1;
			generateList(r, H[i]);
			cout << "list nr:" << i << " is: ";
			for (int j : H[i])
				cout << j << " ";
			cout << endl;
			i++;
			n = n - r;
			k2--;
		}
		else
		{
			generateList(n, H[i]);
			cout << "list nr:" << i << "is: ";
			for (int j : H[i])
				cout << j << " ";
			cout << endl;
			i++;
			k2--;
		}

	}
	k = i - 1;
}
void generateRandomLists2(int n, list<int> H[], int& k,int nrOfLists) { // this generates sorted lists with fixed number of total elements
	int i = 1;
	srand(time(NULL));
	int r = 0;
	while (n > 0 && nrOfLists>0) {
		if (nrOfLists > 1)
		{
			if (n > 1)
			{
				r = n / nrOfLists;
				if (r == 0)
					r = 1;
			}
			else
			{
				r = 1;
			}
			generateList(r, H[i]);
			i++;
			n = n - r;
			nrOfLists--;
		}
		else if(nrOfLists==1)
		{
			generateList(n, H[i]);
			nrOfLists--;
			i++;
			
		}

	}
	k = i - 1;
}
void generateRandomLists3(int n, list<int> H[], int nrOfLists) { // this generates random sorted lists with k fixed
	
	for (int i = 1; i <= nrOfLists;i++) {
		
		generateList(n, H[i]);
		
	
	}
	

}
void sortKLists(list<int> H[], int k,int n,list<int>& my_list,Operation comp,Operation assig) {
	
	list<int> a[10001]; // create the heap
	for (int i = 1; i <= k; i++)
		a[i] = H[i];
	buildHeap(a, k, comp, assig);

	while(k>0)
	{

		my_list.push_back(a[1].front()); // push every top of the heap so the minimum of the minimums
		a[1].pop_front();
		if (a[1].empty()) {

			assig.count(); // if it is empty, swap with the last and decrease the size
			swap(a[1], a[k]);
			k--;
		}
		minHeapify(a, 1, k, comp, assig);
	}
	
}
void perf() {
	int n = 1000;
	const int MAX_S = 500;
	const int step = 10;
	int i;
	list<int> H[10001];
	for (int j = 0; j < 5; j++)
	{
		
		for (int k = 10; k < MAX_S; k = k + step)
		{
			Operation comp = profiler.createOperation("list_comp", k);
			Operation assig = profiler.createOperation("list_assig", k);
			generateRandomLists2(n, H, i,k);
			list<int> my_list;
			sortKLists(H, i, k, my_list,comp,assig);
		}
	}
	
	profiler.divideValues("list_assig", 5);
	profiler.divideValues("list_comp", 5);
	profiler.addSeries("op", "list_comp", "list_assig");
}
void perf2() {
	int k;
	const int MAX_S = 10000;
	const int step = 200;
	int i;
	list<int> H[10001];
	for (int j = 0; j < 5; j++)
	{
		k = 5;
		for (int n = 200; n < MAX_S; n = n + step)
		{
			Operation comp = profiler.createOperation("k5_comp", n);
			Operation assig = profiler.createOperation("k5_assig", n);
			generateRandomLists3(n, H, k);
			list<int> my_list;
			sortKLists(H, k, k, my_list,comp,assig);
		}
	profiler.addSeries("op1", "k5_comp", "k5_assig");
		k = 15;
		for (int n = 200; n < MAX_S; n = n + step)
		{
			Operation comp = profiler.createOperation("k15_comp", n);
			Operation assig = profiler.createOperation("k15_assig", n);
			generateRandomLists3(n, H, k);
			list<int> my_list;
			sortKLists(H, k, k, my_list,comp,assig);
		}
	profiler.addSeries("op2", "k15_comp", "k15_assig");
	
		k = 100;
		for (int n =200; n < MAX_S; n = n + step)
		{
			Operation comp = profiler.createOperation("k100_comp", n);
			Operation assig = profiler.createOperation("k100_assig", n);
			generateRandomLists3(n, H, k);
			list<int> my_list;
			sortKLists(H, k, k, my_list,comp,assig);
		}
		profiler.addSeries("op3", "k100_comp", "k100_assig");
	}
	profiler.divideValues("k5_assig", 5);
	profiler.divideValues("k5_comp", 5);
	profiler.divideValues("k15_assig", 5);
	profiler.divideValues("k15_comp", 5);
	profiler.divideValues("k100_assig", 5);
	profiler.divideValues("k100_comp", 5);
	profiler.createGroup("totalcomp", "k5_comp", "k15_comp", "k100_comp");
	profiler.createGroup("totalop", "op1", "op2", "op3");
	profiler.createGroup("totalassig", "k5_assig", "k15_assig", "k100_assig");

}
void demo() {
	list<int> h[500];
	int n = 20,k=0;
	generateRandomLists(n,h,k,2);
	list<int> my_list;
	Operation comp = profiler.createOperation("k100_comp", n);
	Operation assig = profiler.createOperation("k100_assig", n);
	sortKLists(h, k, n, my_list, comp, assig);
	cout << endl;

	for(int i: my_list)
	{
		cout <<i << " ";
	}
	cout << endl;
}
void demo2() {
	list<int> h[500];
	int n = 60, k = 0;
	generateRandomLists(n, h, k, 6);
	list<int> my_list;
	Operation comp = profiler.createOperation("k100_comp", n);
	Operation assig = profiler.createOperation("k100_assig", n);
	sortKLists(h, k, n, my_list, comp, assig);
	cout << endl;

	for(int i:my_list)
	{
		cout << i << " ";
	
	}
}
int main() {
	demo();
	cout << endl;
	demo2();
	/*perf();
	profiler.reset();
	perf2();
	profiler.showReport();*/
	


}