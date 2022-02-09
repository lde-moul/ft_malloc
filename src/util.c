/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:19:14 by lde-moul          #+#    #+#             */
/*   Updated: 2022/02/09 19:16:51 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>
#include <stdalign.h>

uintptr_t	block_end(t_block *block)
{
	return ((uintptr_t)align_up(block + 1, ALIGN) + block->size);
}

void	*block_from_ptr(void *ptr)
{
	return (align_down((t_block *)ptr - 1, alignof(t_block)));
}

void	find_ptr(void *ptr_to_find,
	t_zone ***ptr_found_zone, t_block ***ptr_found_block)
{
	t_zone	**ptr_zone;
	t_block	**ptr_block;

	ptr_zone = &g_state.zones;
	while (*ptr_zone)
	{
		if ((void *)*ptr_zone < ptr_to_find
			&& (void*)zone_end(*ptr_zone) > ptr_to_find)
		{
			ptr_block = &((*ptr_zone)->blocks);
			while (*ptr_block)
			{
				if (align_up(*ptr_block + 1, ALIGN) == ptr_to_find)
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

void	remove_block(t_zone **ptr_zone, t_block **ptr_block)
{
	t_zone	*zone;

	zone = *ptr_zone;
	*ptr_block = (*ptr_block)->next;
	if (!zone->blocks)
	{
		if (g_state.empty_zone_ready[zone->type])
		{
			*ptr_zone = zone->next;
			munmap(zone, sizeof(t_zone) + zone->size);
		}
		else
			g_state.empty_zone_ready[zone->type] = 1;
	}
}
