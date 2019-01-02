#include "../include/malloc.h"

t_block			*add_block_to_zone(t_zone *zone, size_t data_size)
{
	t_block *last_block;
	t_block *new_block;

	last_block = zone->start_block;
	while (last_block->next_address)
	{
		last_block = (t_block*)last_block->next_address;
	}
	new_block = (t_block*)((void*)last_block +
			sizeof(t_block) + last_block->data_size);
	block_init(zone, new_block, data_size);

	last_block->next_address = (void*)new_block;
	return new_block;
}

