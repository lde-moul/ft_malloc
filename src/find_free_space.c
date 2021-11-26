/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_free_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:07:11 by lde-moul          #+#    #+#             */
/*   Updated: 2020/02/06 18:09:31 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdalign.h>

static uintptr_t	block_start(void *ptr)
{
	t_block	*block;

	block = align_up(ptr, alignof(t_block));
	return ((uintptr_t)align_up(block + 1, ALIGN));
}

static int	enough_space_after_block(t_zone *zone, t_block *block,
						size_t size)
{
	uintptr_t	end;

	if (block->next)
		end = (uintptr_t)block->next;
	else
		end = zone_end(zone);
	return (block_start((t_block *)block_end(block)) + size <= end);
}

static int	enough_space_at_zone_start(t_zone *zone, size_t size)
{
	uintptr_t	end;

	if (zone->blocks)
		end = (uintptr_t)zone->blocks;
	else
		end = zone_end(zone);
	return (block_start(zone + 1) + size <= end);
}

void	find_free_space(size_t size,
	t_zone **ptr_zone, t_block **ptr_block)
{
	int	zone_type;

	get_zone_size_and_type(size, NULL, &zone_type);
	*ptr_block = NULL;
	*ptr_zone = g_state.zones;
	while (*ptr_zone)
	{
		if ((*ptr_zone)->type == zone_type)
		{
			if (enough_space_at_zone_start(*ptr_zone, size))
				return ;
			*ptr_block = (*ptr_zone)->blocks;
			while (*ptr_block)
			{
				if (enough_space_after_block(*ptr_zone, *ptr_block, size))
					return ;
				*ptr_block = (*ptr_block)->next;
			}
		}
		*ptr_zone = (*ptr_zone)->next;
	}
	return ;
}
