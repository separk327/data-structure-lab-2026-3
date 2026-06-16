#include <stdio.h>

void main() {
	int i;
	char string1[20] = "Dream come true", string2[20];
	char string2[20], *ptr1;
	char* ptr2;


	ptr1 = string1;
	printf("\n string1狼 林家绰 = %u \t ptr1 = %u", string1.ptr1);
	printf("\n string1狼 林家绰 = %u", &string1[0]);

	printf("\n\n string1; %s", string1);
	printf("\n\n ptr1 %s", ptr1);
	printf("\n\n ptr1+7:%s", ptr1 + 7);
}