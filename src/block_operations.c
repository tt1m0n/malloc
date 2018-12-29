#include "../include/malloc.h"

void		block_init(t_zone *zone, t_block *ptr_block,
				size_t data_size)
{
	ptr_block->zone = zone;
	ptr_block->next_address = NULL;
	ptr_block->is_free = TRUE;
	ptr_block->data_size = data_size;
	ptr_block->ptr_data = (void*)ptr_block + sizeof(t_block);
}

t_block		*get_available_block(t_block *block, size_t data_size)
{
	t_block	*current_block;

	current_block = get_free_block(block);
	while (current_block && current_block->data_size < data_size)
	{
		current_block = get_free_block(current_block->next_address);
	}
	return (current_block);
}

t_block		*get_free_block(t_block *block)
{
	t_block	*current_block;

	current_block = block;
	while (current_block && !current_block->is_free)
	{
		current_block = current_block->next_address;
	}
	return current_block;
}

void 		set_block_to_used(t_block *block, size_t data_size)
{
	block->data_size = data_size;
	block->is_free = FALSE;
}

t_my_bool   is_block_exist(t_block *check_block)
{
    t_block *current_block;
    t_zone  *current_zone;

    current_zone = (t_zone*)g_start_address;
    while (current_zone)
    {
        current_block = current_zone->start_block;
        while(current_block)
        {
            if (current_block == check_block)
            {
                return (TRUE);
            }
            current_block = (t_block*)current_block->next_address;
        }
        current_zone = (t_zone*)current_zone->next_zone;
    }

    return (FALSE);
}
