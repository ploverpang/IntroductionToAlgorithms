//线性有序链表 使用递归实现插入，简介明了 2014-3-4，犯的错误：递归的节点指针一定要是引用，否则地址无法传递给参数
//             使用非递归实现插入。 2014-3-5

#include <iostream>
#include <Ctime>
#include <Algorithm>

using namespace std;

static const int max_val = 65535;
class node
{
public:
	int val;
	node *next;
	node(int v, node *p) {val=v; next=p;}
};

class LLinkedList
{
public:
	LLinkedList();
	size_t size() const {return n;}
	void insert(int val);
	void report() const;  //将链表元素放到向量x中去
	//friend class node;
private:
	size_t n; //链表元素数量
	node *head;
	node* rinsert(node* &p, int t);  //插入的递归实现
	void normalInsert(int val);      //插入的非递归实现
};

LLinkedList::LLinkedList()
{
	head = new node(max_val, NULL);
	n = 0;
}

node* LLinkedList::rinsert(node* &p, int t)
{
	if(t > p->val)
	{
		p->next = rinsert(p->next, t);
	}
	else
	{
		p = new node(t, p);
		++n;
	}
	return p;
}

void LLinkedList::normalInsert(int val)
{
	node *tmp = head;
	node *front = head; //指向大于val的节点的上一节点，用来插入元素使用
	if(val<head->val) //如果在头结点前插入，则头节点变为新插入元素
	{
		tmp = new node(val, tmp);
		head = tmp;
	}
	else
	{
		tmp = tmp->next;  //tmp先走一步
		while(val>tmp->val)
		{
			tmp = tmp->next;
			front = front->next;
		}
		tmp = new node(val, tmp);
		front->next = tmp;
	}
	++n;
}

void LLinkedList::insert(int val)
{
	//normalInsert(val);
	rinsert(head, val);
}

void LLinkedList::report() const
{
	node* tmp = head;
	for(int i=0; i<n; ++i)
	{
		cout << tmp->val << " , " ;
		tmp = tmp->next;
	}
	cout << endl;
}
/*
int main()
{
	int testArray[10] = {5,6,4,3,7,2,8,1,9,0};
	sort(testArray, testArray+10);
	
	
	int* testArray = new int[20000];
	for(int ii=0; ii != 20000; ++ii)
	{
		testArray[ii] = ii;
	}
	LLinkedList lllist;
	clock_t start, finish;
	start = clock();
	int i =0;
	for(; i != 8616; ++i)	
	{
		lllist.insert(testArray[i]);
	}
	for(;i != 20000; ++i)	
	{
		lllist.insert(testArray[i]);
	}
	finish = clock();
	double duration = static_cast<double>((finish-start));  ///CLOCKS_PER_SEC
	cout << "Insert operation spends " << duration << endl;
	cout << "The size of LinkedList is " << lllist.size() << endl;
	cout << "Now report the LinkedList" << endl;
	//lllist.report();
	
	system("PAUSE");
	return 0;
}
*/