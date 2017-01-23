#include <stdio.h>
void main_abc() {
	float average(int array[5]);
//	extern abc;
//	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int a[10];
	int pv , *p1;
	int* p = a;
	printf("Please input 10 number \n");
	for (int i=0; i<10; i++)
	{
		scanf("%d",p++);
	}
	scanf("%d", &pv);
	p1 = &pv;
	printf("The average of 10 number is %f\n", average(a));
	printf("The all range avaiable is %d\n", *p1);
}

float average(int array[5]) {
	int sum = 0;
	static int abc = 10;
	for(int i = 0; i<10; i++) {
		sum = sum + array[i];
	}
	return sum/10;
}