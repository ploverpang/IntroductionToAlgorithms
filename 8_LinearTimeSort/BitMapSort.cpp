#include <iostream>
//#include <bitset>
#include <fstream>
#include <string>
#include "time.h"

using namespace std;

#define MY_RAND_MAX 10000000  //随机数的范围为[0, MY_RAND_MAX)
#define NUM_MAX 1000000  //待排序的数字数量
#define BITSPERWORD 32
#define SHIFT 5  //除以32即右移5位
#define MASK 0X1F

unsigned long int next = 1;
string file_name("rand_num.txt");  //随机数文件的文件名
string sorted_file_name("sorted_num.txt");
int a[1+MY_RAND_MAX/BITSPERWORD];

void set(int *a, unsigned long i)
{
	a[i>>SHIFT]=(1<<(MASK&i));
}

bool test(int *a, unsigned long i)
{
	return a[i>>SHIFT]==(1<<(MASK&i));
}

int rand_num()
{
	next = next * 1103515245 + 12345; 
    return (unsigned int)(next) % MY_RAND_MAX; 
	//return srand((unsigned)time(NULL));
}

void generateNumber2File()
{
	ofstream outfile(file_name.c_str());
	if(!outfile)
	{
		cerr << "error: Can't open file " << file_name << endl;
	}

	for(int j = 0; j != NUM_MAX; ++j)
	{
		outfile << rand_num() << endl;
	}
	outfile.close(); 	
}

void bitMapSort()
{
	unsigned long int number;
	ifstream infile(file_name.c_str());
	//bitset<MY_RAND_MAX> b;
	while(infile>>number)
	{
		//cout << number << endl;
		set(a, number);
	}
	infile.close();
	
	ofstream outfile(sorted_file_name.c_str());
	if(!outfile)
	{
		cerr << "error: Can't open file: " << sorted_file_name << endl;
	}
	for(unsigned long int i = 0; i !=MY_RAND_MAX; ++i)
	{
		if(test(a, i))
			outfile << i << endl;
	}
	outfile.close();
}
/*
int main()
{	
	generateNumber2File();
	clock_t start, finish;
	start = clock();
	bitMapSort();
	finish = clock();
	double duration = (double)(finish-start)/CLOCKS_PER_SEC;
	cout << "The duration of sorted is " << duration << " seconds" << endl;
	system("PAUSE");
	return 1;
}
*/