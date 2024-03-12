#include <iostream>
using namespace std;

typedef struct Node {
	int value = 0;
	Node* left = NULL;
	Node* right = NULL;
	Node* parent = NULL;
	int size = 0;
};

Node* build(Node* root, int l,int r,int a[]) {
	if (l <= r)
	{
	    int mij = (l + r) / 2;
		root->left = new Node;
		root->right = new Node;
		root->size = r - l + 1;
	    root->value = a[mij];
		if(root->left!=NULL)
		root->left->parent = root;
		if(root->right!=NULL)
		root->right->parent = root;
		root->left = build(root->left, l, mij - 1, a);
		root->right = build(root->right, mij + 1, r, a);
		return root;
	}
	return NULL;

	
}
Node* select2(Node* root,int i) {

	int rank = 0;
	if (root->left != NULL)
	{
		rank = root->left->size + 1;

	}
	else
		rank = root->size - 1;
	//cout << " node=" << root->value << " size=" << root->size << " rank=" << rank;
	if (i == rank)
		return root;
	else if (i < rank)
	{
		if (root->left != NULL)
			return select2(root->left, i);
	}
	else
	{
		if (root->right != NULL)
			return select2(root->right, i - rank);
	}
}
Node* select(Node* root, int i) {
	int rank = 0;
	if (root->left)
		rank = root->left->size + 1;
	else
		rank = 1;
	if (i == rank)
		return root;
	else if (i < rank)
		return select(root->left, i);
	else
		return select(root->right, i - rank);

}

