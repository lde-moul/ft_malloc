/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:56:45 by lde-moul          #+#    #+#             */
/*   Updated: 2021/12/13 19:09:49 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>
#include <stdalign.h>
#include <errno.h>

t_state			g_state;
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

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
	ptr_zone = &g_state.zones;
	while (*ptr_zone && *ptr_zone < new_zone)
		ptr_zone = &((*ptr_zone)->next);
	new_zone->next = *ptr_zone;
	*ptr_zone = new_zone;
	return (new_zone);
}

static t_block	*add_block(size_t size, t_zone *zone, t_block *block)
{
	t_block	*new_block;

	if (!zone->blocks && zone->type < 2)
		g_state.empty_zone_ready[zone->type] = 0;
	if (block)
	{
		new_block = (t_block *)block_end(block);
		new_block = align_up(new_block, alignof(t_block));
		new_block->next = block->next;
		block->next = new_block;
	}
	else
	{
		new_block = (t_block *)(zone + 1);
		new_block = align_up(new_block, alignof(t_block));
		new_block->next = zone->blocks;
		zone->blocks = new_block;
	}
	new_block->size = size;
	return (new_block);
}

void	*base_malloc(size_t size)
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

void	*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = base_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
