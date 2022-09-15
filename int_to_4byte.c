#include <stdio.h>

int main()
{
	int a = 6768;
	for(int i = 0; i < sizeof(a); i++)
	{
		printf("%d", ((int)*(((unsigned char*)(&a)) + i)));
	}
	
}
