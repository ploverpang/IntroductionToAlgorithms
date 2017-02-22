#include<iostream>

using namespace::std;

struct Node
{
	int data;
	Node *lchild;
	Node *rchild;
	Node *p;
	Node(int val):data(val),lchild(0),rchild(0), p(NULL) {};
};

class BST
{
public:
	BST();
	BST(const int *newData, const size_t dataNum);
	void insertElem(const int newData);
	void insertElem1(const int newData);
	Node* search(const int val) const;
	size_t getSize() const;
	void midOrderPrint() const;
	Node* successor(Node *x);
	Node* predecessor(Node *x);
	void deleteNode(Node *x);

private:
	Node *m_root;
	size_t m_size;
	void printNode(const Node *node) const;
	void midOrderWithNode(const Node *node) const;
	Node* searchWithNode(Node *node, const int val) const;
    Node* minimum(Node *x);
	Node* maximum(Node *x);
	void insertElemReserve(const int newData, Node *x, Node *y);
	void replace(Node *u, Node *v);
};

BST::BST()
{
	m_root = NULL;
	m_size = 0;
}

Node* BST::minimum(Node *x)
{
    Node *node = x;
    while(node->lchild != NULL)
        node = node->lchild;
    return node;
}

Node* BST::maximum(Node *x)
{
    Node *node = x;
    while(node->rchild != NULL)
        node = node->rchild;
    return node;
}

BST::BST(const int *newData, const size_t dataNum)
{
	m_root = NULL;
	m_size = 0;

	for(size_t i = 0; i < dataNum; ++i)
	{
		insertElem(newData[i]);
	}
}

size_t BST::getSize() const
{
	return m_size;
}

void BST::insertElem1(const int newData)
{
	// iterative
	Node *x = m_root;
	Node *y = NULL; // x's parent

	while(x != NULL)
	{
		y = x;
		if(newData < x->data)
			x = x->lchild;
		else
			x = x->rchild;
	}

	x = new Node(newData);
	if(y == NULL)
		m_root = x;
	else if(newData < y->data)
		y->lchild = x;
	else
		y->rchild = x;
	x->p = y;
	m_size++;
}

void BST::insertElem(const int newData)
{
	// reserve
	insertElemReserve(newData, m_root, NULL);
}

void BST::insertElemReserve(const int newData, Node *x, Node *y)
{
	if(x == NULL)
	{
		x = new Node(newData);
		if(y == NULL)
			m_root = x;
		else if(newData < y->data)
			y->lchild = x;
		else
			y->rchild = x;
		x->p = y;
	}
	else if(newData < x->data)
		insertElemReserve(newData, x->lchild, x);
	else
		insertElemReserve(newData, x->rchild, x);
	m_size++;
}

void BST::printNode(const Node *node) const
{
	cout << node->data << endl;
}

void BST::midOrderWithNode(const Node *node) const
{
	if(node == NULL) return;
	midOrderWithNode(node->lchild);
	printNode(node);
	midOrderWithNode(node->rchild);
}

void BST::midOrderPrint() const
{
	midOrderWithNode(m_root);
}

Node* BST::searchWithNode(Node *node, const int val) const
{
	if(node == NULL)
	{
		cout << "Can't find Value of " << val << endl;
		return NULL;
	}
	if(node->data == val)
	{
		return node;
	}
	if(val<node->data)
		return searchWithNode(node->lchild, val);
	else
		return searchWithNode(node->rchild, val);
}

Node* BST::search(const int val) const
{
	return searchWithNode(m_root, val);
}

Node* BST::successor(Node *x)
{
	if(x->rchild != NULL)
		return minimum(x->rchild);
	while(x->p != NULL && x == x->p->rchild)
		x = x->p;
	return x->p;
}

Node* BST::predecessor(Node *x)
{
	if(x->lchild != NULL)
		return maximum(x->lchild);
	while(x->p != NULL && x == x->p->lchild)
		x = x->p;
	return x->p;
}

//replace Node u by Node v
void BST::replace(Node *u, Node *v)
{
	if(u == m_root)
		m_root = v;
	else if(u->p->lchild == u)
		u->p->lchild = v;
	else
		u->p->rchild = v;
	v->p = u->p;
}

void BST::deleteNode(Node *x)
{
	if(x->lchild == NULL && x->rchild == NULL)
	{
		if(x == x->p->lchild) x->p->lchild = NULL;
		else x->p->rchild = NULL;
		delete x;
	}
	else if(x->lchild == NULL)
	{
		replace(x, x->rchild);
	}
	else if(x->rchild == NULL)
	{
		replace(x, x->lchild);
	}
	else
	{
		Node *y = successor(x);
		if(y != x->rchild)
		{
			replace(y, y->rchild);
			Node *r = x->rchild;
			y->rchild = r;
			y->rchild->p = y;
		}
		replace(x, y);
		y->lchild = x->lchild;
		x->lchild->p = y;
	}
}

int main()
{
	int testArray[10] = {5,4,6,3,7,2,8,1,9,0};
	BST aBST(testArray, 10);
	aBST.midOrderPrint();

	int Val = 3;
	Node *pSearched = aBST.search(Val);
	Node *pSuccessed = aBST.successor(pSearched);
	Node *pPredecessor = aBST.predecessor(pSearched);
	aBST.deleteNode(pSearched);

	aBST.midOrderPrint();

	cout << pPredecessor->data << endl;
	return 0;
}
