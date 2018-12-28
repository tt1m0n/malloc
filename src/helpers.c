#include "../include/malloc.h"

char 	get_block_type(size_t data_size)
{
	if (data_size <= TINY_BLOCK)
		return (TINY);
	else if (data_size <= SMALL_BLOCK)
		return (SMALL);
	else
		return LARGE;
}
