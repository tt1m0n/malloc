#include <stdio.h>
#include <stdlib.h>
#include "include/malloc.h"

int main()
{
	char *ptr1 = NULL;
	char *ptr2 = NULL;
	char *ptr3 = NULL;

	ptr1 = ft_malloc(2);
	if (ptr1 == NULL)
	{
		printf("FAKADON1");
	}
	ptr2 = ft_malloc(2000);
	if (ptr2 == NULL)
	{
		printf("FAKADON2");
	}
	ptr3 = ft_malloc(1024 * 1024);
	if (ptr3 == NULL)
	{
		printf("FAKADON3");
	}

	//free(ptr);

    return 0;
}
