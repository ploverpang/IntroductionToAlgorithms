/*
具有O（1）复杂度max（）操作的栈,使用数组实现
使用泛型
2014.1.20 修改于2014.1.21
*/
#include <iostream>

//#define MAX_SIZE 100;
using namespace std;

static const int MAX_SIZE = 100;

template<typename T> class Stack;
template<typename T> ostream& operator<< (ostream &os, const Stack<T> &s);

template<typename T>
class Stack
{
public:
	Stack();
	void push(const T &val);
	T& pop();
	const T& max() const;
	T& front();
	const size_t& getSize() const;
	bool isEmpty() const;
	friend std::ostream& operator<< (std::ostream &os, const Stack<T> &s);
private:
	T data[MAX_SIZE];
	size_t top;
	size_t size;
	size_t maxElemIndexArray[MAX_SIZE];
	size_t maxIndex;
};

template<typename T>
Stack<T>::Stack()
{
	top = -1;
	size = 0;
	for(size_t i = 0; i != MAX_SIZE; ++i)
	{
		maxElemIndexArray[i] = -1;
	}
	maxIndex = -1;
}

template<typename T>
void Stack<T>::push(const T &val)
{
	if(top == -1)
	{
		data[0] = val;
		top = 0;
		maxIndex = 0;
		++size;
		return;
	}
	if(size==MAX_SIZE-1)
	{
		cerr << "The stack is full" << endl;
		return;
	}
	data[++top] = val;
	++size;

	if(val > data[maxIndex])
	{
		maxElemIndexArray[top] = maxIndex; //保存之前的最大值标号
		maxIndex = top;                    //更新最大值标号
	}
}
template<typename T>
T& Stack<T>::pop() 
{
	/*
	if(size == 0)
	{
		cerr << "No element to pop" << endl;
	}
	*/
	if(top == maxIndex)
	{
		maxIndex = maxElemIndexArray[top];
	}
	--size; 
	return data[top--];
}

template<typename T>
T& Stack<T>::front()
{
	return data[top];
}

template<typename T>
const size_t& Stack<T>::getSize() const
{
	return size;
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	return (size==0 ? true : false);
}

template<typename T>
const T& Stack<T>::max() const
{
	return data[maxIndex];
}

template<typename T>
std::ostream& operator<<(std::ostream &os, const Stack<T> &s)
{
	os << "< ";
	for(size_t i = 0; i != size-1; ++i)
		os << data[i] << " , " ;
	os << "data[size-1]";
	os << " >";
	return os;
}
/*
int main()
{
	Stack<int> aStack;
	
	cout << "Is Stack empty? " << aStack.isEmpty() << endl;
	aStack.push(1);
	aStack.push(2);
	cout << "The front is " << aStack.front() << " It should be 2 " <<  endl;
	cout <<"The pop is " << aStack.pop() << " It should be 2 " << endl;
	cout << "The front is " << aStack.front() << " It should be 1 " <<  endl;
	cout << "The size now is " << aStack.getSize() << " It should be 1" << endl;

	int testArray[10] = {5,4,6,3,7,2,8,0,9,1};
	for(size_t i = 0; i != 10; ++i)
		aStack.push(testArray[i]);
	cout << "The max of TestArray is " << aStack.max() << "; It should be 9" << endl;
	aStack.pop();
	aStack.pop();
	cout << "After pop, the max of TestArray is " << aStack.max() << "; It should be 8" << endl;
//	cout << aStack << endl;
	system("PAUSE");
	return 0;
}
*/