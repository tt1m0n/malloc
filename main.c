#include <stdio.h>
#include <stdlib.h>
#include "include/malloc.h"
#include <memory.h>

t_zone  *g_start_zone;

int main()
{
    int i;
    char *addr;
    char *addr1;
    char *addr2;

    i = 0;
    while (i < 1024)
    {
        addr = (char*)malloc(1024);

        addr[0] = 42;
        free(addr);
        i++;
    }
    g_start_zone = g_start_address;
    t_zone  *next = (t_zone*)g_start_zone->next_zone;
    //t_zone  *next1 = ((t_zone*)g_start_zone->next_zone)->next_zone;
    //show_alloc_mem();

    return (0);
}