#include "include/malloc.h"
#include "stdio.h"
#include <string.h>
int main()
{
    int i;
    char *addr;

    i = 0;
    while (i < 10000)
    {
        addr = (char*)malloc(100);
        addr = realloc(addr, 500);
        i++;
    }
    return (0);
}