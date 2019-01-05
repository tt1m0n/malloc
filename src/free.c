/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakovsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:13:34 by omakovsk          #+#    #+#             */
/*   Updated: 2019/01/05 18:13:36 by omakovsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void	free(void *ptr)
{
	t_block	*block;

	pthread_mutex_lock(&g_mutex);
	if (!ptr || !g_start_address)
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	block = (t_block*)(ptr - sizeof(t_block));
	if (is_block_exist(block) == FALSE)
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	if (block->is_free == TRUE)
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	release_block(block);
	pthread_mutex_unlock(&g_mutex);
}

void	release_block(t_block *block)
{
	t_block *next_block;

	next_block = block->next_block;
	block->is_free = TRUE;
	if (block->next_block && next_block->is_free == TRUE)
	{// do not pass test2
	//	block_fusion_free(block);
	}
	if (is_need_release_zone(block->zone) == TRUE)
	{
		release_zone(block->zone);
	}
}

void	block_fusion_free(t_block *block)
{
	t_block *next_block;

	next_block = block->next_block;
	block->data_size = block->data_size + sizeof(t_block) +
			next_block->data_size;
	block->next_block = next_block->next_block;
}
