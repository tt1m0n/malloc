/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakovsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:14:39 by omakovsk          #+#    #+#             */
/*   Updated: 2019/01/05 18:14:41 by omakovsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void	show_alloc_mem(void)
{
	show_zone_memory();
}

void	show_zone_memory(void)
{
	t_zone	*current_zone;

	pthread_mutex_lock(&g_mutex);
	current_zone = (t_zone*)g_start_address;
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
		show_block_memory(current_zone->start_block);
		current_zone = current_zone->next_zone;
		ft_putchar('\n');
	}
	pthread_mutex_unlock(&g_mutex);
}

void	show_block_memory(t_block *block)
{
	t_block *current_block;

	current_block = block;
	while (current_block)
	{
		ft_puthex((unsigned int)current_block->ptr_data);
		ft_putstr(" - ");
		ft_puthex((unsigned int)(current_block->ptr_data +
		current_block->data_size));
		ft_putstr(" : ");
		ft_putnbr((size_t)current_block->data_size);
		ft_putstr(" bytes");
		ft_putstr("\n");
		current_block = current_block->next_block;
	}
}

void	ft_puthex(unsigned int number)
{
	char	hex_result[8];
	int		hex;
	int		i;

	i = 7;
	fill_zero_ascii(hex_result, 8);
	while (number)
	{
		hex = number % 16;
		if (hex >= 10)
			hex_result[i] = hex + 'A' - 10;
		else
			hex_result[i] = hex + '0';
		number /= 16;
		i--;
	}
	i = 0;
	ft_putstr("0x");
	while (i <= 7)
	{
		ft_putchar(hex_result[i]);
		i++;
	}
}

void	fill_zero_ascii(char *str, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		str[i++] = '0';
	}
}
