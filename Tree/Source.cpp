#include<iostream>
#include<queue>
using namespace std;

struct Node
{
	int data;
	Node* left;
	Node* right;
};
Node* createNode(int data)
{
	Node* newNode = new Node;
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}
void Insert(Node*& root, int data)
{
	if (root == NULL)
	{
		Node* newNode = createNode(data);
		root = newNode;
		return;
	}
	if (data <= root->data)
	{
		Insert(root->left, data);
	}
	else if (data > root->data)
	{
		Insert(root->right, data);
	}
}

void LNR(Node* root)
{
	if (root == NULL)
		return;
	LNR(root->left);
	cout << root->data << " ";
	LNR(root->right);
}
void LRN(Node* root)
{
	if (root == NULL)
		return;
	LRN(root->left);
	LRN(root->right);
	cout << root->data;
}
void NLR(Node* root)
{
	if (root == NULL)
		return;
	cout << root->data << " ";
	NLR(root->left);
	NLR(root->right);
}

void LevelOrder(Node* root)
{
	if (root == NULL)
		return;
	queue<Node*>q;
	q.push(root);
	while (!q.empty())
	{
		Node* pCurr = q.front();
		q.pop();
		cout << pCurr->data << " ";
		if (pCurr->left != NULL)
		{
			q.push(pCurr->left);
		}
		if (pCurr->right != NULL)
		{
			q.push(pCurr->right);
		}
	}
}
int Height(Node* root)
{
	if (root == NULL)
	{
		return 0;
	}
	int left = Height(root->left);
	int right = Height(root->right);
	return max(left, right) + 1;
}
int countNode(Node* root)
{
	if (root == NULL)
		return 0;
	int left = countNode(root->left);
	int right = countNode(root->right);
	return left + right + 1;
}
int sumNode(Node* root)
{
	if (root == NULL)
		return 0;
	int left = sumNode(root->left);
	int right = sumNode(root->right);
	return left + right + root->data;
}
Node* Search(Node* root, int x)
{
	if (root == NULL)
		return NULL;
	if (x > root->data)
	{
		return Search(root->right, x);
	}
	else if (x < root->data)
		return Search(root->left, x);
	else if (x == root->data)
		return root;
}
Node* FindMax(Node* root)
{
	while (root->right != NULL)
	{
		root = root->right;
	}
	return root;
}
void Remove(Node*& root, int x)
{
	if (root == NULL)
		return;
	if (x < root->data)
		Remove(root->left, x);
	else if (x > root->data)
		Remove(root->right, x);
	else
	{
		if (root->left == NULL)
		{
			Node* tmp = root->right;
			delete root;
			root = tmp;
		}
		else if (root->right == NULL)
		{
			Node* tmp = root->left;
			delete root;
			root = tmp;
		}
		else
		{
			Node* tmp = FindMax(root->left);
			root->data = tmp->data;
			Remove(root->left, tmp->data);
		}
	}
}
Node* createTree(int a[], int n)
{
	Node* root = NULL;
	for (int i = 0; i < n; i++)
	{
		Insert(root, a[i]);
	}
	return root;
}
void removeTree(Node*& root)
{
	if (root == NULL)
		return;
	removeTree(root->left);
	removeTree(root->right);
	delete root;
	root = NULL;
}
int heightNode(Node* root, int value)
{
	Node* valueNode = Search(root, value);
	return Height(valueNode);
}
int Level(Node* root, Node* p, int num = 1)
{
	if (root == NULL || p == NULL)
		return 0;
	if (root == p)
		return num;
	if (p->data < root->data)
		return Level(root->left, p, num + 1);
	else if (p->data > root->data)
		return Level(root->right, p, num + 1);
}
int countLeaf(Node* root)
{
	if (root == NULL)
		return 0;
	int left = countLeaf(root->left);
	int right = countLeaf(root->right);
	if (root->left == NULL && root->right == NULL)
	{
		return left + right + 1;
	}
	else
	{
		return left + right;
	}
}
int countLess(Node* root, int x)
{
	if (root == NULL)
		return 0;
	int left = countLess(root->left, x);
	int right = countLess(root->right, x);
	if (x > root->data)
		return 1 + left + right;
	else
		return left + right;
}
int countGreater(Node* root, int x)
{
	if (root == NULL)
		return 0;
	int left = countGreater(root->left, x);
	int right = countGreater(root->right, x);
	if (x < root->data)
		return 1 + left + right;
	else
		return left + right;
}
void rotateLeft(Node*& root)
{
	Node* p = root->right;
	root->right = p->left;
	p->left = root;
	root = p;
}

