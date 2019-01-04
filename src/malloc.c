#include "../include/malloc.h"

void	*g_start_address = NULL;

void	*malloc(size_t size)
{
	t_zone	*start_zone;
	t_block	*block;

	ft_putstr("malloc\n");
	block = NULL;
	start_zone = start_zone_init(size);
	if (!start_zone)
		return (NULL);
	block = get_block(start_zone, size);
	if (!block)
		return (NULL);
	set_block_to_used(block, size);
	return (block->ptr_data);
}

t_block	*get_block(t_zone *start_zone, size_t size)
{
	t_zone	*current_zone;
	t_block *block;

	current_zone = start_zone;
	block = NULL;
	while (!block)
	{
		current_zone = get_correct_type_zone(current_zone, size);
		if (!current_zone)
		{
			current_zone = add_new_zone(start_zone, size);
			if (!current_zone)
				return (NULL);
			block_init(current_zone, current_zone->start_block, size);
		}
		block = get_available_block(current_zone->start_block, size);
		if (!block)
		{
			if (is_available_space_zone(current_zone, size) == TRUE)
				block = add_block_to_zone(current_zone, size);
			else
				current_zone = current_zone->next_zone;
		}
	}

	return (block);
}
