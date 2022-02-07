/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:17:26 by lde-moul          #+#    #+#             */
/*   Updated: 2022/02/07 19:27:55 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	space_after_block(t_zone *zone, t_block *block)
{
	if (block->next)
		return ((uintptr_t)block->next - block_end(block));
	else
		return (zone_end(zone) - block_end(block));
}

static void	move_content_to_new_location(void *old_ptr, void *new_ptr,
	size_t old_size, size_t new_size)
{
	size_t	i;
	size_t	n;

	if (new_size > old_size)
		n = old_size;
	else
		n = new_size;
	i = 0;
	while (i < n)
	{
		((char *)new_ptr)[i] = ((char *)old_ptr)[i];
		i++;
	}
}

static void	*base_realloc(void *ptr, size_t size)
{
	t_zone	**ptr_zone;
	t_block	**ptr_block;
	void	*new_ptr;

	if (!ptr)
		return (base_malloc(size));
	find_ptr(ptr, &ptr_zone, &ptr_block);
	if (!ptr_block)
		return (NULL);
	if ((*ptr_block)->size + space_after_block(*ptr_zone, *ptr_block)
		>= size && size)
	{
		(*ptr_block)->size = size;
		return (ptr);
	}
	new_ptr = base_malloc(size);
	if (!new_ptr)
		return (NULL);
	move_content_to_new_location(ptr, new_ptr, (*ptr_block)->size, size);
	remove_block(ptr_zone, ptr_block);
	return (new_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	pthread_mutex_lock(&g_mutex);
	ptr = base_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