Node* findMin(Node* root) {
	while (root->left != NULL)
	{
		root = root->left;
	}
	return root;
}
Node* succ(Node* root) {
	Node* y = new Node;
	if (root->right)
		return findMin(root->right);
	y = root->parent;
	while (root == y->right && y)
	{
		root = y;
		y = y->parent;
	}
	return y;
	    
}
int calcsize(Node* root) {
	while (root) {
		if(root->size>1)
		root->size--;
		root = root->parent;
	}
	return 0;
}
Node* dellete(Node* root,int i) {
	
	Node* toDelete = select(root, i);
	
	cout << " todelete=" << toDelete->value;
	//cout << " succ of todelete=" << succ(toDelete)->value;
	if (toDelete->left == NULL && toDelete->right == NULL)
	{
		Node* aux = toDelete->parent;
		//cout <<"toDel="<< toDelete->value;
		//cout <<"aux="<< aux->value;
		if (aux->value < toDelete->value)
		{
			aux->right->parent = NULL;
			aux->right = NULL;
		}
		else
		{
			aux->left->parent = NULL;
			aux->left = NULL;
			
				//cout <<"auxleft="<< aux->left->value;
		}
		while (aux)
		{
			aux->size--;
			aux = aux->parent;
		}
		return aux;

	}
	if (toDelete->left == NULL)
	{
		
		Node* aux = toDelete->right;
		Node* aux2 = new Node;
		if (toDelete->parent)
		{
			//cout << " toDelete= " << toDelete<<"parent="<<toDelete->parent->value;
			if (toDelete->value < toDelete->parent->value)
			{
				toDelete->parent->left = aux;
				aux->parent = toDelete->parent;
			}
			else
			{
				toDelete->parent->right = aux;
				aux->parent = toDelete->parent;
			}
		}
		else
		{
			aux2 = select(root, i + 1);
			//cout << " aux2= " << aux2->value;
			//cout << " aux2p= " << aux2->parent->value;
			if (aux2!= toDelete->right)
			{
				toDelete->value = aux2->value;
				aux2->parent->left = NULL;
			}
			else
				if (aux2->right)
				{
					toDelete->right = aux2->right;
				}

				else
					toDelete->right = NULL;
			toDelete->value = aux2->value;
		}
		if (toDelete->parent)
		{
			aux2 = toDelete->parent;
			while (aux2)
			{
				aux2->size--;
				aux2 = aux2->parent;
			}
		}
		else if (toDelete->size>1)
			toDelete->size--;

		toDelete = NULL;
		return aux;
	}
	if (toDelete->right == NULL)
	{
		Node* aux = toDelete->left;
		Node* aux2 = new Node;
		//cout << " aux= " << aux->value;
		if (toDelete->parent) {
			if (toDelete->value > toDelete->parent->value)
			{
				toDelete->parent->right = aux;
				aux->parent = toDelete->parent;
			}
			else
			{
				toDelete->parent->left = aux;
				aux->parent = toDelete->parent;
			}
		}
		else
		{
			aux2 = select(root, i - 1);
			//cout << " aux2= " << aux2->value;
			//cout << " aux2p= " << aux2->parent->value;
			if (aux2 != toDelete->left)
			{
				toDelete->value = aux2->value;
				aux->parent->size--;
				aux2->parent->right = NULL;
			}
			else
				if (aux2->left)
				{
					toDelete->left = aux2->left;
				}

				else
					toDelete->left = NULL;
			toDelete->value = aux2->value;
		}
		if (toDelete->parent)
		{
			aux2 = toDelete->parent;
			while (aux2)
			{
				aux2->size--;
				aux2 = aux2->parent;
			}
		}
		else
			toDelete->size--;
		
		toDelete = NULL;
		return aux;
	}
	Node* aux = succ(toDelete);
	//cout << " succesor of aux is= " << aux->value;
	Node* aux2 = aux;
	while (aux2->parent)
	{
		//cout << " node=" << aux2->value << " " << aux2->size;
		aux2 = aux2->parent;
		aux2->size--;
	}
	//cout << " todelete=" << toDelete->value << " aux=" << aux->value;
	if (aux != toDelete->right)
		aux->parent->left = aux->right;
	else
	{
		aux->parent->right = aux->right;
		if (aux->left == NULL && aux->right)
			aux->right->parent = aux->parent;
		\
	}
	toDelete->value = aux->value;
	
	
	free(aux);
	return toDelete;

}
Node* dellete3(Node* root, int i) {

	Node* toDelete = select(root, i);

	cout << " todelete=" << toDelete->value;
	if (toDelete->left == NULL && toDelete->right == NULL)
	{
		Node* aux = toDelete->parent;
		if (aux->value < toDelete->value)
		{
			aux->right->parent = NULL;
			aux->right = NULL;
		}
		else
		{
			aux->left->parent = NULL;
			aux->left = NULL;

		}
		calcsize(toDelete);
		return aux;

	}
	if (toDelete->left == NULL)
	{

		Node* aux = toDelete->right;
		Node* aux2 = new Node;
		if (toDelete->parent)
		{
			if (toDelete->value < toDelete->parent->value)
			{
				toDelete->parent->left = aux;
				aux->parent = toDelete->parent;
			}
			else
			{
				toDelete->parent->right = aux;
				aux->parent = toDelete->parent;
			}
		}
		else
		{
			aux2 = select2(root, i + 1);
			if (aux2 != toDelete->right)
			{
				toDelete->value = aux2->value;
				aux2->parent->left = NULL;
			}
			else
				if (aux2->right)
				{
					toDelete->right = aux2->right;
				}

				else
					toDelete->right = NULL;
			toDelete->value = aux2->value;
		}
		calcsize(toDelete);

		toDelete = NULL;
		return aux;
	}
	if (toDelete->right == NULL)
	{
		Node* aux = toDelete->left;
		Node* aux2 = new Node;
		if (toDelete->parent) {
			if (toDelete->value > toDelete->parent->value)
			{
				toDelete->parent->right = aux;
				aux->parent = toDelete->parent;
			}
			else
			{
				toDelete->parent->left = aux;
				aux->parent = toDelete->parent;
			}
			calcsize(toDelete);
		}
		else
		{
			aux2 = select2(root, i - 1);
			if (aux2 != toDelete->left)
			{
				toDelete->value = aux2->value;
				aux2->parent->right = NULL;
			}
			else
				if (aux2->left)
				{
					toDelete->left = aux2->left;
				}

				else
					toDelete->left = NULL;
			toDelete->value = aux2->value;
			calcsize(aux2->parent);
		}
		

		toDelete = NULL;
		return aux;
	}
	Node* aux = succ(toDelete);
	Node* aux2 = aux;
	calcsize(toDelete);
	if (aux != toDelete->right)
		aux->parent->left = aux->right;
	else
	{
		aux->parent->right = aux->right;
		if (aux->left == NULL && aux->right)
			aux->right->parent = aux->parent;
		\
	}
	toDelete->value = aux->value;


	free(aux);
	return toDelete;

}

