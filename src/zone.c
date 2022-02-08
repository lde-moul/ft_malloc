/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:16:39 by lde-moul          #+#    #+#             */
/*   Updated: 2022/02/08 20:05:39 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

static size_t	get_rounded_size(size_t size)
{
	size += sizeof(t_zone);
	return ((size_t)align_up((void *)size, getpagesize()));
}

static size_t	get_wasted_size(size_t block_size)
{
	size_t	zone_size;

	zone_size = get_rounded_size(block_size) - sizeof(t_zone);
	return (zone_size % block_size);
}

uintptr_t	zone_end(t_zone *zone)
{
	return ((uintptr_t)(zone + 1) + zone->size);
}

void	get_zone_size_and_type(size_t block_size,
	size_t *zone_size, int *zone_type)
{
	if (block_size <= TINY)
		*zone_type = 0;
	else if (block_size <= SMALL)
		*zone_type = 1;
	else
		*zone_type = 2;
	if (!zone_size)
		return ;
	if (*zone_type == 0)
		*zone_size = 100 * (TINY + sizeof(t_block));
	else if (*zone_type == 1)
		*zone_size = 100 * (SMALL + sizeof(t_block));
	else
	{
		*zone_size = block_size + sizeof(t_block);
		if (16 * get_wasted_size(*zone_size) > get_rounded_size(*zone_size))
			*zone_size *= 16;
	}
	*zone_size = get_rounded_size(*zone_size);
}
