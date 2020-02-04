/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:52:35 by lde-moul          #+#    #+#             */
/*   Updated: 2020/02/04 20:56:48 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdalign.h>

static uintptr_t	block_start(void *ptr)
{
	t_block	*block;

	block = align_up(ptr, alignof(t_block));
	return (uintptr_t)align_up(block + 1, ALIGN);
}

size_t				space_after_block(t_zone *zone, t_block *block)
{
	if (block->next)
		return ((uintptr_t)block->next - block_end(block));
	else
		return (zone_end(zone) - block_end(block));
}

int					enough_space_after_block(t_zone *zone, t_block *block,
						size_t size)
{
	uintptr_t	end;

	if (block->next)
		end = (uintptr_t)block->next;
	else
		end = zone_end(zone);
	return (block_start((t_block*)block_end(block)) + size <= end);
}

int					enough_space_at_zone_start(t_zone *zone, size_t size)
{
	uintptr_t	end;

	if (zone->blocks)
		end = (uintptr_t)zone->blocks;
	else
		end = zone_end(zone);
	return (block_start(zone + 1) + size <= end);
}
