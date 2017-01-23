/*****************************
单链表建立，打印
头指针内没有内容，只是指向第一个节点
******************************/

#include "stdio.h"
#include "stdlib.h"
#include <math.h>
#include <iostream>

typedef struct student
{
	int num;
	struct student *next;
}node;

node* create()
{
	node* head;  //头指针
	node* p;     //游标指针
	int tmp_num;

	head = (node*)malloc(sizeof(node*));
	p = head;
	node* s;    //新创建的节点
	while (1)
	{
		scanf("%d", &tmp_num);
		if (tmp_num != 0)
		{
			s = (node*)malloc(sizeof(node*));
			s->num = tmp_num;
			p->next = s;
			p = s; //游标向后移
		}
		else break;
	}
	p->next = NULL;
	return head;
}

void print(node* head)
{
	node *s = head->next;
	while (s->next != NULL)
	{
		printf("%d\n", s->num);
		s = s->next;
	}
	printf("%d\n", s->num);
}


/**********************
string类型的数转为long int
**********************/
long int string2num(char a[])
{
	int length = strlen(a);
	long int tmp = 0;
	for (int i = 0; i<length ; i++)
	{
		tmp += int(a[i]-'0') * pow(10, i);
	}
	return tmp;
}

/********************************
循环右移char*，比如“abcdefghi”右移2为“hiabcdefg”
*********************************/
void LoopMove(char* pStr, int steps)
{
	int length = strlen(pStr);
	char tmp[10];
	char *abc = tmp;
	memcpy(tmp, pStr+(length-steps), steps+1); //末尾的steps个元素
	memcpy(pStr, tmp, steps+1);
	memcpy(pStr+steps, pStr, (length-steps));

}
// void main()
// {
// // 	node *head = create();
// // 	printf("Now we will print the element of list\n");
// // 	print(head);
// 	//printf("Size of node xing is %d", (int)sizeof(node*));
// 	//printf("Size of node  is %d", (int)sizeof(node));
// 	char *string = "12345";
// //	printf("The number covert from string is %ld\n", string2num(string));
// 	LoopMove(string, 2);
// 	printf("Output of LoopMove is %s\n", string);
// }