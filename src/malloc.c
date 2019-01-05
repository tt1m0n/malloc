/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakovsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:14:21 by omakovsk          #+#    #+#             */
/*   Updated: 2019/01/05 18:14:22 by omakovsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void				*g_start_address = NULL;
pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size)
{
	t_zone	*start_zone;
	t_block	*block;

	pthread_mutex_lock(&g_mutex);
	start_zone = start_zone_init(size);
	if (!start_zone)
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	block = get_block(start_zone, size);
	if (!block)
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	set_block_to_used(block, size);
	pthread_mutex_unlock(&g_mutex);
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
