#include<stdio.h> 
int main()
{
	float a,b;
	b=2.0e20 + 1.0;
	printf("%f\n",b);
	a = b - 2.0e20;
	printf("%f\n",a);
	return 0;
}