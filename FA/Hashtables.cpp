#include <iostream>
#include "Profiler.h";
/*


In this project we create and use a Hashtable for a better insertion and search of an item ( in the best or average case )
This hastable will hold as "indexes" the key of a structure, which key has to be unique and that key will be stored in the hashtable, not the whole structure
We will use a quadratic hash function as it is decently efficient for our needs (key+3*i+i^2)%n
Both the search and the insertion have O(1) in the best case, O(n) in the worst case
By using quadratic probing we want to lower the chances of getting into a worst case



*/
using namespace std;
typedef struct Node {
	int key;
	char c;
};
int quadraticProbing(int k, int i, int n) {
	int calc= (k%n + 3 * i + 5 * i * i) % n;
	//cout<<"calcul= "<<calc << endl;
	return calc;
}
int hashInsert(int T[],Node k,int n) { // this function inserts in the hashtable by using the quadratic probing
	int i = 0;
	int ok=0;
	while (i < n) {
		int j = quadraticProbing(k.key, i,n);
		if (T[j] == 0 || T[j]==-1)
		{
			T[j] = k.key;
			ok = 1;
			//cout << "element with key:" << k.key << " inserted at position: " << j << endl;
			return j;
		}
		else
			i++;
	}
	if (ok == 0)
	{
		//cout << "hash full";
	}
	return -1;
}
int hashSearch(int T[],int k, int n,int del) { // this function searches for an element and can also delete it if del=1, and it returns the rehash idex ( equal to the nr of trials to insert an item )
	int i = 0;
	while (i < n) {
		int j = quadraticProbing(k, i, n);
		if (T[j] == k)
		{
			if (del == 1)
			{
				T[j] = -1;
				cout << "element with key:" << k << " has been succesfully deleted"<<endl;
				return -1;
			}
			else
			{
				cout << "element with key:" << k << " has been found" << endl;
				return i + 1;
			}
		}
		else if (T[j] == 0) {
			cout << "element with key:" << k << " does not exist" << endl;
			return i+1;
			
			
		}
		i++;
	}
	cout << "element with key:" << k << " does not exist" << endl;
	return i;
	
}
void insertArray(int a[],int fill,Node Nodes[]) { // this function is helping inserting random elements as keys
	FillRandomArray(a, fill, 1, 1000000, true, 0);
	
	for (int i = 0; i < fill; i++)
	{
		Nodes[i].key = a[i];
		Nodes[i].c = 'c';
	}
	
}
float roundd(float var)
{
	float value = (int)(var * 100 + .5);
	return (float)value / 100;
}
void hashDelete(int T[], int key,int n) { // this function deletes by activating "del" in search
	hashSearch(T, key, n,1);

}
void avMaxFoundUniformly(int T[], int aux[], int n,int fill,int& max,float& value) { // this found is uniformly choosing elements to be searched ( which we know they are already there )
	float nrtries = 0;
	 value = 0;
	float avg = 0;
	float sum = 0;
	 max = 0;
	int j = 0;
	int ok;
	int parts = fill / 1500;
	int prov = 0;
	for (int i = 1; i < fill; i=i+parts)
	{
		prov = hashSearch(T, aux[i], n, 0);
		if (max < prov)
			max = prov;
		nrtries++;
		sum += prov;

	}
	value = sum / nrtries;
	//cout << "              " << roundd(value) << "                            " << max;
	

}

void avMaxFound(int T[],int aux[],int n,int& max,float& value) { // this does the same as the one above but nonuniformly
	float nrtries = 0;
	float avg = 0;
	float sum = 0;
	value = 0;
	max = 0;
	for (int i = 0; i < 1500; i++)
	{
		int prov = hashSearch(T, aux[i], n,0);
		if (max < prov)
			max = prov;
		nrtries++;
		sum += prov;

	} 
	value = sum / nrtries;
	//cout <<"              "<< roundd(value) << "                            " << max;
	

}
void avMaxNotFound(int T[], int n,int& max,float& value) { // this does the same as the one above but for elements we know for sure they arent there
	float nrtries = 0;
	float avg = 0;
	float sum = 0;
	 max = 0;
	 value = 0;
	for (int i = 100001; i < 101501; i++)
	{
		int prov = hashSearch(T, i, n,0);
		if (max < prov)
			max = prov;
		nrtries++;
		sum += prov;

	}
	value = sum / nrtries;
	//cout <<"                               "<< roundd(value) << "                               " << max << "          ";
	

}

