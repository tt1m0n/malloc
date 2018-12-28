#include "../include/malloc.h"

t_zone	*start_zone_init(size_t data_size)
{
	t_zone	*start_zone;
	char 	block_type;

	start_zone = (t_zone*)g_start_address;
	if (start_zone == NULL)
	{
		block_type = get_block_type(data_size);
		start_zone = get_new_zone(data_size, block_type);
		if (start_zone == NULL)
			return NULL;
		g_start_address = start_zone;
		block_init(start_zone, (t_block*)start_zone->start_block, data_size);
	}
	return (start_zone);
}

t_zone	*get_new_zone(size_t block_size, char block_type)
{
	size_t	size_to_allocate;
	void	*zone_ptr;

	if (block_type == LARGE)
	{
		size_to_allocate = block_size + sizeof(t_block);
	}
	else
	{
		size_to_allocate = get_size_to_allocate(block_size);
	}
	zone_ptr = zone_allocate(size_to_allocate);
	if (zone_ptr != NULL)
	{
		zone_init(size_to_allocate, block_type, (t_zone*)zone_ptr);
	}
	return (zone_ptr);
}

size_t	get_size_to_allocate(size_t block_size)
{
	size_t	page_size;
	size_t	number_of_pages;
	size_t	number_allocation;

	number_of_pages = 0;
	number_allocation = 0;
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
	t_zone	*next_zone;

	if (!zone)
	{
		return NULL;
	}
	current_zone = zone;
	while (current_zone->next_zone)
	{
		current_zone = current_zone->next_zone;
	}
	current_zone->next_zone = get_new_zone(data_size,
			get_block_type(data_size));
	if (current_zone->next_zone)
	{
		next_zone = current_zone->next_zone;
		next_zone->previous_zone = current_zone;
		block_init(current_zone->next_zone,
				current_zone->next_zone->start_block, data_size);
	}
	return (current_zone->next_zone);
}