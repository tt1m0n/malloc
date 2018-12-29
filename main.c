#include <stdio.h>
#include <stdlib.h>
#include "include/malloc.h"
#include <memory.h>

#define M (1024 * 1024)

void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	ft_malloc(20000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	ft_malloc(21000);
	show_alloc_mem();
}