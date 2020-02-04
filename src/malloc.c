/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:56:45 by lde-moul          #+#    #+#             */
/*   Updated: 2020/02/04 20:55:47 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdalign.h>
#include <errno.h>

t_zone	*g_zones;

static void		get_zone_size_and_type(size_t block_size,
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
	*zone_size = (size_t)align_up(((void*)*zone_size), getpagesize());
}

static void		find_free_space(size_t size,
	t_zone **ptr_zone, t_block **ptr_block)
{
	int	zone_type;

	get_zone_size_and_type(size, NULL, &zone_type);
	*ptr_block = NULL;
	*ptr_zone = g_zones;
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

static t_zone	*add_zone(size_t block_size)
{
	t_zone	*new_zone;
	t_zone	**ptr_zone;
	int		zone_type;
	size_t	zone_size;

	get_zone_size_and_type(block_size, &zone_size, &zone_type);
	new_zone = mmap(NULL, zone_size,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (new_zone == MAP_FAILED)
		return (NULL);
	new_zone->blocks = NULL;
	new_zone->size = zone_size - sizeof(t_zone);
	new_zone->type = zone_type;
	ptr_zone = &g_zones;
	while (*ptr_zone && *ptr_zone < new_zone)
		ptr_zone = &((*ptr_zone)->next);
	new_zone->next = *ptr_zone;
	*ptr_zone = new_zone;
	return (new_zone);
}

static t_block	*add_block(size_t size, t_zone *zone, t_block *block)
{
	t_block	*new_block;

	if (block)
	{
		new_block = (t_block*)block_end(block);
		new_block->next = block->next;
		block->next = new_block;
	}
	else
	{
		new_block = (t_block*)(zone + 1);
		new_block->next = zone->blocks;
		zone->blocks = new_block;
	}
	new_block = align_up(new_block, alignof(t_block));
	new_block->size = size;
	return (new_block);
}

void			*malloc(size_t size)
{
	t_zone	*zone;
	t_block	*block;

	zone = NULL;
	block = NULL;
	if (size <= SMALL)
		find_free_space(size, &zone, &block);
	if (!zone)
		zone = add_zone(size);
	if (!zone)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (align_up(add_block(size, zone, block) + 1, ALIGN));
}
