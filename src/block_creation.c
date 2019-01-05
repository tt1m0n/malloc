/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakovsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 17:58:23 by omakovsk          #+#    #+#             */
/*   Updated: 2019/01/05 17:58:34 by omakovsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

t_block			*add_block_to_zone(t_zone *zone, size_t data_size)
{
	t_block *last_block;
	t_block *new_block;

	last_block = zone->start_block;
	while (last_block->next_block)
	{
		last_block = last_block->next_block;
	}
	new_block = (t_block*)((void*)last_block +
			sizeof(t_block) + last_block->data_size);
	block_init(zone, new_block, data_size);
	last_block->next_block = new_block;
	return (new_block);
}
