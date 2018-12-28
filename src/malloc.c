#include "../include/malloc.h"

void	*g_start_address = NULL;

void	*ft_malloc(size_t size)
{
	t_zone	*start_zone;
	t_block	*block;

	block = NULL;
	start_zone = start_zone_init(size);
	if (start_zone == NULL)
		return (NULL);
	block = get_block(start_zone, size);
	if (block == NULL)
		return (NULL);
	set_block_to_used(block, size);
	return (block->ptr_data);
}

t_block	*get_block(t_zone *start_zone, size_t size)
{
	t_zone	*current_zone;
	t_block *block;

	block = NULL;
	while (block == NULL)
	{
		current_zone = get_correct_type_zone(start_zone, size);
		if (current_zone == NULL)
		{
			current_zone = add_new_zone(start_zone, size);
			if (current_zone == NULL)
				return (NULL);
			block_init(current_zone, current_zone->start_block, size);
		}
		block = get_reusable_block(current_zone->first_block, size);
		if (block == NULL)
		{
			if (is_space_available_zone(current_zone, size) == TRUE)
				block = add_block_to_zone(current_zone, size);
			else
				current_zone = current_zone->next_zone;
		}
	}
	return (block);
}
