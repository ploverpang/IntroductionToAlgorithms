#include<iostream>

using namespace::std;

struct Node 
{
	int data;
	Node *lchild;
	Node *rchild;
	Node(int val):data(val),lchild(0),rchild(0){};
};

class BST
{
public:
	BST();
	BST(const int *newData, const size_t dataNum);
	Node* insertElem(Node* node, const int newData);
	bool search(const int val) const;
	size_t getSize() const;
	void midOrderPrint() const;
private:
	Node *root;
	size_t size;
	void printNode(const Node *node) const;
	void midOrderWithNode(const Node *node) const;
	bool searchWithNode(const Node *node, const int val) const;
};

BST::BST()
{
	root = NULL;
	size = 0;
}

BST::BST(const int *newData, const size_t dataNum)
{
	
	//root = new Node();    //早些的版本在构造函数中。预先定义了一个节点，然后在插入操作时，判断是否size为0
	//root->lchild = NULL;  //这个操作完全可以把root设为NULL，在insert中统一操作
	//root->rchild = NULL;

	root = NULL;
	size = 0;

	for(size_t i = 1; i != dataNum; ++i)
	{
		insertElem(root, newData[i]);
	}
}

size_t BST::getSize() const
{
	return size;
}

Node* BST::insertElem(Node* node, const int newData)
{
	/*
	if(size == 0)
	{
		node->data = newData;
		++size;
		return;
	}
	*/
	if(node == NULL)
	{
		node = new Node(newData);
		++size;
	}
	else if(newData < node->data)	
	{
		 node = insertElem(node->lchild, newData);
	}
	else
	{	
		node = insertElem(node->rchild, newData);
	}
	return node;
	/*
	if(size == 0)
	{	
		tmp_root->data = newData;
		++size;
		return;
	}
	
	if((tmp_root->lchild == NULL) && (tmp_root->rchild == NULL)) //if BST is no element
	{
		tmp_root->data = newData;
		return;
	}
	
	Node *tmp_root = root;
	while(tmp_root != NULL)
	{
		if(newData < tmp_root->data)	
			tmp_root = tmp_root->lchild;
		else
			tmp_root = tmp_root->rchild;
	}
	tmp_root = new Node();
	tmp_root->lchild = NULL;
	tmp_root->rchild = NULL;
	tmp_root->data = newData;
	*/
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
/*
	if(node->lchild != NULL)
	{
		midOrderWithNode(node->lchild);
	}
	printNode(node);
	if(node->rchild != NULL)
	{
		midOrderWithNode(node->rchild);
	}
*/
}

void BST::midOrderPrint() const
{
	if(size == 0)
	{
		cerr << "ERROR! No element in the BST " << endl;
		return;
	}
	midOrderWithNode(root);
}

bool BST::searchWithNode(const Node *node, const int val) const
{
	if(node == NULL)
	{	
		cout << "Can't find Value of " << val << endl;
		return false;
	}
	if(node->data == val)
	{
		return true;
	}
	if(val<node->data)
		 return searchWithNode(node->lchild, val);
	else
		return searchWithNode(node->rchild, val);
}

bool BST::search(const int val) const
{
	return searchWithNode(root, val);
}

/*
int main()
{
	int testArray[10] = {5,4,6,3,7,2,8,1,9,0};
	BST aBST(testArray, 10);
	aBST.midOrderPrint();
	int Val = 10;
	cout << "Can we find Value of " << Val <<
		"in the BST  " << aBST.search(Val) << endl;
	system("PAUSE");
	return 0;
}
*/