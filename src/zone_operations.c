#include "../include/malloc.h"

void	zone_init(size_t size_of_allocation,
			char block_type, t_zone *ptr_zone)
{
	ptr_zone->start_block = (t_block*)((void*)ptr_zone + sizeof(t_zone));
	ptr_zone->next_zone = NULL;
	ptr_zone->previous_zone = NULL;
	ptr_zone->size = size_of_allocation;
	ptr_zone->type = block_type;
}

t_zone		*get_correct_type_zone(t_zone *start_zone,
									 size_t data_size)
{
	t_zone	*current_zone;

	current_zone = start_zone;
	while (current_zone)
	{
		if (is_correct_type_zone(current_zone, data_size))
		{
			return (current_zone);
		}
		current_zone = current_zone->next_zone;
	}
	return (current_zone);
}

t_my_bool 	is_correct_type_zone(t_zone* zone, size_t data_size)
{
	if (zone && zone->type)
	{
		if (zone->type == TINY && data_size <= TINY_BLOCK)
		{
			return (TRUE);
		}
		else if (zone->type == SMALL &&
				data_size > TINY_BLOCK &&
				data_size <= SMALL_BLOCK)
		{
			return (TRUE);
		}
		else if (zone->type == LARGE && data_size > SMALL_BLOCK)
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

t_my_bool	is_available_space_zone(t_zone *zone, size_t data_size)
{
	void	*last_address;
	void	*possible_address;
	t_block	*last_block;

	last_address = (void*)zone + zone->size;
	last_block = zone->start_block;
	while (last_block->next_block)
	{
		last_block = last_block->next_block;
	}
	possible_address = (void*)last_block + sizeof(t_block) +
						last_block->data_size + sizeof(t_block) +
						data_size;
	if (possible_address > last_address)
	{
		return (FALSE);
	}
	return (TRUE);
}