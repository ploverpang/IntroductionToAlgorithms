#include <iostream>
#include <vector>
#include <set>

using namespace std;

/*
struct DataType
{
	int index;
	int satelite;
	DataType(int i, int s):index(i),satelite(s){};
};
*/

typedef int DataType;

struct Node
{
	DataType elem;
	Node *next;
	Node(DataType e, Node* p=NULL):elem(e),next(p){};
};

class List
{
public:
	List():head(0),tail(0){};
	void insert(const DataType newData);
	bool search(const DataType data) const;
	bool deleteElem(const DataType data);
private:
	Node* head;
	Node* tail;
};

class Hashing
{
public:
	Hashing(size_t ts = 701)
	{
		tableSize = ts;
		hashTable.reserve(ts);
	}
	void insertInHash(const DataType newData);
	bool searchInHash(const DataType data) const;
	bool deleteInHash(const DataType data);
private:
	int hash_method(const int index) const {return (index%701);};
	vector<List> hashTable;
	size_t tableSize;   // 哈希表的容量，即vector大小
};

void List::insert(const DataType newData)
{
	if(head == NULL)
	{
		head = new Node(newData);
		tail = head;
	}
	else
	{
		tail->next = new Node(newData);
		tail = tail->next;
	}
}

bool List::search(const DataType data) const
{
	Node *tmp = head;
	while(tmp != tail)
	{
		if(tmp->elem == data)
			return true;
		tmp = tmp->next;
	}
	return false;
}

void Hashing::insertInHash(const DataType newData)
{
	hashTable[hash_method(newData)].insert(newData);
}

bool Hashing::searchInHash(const DataType data) const
{
	return (hashTable[hash_method(data)].search(data));
}

/*
int main()
{
	Hashing hash;
	set<int> aSet;
	for(int i = 0; i != 300; ++i)
	{
		int randNum = rand()%10000;
		aSet.insert(randNum);
		hash.insertInHash(randNum);
	}

	for(int j=0; j!=10; ++j)
	{
		int randNum = rand()%10000;
		if(aSet.count(randNum) == 1)
		{
			cout << "This number " << randNum << "inserted in hash table " << endl;
			cout << "Hashing test is " << hash.searchInHash(randNum) << endl; 
		}
		else
		{
			cout << "This number " << randNum << "not in the hash table " << endl;
			cout << "Hashing test is " << hash.searchInHash(randNum) << endl; 
		}
		cout << "########################test " << j <<" over#############################" << endl;
	}
	system("PAUSE");
	return 0;
}
*/