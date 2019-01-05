/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem_bonuses.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakovsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 20:37:15 by omakovsk          #+#    #+#             */
/*   Updated: 2019/01/05 20:40:20 by omakovsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void	show_alloc_tiny_zones(void)
{
	t_zone	*current_zone;

	pthread_mutex_lock(&g_mutex);
	current_zone = (t_zone*)g_start_address;
	while (current_zone)
	{
		if (current_zone->type != TINY)
		{
			current_zone = current_zone->next_zone;
			continue ;
		}
		ft_putstr("TINY : ");
		ft_puthex((unsigned int)((void*)current_zone));
		ft_putstr("\n");
		show_block_memory(current_zone->start_block);
		current_zone = current_zone->next_zone;
		ft_putchar('\n');
	}
	pthread_mutex_unlock(&g_mutex);
}

void	show_alloc_small_zones(void)
{
	t_zone	*current_zone;

	pthread_mutex_lock(&g_mutex);
	current_zone = (t_zone*)g_start_address;
	while (current_zone)
	{
		if (current_zone->type != SMALL)
		{
			current_zone = current_zone->next_zone;
			continue ;
		}
		ft_putstr("SMALL : ");
		ft_puthex((unsigned int)((void*)current_zone));
		ft_putstr("\n");
		show_block_memory(current_zone->start_block);
		current_zone = current_zone->next_zone;
		ft_putchar('\n');
	}
	pthread_mutex_unlock(&g_mutex);
}

void	show_alloc_large_zones(void)
{
	t_zone	*current_zone;

	pthread_mutex_lock(&g_mutex);
	current_zone = (t_zone*)g_start_address;
	while (current_zone)
	{
		if (current_zone->type != LARGE)
		{
			current_zone = current_zone->next_zone;
			continue ;
		}
		ft_putstr("LARGE : ");
		ft_puthex((unsigned int)((void*)current_zone));
		ft_putstr("\n");
		show_block_memory(current_zone->start_block);
		current_zone = current_zone->next_zone;
		ft_putchar('\n');
	}
	pthread_mutex_unlock(&g_mutex);
}

void	show_unused_memory(void)
{
	t_zone	*current_zone;

	pthread_mutex_lock(&g_mutex);
	current_zone = (t_zone*)g_start_address;
	ft_putstr("NOTE:\nIt's shows unused memory for one alloc with malloc func\n"
	"If you want to call malloc more than one time, you need\n"
	"to remember that each allocation additional takes memory\n"
	"for t_block struct\n\n");
	while (current_zone)
	{
		if (current_zone->type == TINY)
			ft_putstr("TINY : ");
		else if (current_zone->type == SMALL)
			ft_putstr("SMALL : ");
		else
			ft_putstr("LARGE : ");
		ft_puthex((unsigned int)((void*)current_zone));
		ft_putstr("\n");
		show_free_memory(current_zone->start_block);
		current_zone = current_zone->next_zone;
		ft_putchar('\n');
	}
	pthread_mutex_unlock(&g_mutex);
}

void	show_free_memory(t_block *block)
{
	void	*last_address;
	void	*start_unused_address;
	t_block	*last_block;

	last_address = block->zone + ((t_zone*)block->zone)->size;
	last_block = block;
	while (last_block->next_block)
	{
		last_block = last_block->next_block;
	}
	if (is_available_space_zone(last_block->zone, 1) != TRUE)
	{
		ft_putstr("It's no unused memory in this zone\n");
		return ;
	}
	start_unused_address = last_block->ptr_data + last_block->data_size +
			sizeof(t_block);
	ft_puthex((unsigned int)start_unused_address);
	ft_putstr(" - ");
	ft_puthex((unsigned int)last_address);
	ft_putstr(" : ");
	ft_putnbr(last_address - start_unused_address);
	ft_putstr(" bytes");
	ft_putstr("\n");
}
