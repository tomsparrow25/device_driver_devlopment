#include<stdio.h>

int main()
{
	unsigned char ch;
	FILE *fp;
	fp=fopen("pointer.c", "r");
	while((ch = getc(fp))!=EOF)
	printf("%c", ch);
	fclose(fp);
return 0;
}
