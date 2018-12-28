#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *ptr = NULL;
	//printf("%d\n", getrlimit())
	ptr = malloc(1024);
	if (ptr == NULL)
	{
		printf("FAKADON");
    }

	free(ptr);

    return 0;
}
