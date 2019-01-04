#include "../include/malloc.h"

t_my_bool   is_need_release_zone(t_zone *zone)
{
	if (!zone)
	{
		return (FALSE);
	}
	return (zone_is_empty(zone));
}

t_my_bool   zone_is_empty(t_zone *zone)
{
	t_block *block;

	block = zone->start_block;
	while(block)
	{
		if (block->is_free == FALSE)
		{
			return (FALSE);
		}
		block = block->next_block;
	}
	return (TRUE);
}

void    release_zone(t_zone *zone)
{
    t_zone  *previous_zone;
    t_zone  *next_zone;

    previous_zone = zone->previous_zone;
    next_zone = zone->next_zone;
    if (!previous_zone)
    {
        g_start_address = zone->next_zone;
    }
    else
    {
        ft_putstr("freenew\n");
        ft_putnbr(zone->size);
        previous_zone->next_zone = next_zone;
        if (next_zone)
        {
            next_zone->previous_zone = previous_zone;
        }
    }

	//munmap((void*)zone, zone->size);

}
