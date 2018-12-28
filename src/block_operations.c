#include "../include/malloc.h"

void		block_init(t_zone *zone, t_block *ptr_block,
				size_t data_size)
{
	ptr_block->zone = zone;
	ptr_block->previous_address = NULL;
	ptr_block->next_address = NULL;
	ptr_block->is_free = TRUE;
	ptr_block->size_data = data_size;
	ptr_block->ptr_data = ptr_block + sizeof(t_block);
}