void rotateRight(Node*& root)
{
	Node* p = root->left;
	root->left = p->right;
	p->right = root;
	root = p;
}

int height(Node* root)
{
	if (root == NULL)
		return 0;
	return max(height(root->left) + 1, height(root->right) + 1);
}
void Balance(Node*& root) {
	// Check balance
	int balance = height(root->left) - height(root->right);
	if (balance >= 2) // Mat can bang trai
	{
		if (height(root->left->left) >= height(root->left->right)) // Mat can bang trai trai (left - left)
		{
			rotateRight(root);
		}
		else // Mat can bang trai phai (left - right)
		{
			rotateLeft(root->left);
			rotateRight(root);
		}
	}
	else if (balance <= -2) // Mat can bang phai
	{
		if (height(root->right->right) >= height(root->right->left)) // Mat can bang phai phai (right - right)
		{
			rotateLeft(root);
		}
		else // Mat can bang phai trai (right - left)
		{
			rotateRight(root->right);
			rotateLeft(root);
		}
	}
}
void insertNode(Node*& root, int data)
{
	// Insert node
	if (root == NULL)
	{
		root = createNode(data);
	}
	if (root->data > data)
		insertNode(root->left, data);
	else if (root->data < data)
		insertNode(root->right, data);
	Balance(root);

}
void removeNode(Node*& root, int data) {
	if (root == NULL) return;
	else if (data < root->data) removeNode(root->left, data);
	else if (data > root->data) removeNode(root->right, data);
	if (root->data == data) {
		if (root->left == NULL && root->right == NULL) { //no child 
			delete root;
			root = NULL;
			return;
		}
		else if (root->left == NULL || root->right == NULL) { //1 child
			if (root->left != NULL) {
				Node* temp = root;
				root = root->left;
				delete temp;
			}
			else if (root->right != NULL) {
				Node* temp = root;
				root = root->right;
				delete temp;
			}
		}
		else { //2 children
			Node* succ = root->right;
			while (succ->left != NULL) {
				succ = succ->left;
			}
			root->data = succ->data;
			removeNode(root->right, succ->data);
		}
	}
	if (root != NULL) Balance(root); //make tree balance
}
void printTree(Node* root, int h)
{
	if (root == NULL)
	{
		for (int i = 0; i < h; ++i) cout << "   ";
		cout << "* " << endl;
		return;
	}
	printTree(root->right, h + 1);
	for (int i = 0; i < h; ++i) cout << "   ";
	cout << root->data << endl;
	printTree(root->left, h + 1);
}
void helper(Node* pRoot, vector <int>& a)
{
	if (!pRoot) return;

	helper(pRoot->left, a);
	a.push_back(pRoot->data);
	helper(pRoot->right, a);
}

bool isBST(Node* pRoot)
{
	vector <int> a;
	helper(pRoot, a);
	for (int i = 1; i < a.size(); ++i)
	{
		if (a[i] < a[i - 1])
			return false;
	}
	return true;
}
void FullHelper(Node* root, bool& check)
{
	if (root == NULL)
		return;
	FullHelper(root->left, check);
	FullHelper(root->right, check);
	if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL))
		check = false;
}
bool isFull(Node* root)
{
	bool check = true;
	FullHelper(root, check);
	return check;
}
bool isFullBST(Node* root)
{
	if (isFull(root) && isBST(root))
		return true;
	return false;
}
bool isBalance(Node* root)
{
	if (root == NULL)
	{
		return 1;
	}
	int leftHeight = height(root->left);
	int rightHeight = height(root->right);
	if (abs(leftHeight - rightHeight) <= 1 && isBalance(root->left) && isBalance(root->right))
	{
		return 1;
	}
	return 0;
}
bool isAVL(Node* root)
{
	return isBST(root) && isBalance(root);
}
int main()
{
	//15, 5, 12, 8, 23, 1, 17, 21
	Node* root = NULL;
	Insert(root, 15);
	Insert(root, 5);
	Insert(root, 12);
	Insert(root, 8);
	Insert(root, 23);
	Insert(root, 1);
	Insert(root, 17);
	Insert(root, 21);
	removeNode(root, 1);
	cout << isFullBST(root);
}
