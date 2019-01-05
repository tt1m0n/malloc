/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakovsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:13:27 by omakovsk          #+#    #+#             */
/*   Updated: 2019/01/05 18:19:33 by omakovsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void	*calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	allocation_size;

	allocation_size = count * size;
	ptr = (char*)malloc(allocation_size);
	if (ptr)
	{
		ft_bzero(ptr, allocation_size);
	}
	return (ptr);
}