void testGrade7(int T[], int fill, int n)
{

	int aux[10007];
	int aux2[10007];
	int max1;
	int max1aux = 0;
	int max2aux = 0;
	float value1;
	float value1aux=0;
	int max2;
	float value2;
	float value2aux=0;
	int fill1 = 0;
	int nrElements = 0;
	int i = 0;
	Node Nodes[10007];
	Node newNode;
	insertArray(aux, fill + 1, Nodes);
	while (nrElements != fill)
	{
		if (hashInsert(T, Nodes[i], n) != -1)
		{
			aux2[i] = Nodes[i].key;
			i++;
			nrElements++;
			fill1 = (nrElements * 100 / n);
		}
	}
	for (int j = 0; j < 5; j++)
	{
		avMaxFound(T, aux2, n, max1, value1);
		avMaxNotFound(T, n, max2, value2);
		if (max1aux < max1)
			max1aux = max1;
		if (max2aux < max2)
			max2aux = max2;
		value1aux += value1;
		value2aux += value2;
	}
	value1 = value1aux / 5;
	value2 = value2aux / 5;

	cout << "              " << roundd(value1) << "                            " << max1aux;
	cout << "                               " << roundd(value2) << "                               " << max2aux << "          ";

	//avMaxFoundUniformly(T, aux, n, fill);
	for (i = 0; i < n; i++)
		T[i] = 0;
	cout << endl;
	
}
void testGrade9(int T[], int fill, int n)
{

	int aux[10007];
	int aux2[10007];
	int max;
	float value;
	int max2;
	float value2;
	int fill1 = 0;
	int nrElements = 0;
	int i = 0;
	Node Nodes[10007];
	Node newNode;
	insertArray(aux, fill + 1, Nodes);
	while (nrElements != fill)
	{
		if (hashInsert(T, Nodes[i], n) != -1)
		{
			aux2[i] = Nodes[i].key;
			i++;
			nrElements++;
			fill1 = (nrElements * 100 / n);
		}
	}
	avMaxFoundUniformly(T, aux2, n, fill,max,value);
	cout << "              " << roundd(value) << "                            " << max;
	avMaxNotFound(T, n,max2,value2);
	cout << "                               " << roundd(value2) << "                               " << max2 << "          ";

	for (i = 0; i < n; i++)
		T[i] = 0;
	cout << endl;

}
void testGrade10(int T[], int fill, int n)
{
	int max1, max2;
	float value1, value2;
	int aux[10007];
	int fill2 = 8006;
	int aux2[10007];
	int fill1 = 0;
	int nrElements = 0;
	int i = 0;
	Node Nodes[10007];
	Node newNode;
	insertArray(aux, fill + 1, Nodes);
	while (nrElements != fill)
	{
		if (hashInsert(T, Nodes[i], n) != -1)
		{
			aux2[i] = Nodes[i].key;
			i++;
			nrElements++;
			fill1 = (nrElements * 100 / n);
		}
	}
	int pos = fill / 1901;
	for (int i = 0; i < fill; i=i+pos)
	{
		hashDelete(T, aux2[i], n);
	}
	
	avMaxFoundUniformly(T, aux2, n, fill2,max1,value1);
	cout << "              " << roundd(value1) << "                            "<< max1;
	avMaxNotFound(T, n,max2,value2);
	cout << "                               " << roundd(value2) << "                               " << max2 << "          ";
	
	for (i = 0; i < n; i++)
		T[i] = 0;
	cout << endl;

}
void func() {
	int T[10007] = { 0 };
	int n = 10007;
	int fill1 = 8006;
	int fill2 = 8506;
	int fill3 = 9007;
	int fill4 = 9507;
	int fill5 = 9907;
	cout << "-----------------------------------------------------------------Without Deletion-----------------------------------------------------------------------" << endl;
	cout << "|   Fill factor   |   Medium effort for found   |   Maximum effort for found   |   Medium effort for not found   |   Maximum effort for not found   |" << endl;
	cout << "       0.80     ";
	testGrade7(T, fill1, n);
	cout << "       0.80     ";
	testGrade9(T, fill1, n);
	cout << "       0.85     ";
	testGrade9(T, fill2, n);
	cout << "       0.90     ";
	testGrade9(T, fill3, n);
	cout << "       0.95     ";
	testGrade9(T, fill4, n);
	cout << "       0.99     ";
	testGrade9(T, fill5, n);
	cout << "-----------------------------------------------------------------With Deletion-----------------------------------------------------------------------" << endl;
	cout << "|   Fill factor   |   Medium effort for found   |   Maximum effort for found   |   Medium effort for not found   |   Maximum effort for not found   |" << endl;
	cout << "       0.99     ";
	testGrade10(T, fill5, n);
}
void demo() {
	int T[5] = { 0 };
	int aux[10007];
	int fill = 0;
	int nrElements = 0;
	int n = 10007;
	int n2 = 3;
	int fill1 = 8006;
	Node Nodes[10007];
	Node newNode;
	/*FillRandomArray(aux, fill1, 1, 20000, true, 0);
	aux[0] = 124;
	//for (int i = 0; i < fill1; i++)
		//cout << aux[i]<<" ";
	for (int i = 0; i < fill1; i++)
	{
		Nodes[i].key = aux[i];
		//cout << Nodes[i].key << " ";
		Nodes[i].c = 'c';
		hashInsert(T, Nodes[i], n);
	}
	//hashSearch(T, 10000, n);
	//for (int i = 0; i < fill1; i++)
		//cout << T[i] << " ";
	for (int i = 20000; i < 20003; i++)
		cout<<hashSearch(T, i, n);
		*/
	for (int i = 0; i < n2; i++) {
		Nodes[i].key = i;
		Nodes[i].c = 'c';
		hashInsert(T, Nodes[i], n);
	}
	for (int i = 0; i < 5; i++)
		cout << T[i] << " ";
	hashSearch(T, 1, n, 0);
	hashDelete(T, 1, n);
	for (int i = 0; i < 5; i++)
		cout << T[i] << " ";
	hashSearch(T, 1, n, 0);
	hashInsert(T, Nodes[1], n);
	for (int i = 0; i < 5; i++)
		cout << T[i] << " ";
	hashSearch(T, 1, n, 0);
	hashSearch(T, 3, n, 0);
}
int main() {
	//func();
	//testGrade7();
	demo();
}