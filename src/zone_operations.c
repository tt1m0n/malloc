#include "../include/malloc.h"

void	zone_init(size_t size_of_allocation,
			char block_type, t_zone *ptr_zone)
{
	ptr_zone->start_block = (void*)ptr_zone + sizeof(t_zone);
	ptr_zone->current_zone = (void*)ptr_zone;
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
	while (current_zone != NULL)
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
		else if (zone->type == LARGE &&
				data_size > SMALL_BLOCK)
		{
			return (TRUE);
		}
	}
	return (FALSE);
}