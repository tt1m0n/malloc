#include "../include/malloc.h"

t_zone	*start_zone_init(size_t data_size)
{
	t_zone	*start_zone;
	char 	block_type;

	start_zone = (t_zone*)g_start_address;
	if (!start_zone)
	{
		block_type = get_block_type(data_size);
		start_zone = get_new_zone(data_size, block_type);
		if (!start_zone)
		{
			return (NULL);
		}
		g_start_address = (void*)start_zone;
		block_init(start_zone, start_zone->start_block, data_size);
	}
	return (start_zone);
}

t_zone	*get_new_zone(size_t zone_size, char block_type)
{
	size_t	size_to_allocate;
	void	*zone_ptr;

	if (block_type == LARGE)
	{
        /*
        ** when block_size + sizeof(t_block) + sizeof(t_zone) > SIZE_T_MAX, start new cycle
        */
        if (SIZE_T_MAX - zone_size < sizeof(t_zone) + sizeof(t_block))
        {
            return (NULL);
        }
		size_to_allocate = zone_size + sizeof(t_zone) + sizeof(t_block);
	}
	else
	{
		size_to_allocate = get_size_to_allocate(zone_size);
	}
	zone_ptr = zone_allocate(size_to_allocate);
	if (zone_ptr)
	{
		zone_init(size_to_allocate, block_type, (t_zone*)zone_ptr);
	}
	return ((t_zone*)zone_ptr);
}

size_t	get_size_to_allocate(size_t block_size)
{
	size_t	page_size;
	size_t	number_of_pages;
	size_t	number_allocation;

	number_of_pages = 0;
	number_allocation = 0;
	if (!block_size)
	{
		return (0);
	}
	page_size = (size_t)getpagesize();
	while (number_allocation < MIN_ALLOCATION_PER_ZONE)
	{
		number_of_pages++;
		number_allocation = number_of_pages * page_size / block_size;
	}
	return (number_of_pages * page_size);
}

void	*zone_allocate(size_t size_to_allocate)
{
	void	*zone_ptr;

	zone_ptr = mmap(0, size_to_allocate, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);

	if (zone_ptr == MAP_FAILED)
	{
		return (NULL);
	}
	return (zone_ptr);
}

t_zone		*add_new_zone(t_zone *zone, size_t data_size)
{
	t_zone	*current_zone;
	t_zone  *new_zone;

	if (!zone)
	{
		return NULL;
	}
	current_zone = zone;
	while (current_zone->next_zone)
	{
		current_zone = current_zone->next_zone;
	}
	new_zone = get_new_zone(data_size,
			get_block_type(data_size));
	if (new_zone)
	{
	    current_zone->next_zone = new_zone;
	    new_zone->previous_zone = current_zone;
	}
	return (new_zone);
}