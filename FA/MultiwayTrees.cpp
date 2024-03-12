/*

This project will transform a parrent array into a multiway tree and then into a binary tree, both transformations in O(n)
Also, all 3 of them will be printed so that we can see the level for each node, resulting in the same output for all 3 forms
The first transformation function has a for 1-n and linear complexity in between so it has O(n) complexity
For the second transfomation, by applying master's theorem we have a=2 and c=0 so for sure a>b^c so the complexity is n^logb(a) whic is in the worst case is ~ n so complexity is ~O(n)
*/


#include <iostream>
using namespace std;
typedef struct Node1 {
	int value=0;
	int nrChildren=0;
	Node1* children[100]={0};
};
typedef struct Node2 {
	int value = 0;
	Node2* left=NULL;
	Node2* right=NULL;
};
void pp1(int a[], int size, int parent, int level)
{
	// cout<<repr[1]->
	for (int i = 1; i <= size; i++)
	{
		if (a[i] == parent)
		{
			for (int j = 0; j < level; j++)
				cout << ' ';
			cout<< i << endl;
			pp1(a, size, i, level + 2);
		}

	}
}
void T1(int a[],int size,Node1** root) { // this function has a for 1-n and linear complexity in between so it has O(n) complexity

	Node1* nodes=new Node1[100];
	for (int i = 1; i <= size; i++) {
		if (a[i] != -1)
		{
			(nodes+a[i])->nrChildren++;
			//cout << (nodes + a[i])->nrChildren<<" ";

			*((nodes + a[i])->children) = new Node1[100];
			(nodes + a[i])->children[(nodes + a[i])->nrChildren] = (nodes + i);
			(nodes+a[i])->children[(nodes+a[i])->nrChildren]->value = i;
			//cout << i << " ";
		}
		else
		{
			*root = (nodes + i);
			(*root)->value = i;
		}
	}

}
void pp2(Node1* root,int level) {
	if (root->nrChildren != 0)
	{
		for (int j = 0; j < level; j++)
			cout << ' ';
		cout << root->value<<endl;
		for (int i = 1; i <= root->nrChildren; i++)
			pp2(root->children[i], level + 2);
	}
	else
	{
		if (root->value)
		{
			for (int j = 0; j < level; j++)
				cout << ' ';
			cout << root->value<<endl;
		}
	}
}

Node2* T2(Node1* root, Node1* root2,int index) { // by applying master's theorem we have a=2 and c=0 so for sure a>b^c so the complexity is n^logb(a) whic is < n so complexity is <O(n)
	if (root != NULL)

	{
		Node2* rootR3 = new Node2;
		rootR3->value = root->value;

		
			//cout << "rootr3ianinte=" << rootR3->value << " ";
			
			rootR3->left = T2(root->children[1], root, 2);
			if (root2 && index <= root2->nrChildren)
			{
				//cout << "index=" << index << " ";
				//cout << "root3=" << rootR3->value << " ";
				rootR3->right = T2(root2->children[index], root2, index + 1);
			}

		
		//cout <<"rootr3final="<< rootR3->value << " ";
		return rootR3;
	}
	else
		return NULL;
}
void pp3(Node2* root, int level) {

	if (root)
	{
		for (int j = 0; j < level; j++)
			cout << ' ';
		cout << root->value << endl;
		if (root->left)
			pp3(root->left, level + 2);
		if (root->right)
			pp3(root->right, level);
	}
}
void demo() {
	int a[] = { 0,-1,1,1,1,4,5,2,2,4 };
	cout << "R1:" << endl<<endl;
	pp1(a, 10, -1, 0);
	Node1* root = new Node1;
	Node1* root2 = new Node1;
	Node2* root3 = new Node2;
	T1(a, 9, &root);
	//cout << root->value<<endl;
	cout << endl << "R2:" << endl << endl;
	pp2(root, 0);
	root3 = T2(root, root2, 0);
	//cout << root3->value;
	//cout << root3->left->right->left->value<<endl;
	cout << endl << "R3:" << endl << endl;
	pp3(root3, 0);
}
int main() {
	demo();

}