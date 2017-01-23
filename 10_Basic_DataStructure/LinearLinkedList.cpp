//������������ ʹ�õݹ�ʵ�ֲ��룬������� 2014-3-4�����Ĵ��󣺵ݹ�Ľڵ�ָ��һ��Ҫ�����ã������ַ�޷����ݸ�����
//             ʹ�÷ǵݹ�ʵ�ֲ��롣 2014-3-5

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
	void report() const;  //������Ԫ�طŵ�����x��ȥ
	//friend class node;
private:
	size_t n; //����Ԫ������
	node *head;
	node* rinsert(node* &p, int t);  //����ĵݹ�ʵ��
	void normalInsert(int val);      //����ķǵݹ�ʵ��
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
	node *front = head; //ָ�����val�Ľڵ����һ�ڵ㣬��������Ԫ��ʹ��
	if(val<head->val) //�����ͷ���ǰ���룬��ͷ�ڵ��Ϊ�²���Ԫ��
	{
		tmp = new node(val, tmp);
		head = tmp;
	}
	else
	{
		tmp = tmp->next;  //tmp����һ��
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