void dellete2(Node* root, int i) {
	Node* toDelete = select(root, i);
	cout << endl << "toDelete=" << toDelete->value << endl;
	if (toDelete->left == NULL && toDelete->right == NULL)
	{
		Node* aux2 = toDelete->parent;
		if (toDelete->parent)
			if (toDelete->value > toDelete->parent->value)
				toDelete->parent->right = NULL;
			else
				toDelete->parent->left = NULL;
		while (aux2)
		{
			//cout << " node=" << aux2->value << " " << aux2->size;
			aux2->size--;
			aux2 = aux2->parent;
		}
	}
	else if (toDelete->left == NULL)
	{
		Node* aux2 = new Node;
			
		if (toDelete->parent)
		{
			aux2 = toDelete->parent;
			if (toDelete->value > toDelete->parent->value)
			{
				toDelete->parent->right = toDelete->right;
				toDelete->right->parent = toDelete->parent;
			}
			else
			{
				toDelete->parent->left = toDelete->right;
				toDelete->right->parent = toDelete->parent;
			}
		}
		else
		{
			aux2 = select(root, i + 1);
			
			cout << " aux2= " << aux2;
			cout << " aux2parent= " << aux2->parent->value;
			if (aux2->parent->value != toDelete->value)
				if (aux2->right)
				{
					cout << "da3caz2";
					aux2->parent->left = aux2->right;
				}
				else
				{
					cout << "da4caz2";
					aux2->parent->left = NULL;
				}
			else
				if (aux2->right)
				{
					cout << "da2caz2";
					aux2->parent->right = aux2->right;
				}
				else
				{
					cout << "dacaz2";
					aux2->parent->right = NULL;
				}
			toDelete->value = aux2->value;
		}
		
		while (aux2)
		{
			//cout << " node=" << aux2->value << " " << aux2->size;
			aux2->size--;
			aux2 = aux2->parent;
		}
	}
	else if (toDelete->right == NULL)
	{
		Node* aux2 = toDelete->parent;
		cout << " aux2= " << aux2;
		cout << " aux2parent= " << aux2->parent->value;
		if(toDelete->parent)
			if (toDelete->value > toDelete->parent->value)
			{
				toDelete->parent->right = toDelete->left;
				toDelete->left->parent = toDelete->parent;
			}
			else
			{
				toDelete->parent->left = toDelete->left;
				toDelete->left->parent = toDelete->parent;
			}
		else
		{
			aux2 = select(root, i - 1);
			if (aux2->parent->value != toDelete->value)
				aux2->parent->right = aux2->left;
			else
				if (aux2->left)
					aux2->parent->left = aux2->left;
				else
					aux2->parent->left = NULL;
			toDelete->value = aux2->value;
		}
		while (aux2)
		{
			//cout << " node=" << aux2->value << " " << aux2->size;
			aux2->size--;
			aux2 = aux2->parent;
		}

	}
	else if(toDelete->right!=NULL && toDelete->left!=NULL) {
		Node* aux = select(root,i+1);

		cout <<" succ= "<<aux->value;
	
		Node* aux2 = aux;
		cout << " aux2= " << aux2;
		cout << " aux2parent= " << aux2->parent->value;
		while (aux2->parent)
		{
			//cout << " node=" << aux2->value << " " << aux2->size;
			aux2 = aux2->parent;
			aux2->size--;
		}
		if (aux->parent->value != toDelete->value)
		{
			cout << "bol";
			aux->parent->left = aux->right;
		}
		else
			if (aux->right)
			{
				cout << "da2";
				aux->parent->right = aux->right;
			}
			else
			{
				cout << "da";
				aux->parent->right = NULL;
			}
		toDelete->value = aux2->value;
	}
}
Node* inorder(Node* root) {
	if (root == NULL)
		return NULL;
	if (root->left != NULL)
		inorder(root->left);
	cout << root->value << " " << root->size << " ";
	if (root->parent)
		cout << root->parent->value << " ";
	cout << endl;
	if (root->right != NULL)
		inorder(root->right);

}
void pp3(Node* root, int level) {

	if (root)
	{
		for (int j = 0; j < level; j++)
			cout << ' ';
		cout << root->value << endl;
		if (root->left)
			pp3(root->left, level + 2);
		if (root->right)
			pp3(root->right, level + 2);
	}
	else cout << "empty";
}
void demoS() {
	Node* root = new Node;
	int a[] = { 1,2,3,4,5,6,7 };
	int n = 7;
	int size = n;
	root->value = a[n / 2];
	build(root, 0, n - 1, a);
	inorder(root);
	for (int i = 1; i <= size; i++)
		cout <<"element nr:"<<i<<" is "<< select(root, i)->value<<endl;
	
}
void demoD() {
	Node* root = new Node;
	int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int n = 15;
	int size = n;
	root->value = a[n / 2];
	build(root, 0, n - 1, a);
	srand(time(NULL));
	pp3(root,0);
	cout << endl;
	/*for (int i = 1; i < size; i++)
	{
		int j = rand() % n + 1;
		if (j == 0)
			j = 1;
		n--;
		
		dellete(root, j);
		

		cout << endl;
		pp3(root,0);

	}*/
	cout << "element nr:" << 12 << " is " << select(root, 12)->value << endl;
	dellete(root, 12);
	cout << endl;
	pp3(root, 0);
	cout << "element nr:" << 4 << " is " << select(root, 4)->value << endl;
	dellete(root, 4);
	cout << endl;
	pp3(root, 0);
	cout << "element nr:" << 7 << " is " << select(root, 7)->value << endl;
	dellete(root, 7);
	cout << endl;
	pp3(root, 0);
}
int main() {
	demoS();
	demoD();

	
	
	

	
	


	/*for (int i = 1; i <= n; i++)
		cout << "node nr" << i << " =" << select(root, i)->value << " ";*/
	
	
}