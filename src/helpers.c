/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakovsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:13:57 by omakovsk          #+#    #+#             */
/*   Updated: 2019/01/05 18:14:00 by omakovsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

char	get_block_type(size_t data_size)
{
	if (data_size <= TINY_BLOCK)
	{
		return (TINY);
	}
	else if (data_size <= SMALL_BLOCK)
	{
		return (SMALL);
	}
	else
	{
		return (LARGE);
	}
}
