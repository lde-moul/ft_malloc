/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:19:14 by lde-moul          #+#    #+#             */
/*   Updated: 2019/09/17 19:23:41 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

uintptr_t	zone_end(t_zone *zone)
{
	return ((uintptr_t)(zone + 1) + zone->size);
}

uintptr_t	block_end(t_block *block)
{
	return ((uintptr_t)(block + 1) + block->size);
}

int			enough_space_after_block(t_zone *zone, t_block *block, size_t size)
{
	if (block->next)
		return ((uintptr_t)block->next - block_end(block) >= size);
	else
		return (zone_end(zone) - block_end(block) >= size);
}

void		find_block(t_block *block_to_find,
	t_zone ***ptr_found_zone, t_block ***ptr_found_block)
{
	t_zone	**ptr_zone;
	t_block	**ptr_block;

	ptr_zone = &g_zones;
	while (*ptr_zone)
	{
		if ((t_block*)*ptr_zone < block_to_find
			&& (t_block*)zone_end(*ptr_zone) > block_to_find)
		{
			ptr_block = &((*ptr_zone)->blocks);
			while (*ptr_block)
			{
				if (*ptr_block == block_to_find)
				{
					*ptr_found_zone = ptr_zone;
					*ptr_found_block = ptr_block;
					return ;
				}
				ptr_block = &((*ptr_block)->next);
			}
		}
		ptr_zone = &((*ptr_zone)->next);
	}
}

void		remove_block(t_zone **ptr_zone, t_block **ptr_block)
{
	t_zone	*zone;

	zone = *ptr_zone;
	*ptr_block = (*ptr_block)->next;
	if (!zone->blocks)
	{
		*ptr_zone = zone->next;
		munmap(zone, sizeof(t_zone) + zone->size);
	}
}
