#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Node
{
	int key;
	Node* left;
	Node* right;
	int height;
};
Node* createNode(int data)
{
	Node* newNode = new Node;
	newNode->key = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 1;
	return newNode;
}
int height(Node* root)
{
	if (root == NULL)
		return 0;
	return root->height;
}
void rotateLeft(Node*& root)
{
	Node* p = root->right;
	root->right = p->left;
	p->left = root;
	
	root->height = 1 + max(height(root->left), height(root->right));
	p->height = 1 + max(height(p->left), height(p->right));
	root = p;
}
void rotateRight(Node*& root)
{
	Node* p = root->left;
	root->left = p->right;
	p->right = root;

	root->height = 1 + max(height(root->left), height(root->right));
	p->height = 1 + max(height(p->left), height(p->right));
	root = p;
}
void Balance(Node*& root)
{
	if (root == NULL)
		return;
	int valBalance = height(root->left) - height(root->right);
	root->height = max(height(root->left), height(root->right)) + 1;
	if (valBalance > 1)
	{
		if (height(root->left->left) >= height(root->left->right))
		{
			rotateRight(root);
		}
		else
		{
			rotateLeft(root->left);
			rotateRight(root);
		}
	}
	else if (valBalance < -1)
	{
		if (height(root->right->right) >= height(root->right->left))
		{
			rotateLeft(root);
		}
		else
		{
			rotateRight(root->right);
			rotateLeft(root);
		}
	}
	else
	{
		return;
	}
}
void Insert(Node*& root, int data)
{
	if (root == NULL)
	{
		root = createNode(data);
		return;
	}
	if (data < root->key)
		Insert(root->left, data);
	else if (data > root->key)
		Insert(root->right, data);
	else
		return;
	root->height = 1 + std::max(height(root->left), height(root->right));
	Balance(root);
}
Node* findMax(Node* root)
{
	Node* curr = root;
	while (curr->right != NULL)
		curr = curr->right;
	return curr;
}
void Remove(Node*& root, int data)
{
	if (root == NULL)
		return;
	if (data < root->key)
		Remove(root->left, data);
	else if (data > root->key)
		Remove(root->right, data);
	else
	{
		if (root->left == NULL && root->right == NULL)
		{
			delete root;
			root = NULL;
			return;
		}
		else if (root->left == NULL || root->right == NULL)
		{
			if (root->left != NULL)
			{
				Node* tmp = root;
				root = root->left;
				delete tmp;
			}
			else
			{
				Node* tmp = root;
				root = root->right;
				delete tmp;
			}
		}
		else
		{
			Node* tmp = findMax(root->left);
			root->key = tmp->key;
			Remove(root->left, tmp->key);
		}
	}
	root->height = 1 + std::max(height(root->left), height(root->right));
	Balance(root);
}
void NLR(Node* root)
{
	if (root == NULL)
		return;
	cout << root->key << " ";
	NLR(root->left);
	NLR(root->right);
}
//bool isAVL(Node* root)
//{
//	if(root-)
//}
void LNR(Node* root)
{
	if (root == NULL)
		return;
	LNR(root->left);
	cout << root->key << " ";
	LNR(root->right);
}
void isBSTHelper(Node* root, vector<int>& v)
{
	if (root == NULL)
		return;
	isBSTHelper(root->left, v);
	v.push_back(root->key);
	isBSTHelper(root->right, v);
}
bool isBST(Node* root)
{
	vector<int>v;
	isBSTHelper(root, v);
	for (int i = 0; i < v.size() - 1; i++)
	{
		if (v[i + 1] < v[i])
			return false;
	}
	return true;
}
bool isAVL(Node* root)
{
	if (root == NULL)
		return true;
	bool checkLeft = isAVL(root->left);
	bool checkRight = isAVL(root->right);
	if (abs(height(root->left) - height(root->right)) <= 1 && checkLeft && checkRight)
	{ 
		return true;
	}
	else
	{
		return false;
	}
}
int main()
{
	Node* root = NULL;
	Insert(root, 2);
	Insert(root, 3);
	Insert(root, 4);
	Insert(root, 1);
	Insert(root, 10);
	Insert(root, 7);
	Insert(root, 5);
	Insert(root, 9);
  Remove(root, 1);
	NLR(root);
	cout << endl << isAVL(root);
}
