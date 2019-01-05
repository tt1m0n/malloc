/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakovsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:14:30 by omakovsk          #+#    #+#             */
/*   Updated: 2019/01/05 18:14:32 by omakovsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void	*reallocf(void *ptr, size_t size)
{
	void *new_ptr;

	new_ptr = realloc(ptr, size);
	if (!new_ptr)
	{
		free(ptr);
	}
	return (new_ptr);
}
