/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:16:39 by lde-moul          #+#    #+#             */
/*   Updated: 2020/02/06 18:18:22 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

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
	if (*zone_type == TINY)
		*zone_size = 100 * (TINY + sizeof(t_block));
	else if (*zone_type == SMALL)
		*zone_size = 100 * (SMALL + sizeof(t_block));
	else
		*zone_size = block_size + sizeof(t_block);
	*zone_size += sizeof(t_zone);
	*zone_size = (size_t)align_up(((void *)*zone_size), getpagesize());
}
