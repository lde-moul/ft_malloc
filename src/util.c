/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:19:14 by lde-moul          #+#    #+#             */
/*   Updated: 2020/01/10 18:35:50 by lde-moul         ###   ########.fr       */
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

size_t		space_after_block(t_zone *zone, t_block *block)
{
	if (block->next)
		return ((uintptr_t)block->next - block_end(block));
	else
		return (zone_end(zone) - block_end(block));
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
	*ptr_found_zone = NULL;
	*ptr_found_block = NULL;
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
