/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:17:26 by lde-moul          #+#    #+#             */
/*   Updated: 2021/06/23 16:04:49 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*unlock_and_return(void *ptr)
{
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

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

void	*realloc(void *ptr, size_t size)
{
	t_zone	**ptr_zone;
	t_block	**ptr_block;
	void	*new_ptr;

	pthread_mutex_lock(&g_mutex);
	if (!ptr)
		return (unlock_and_return(base_malloc(size)));
	find_block(block_from_ptr(ptr), &ptr_zone, &ptr_block);
	if (!ptr_block)
		return (unlock_and_return(NULL));
	if ((*ptr_block)->size + space_after_block(*ptr_zone, *ptr_block)
		>= size && size)
	{
		(*ptr_block)->size = size;
		return (unlock_and_return(ptr));
	}
	new_ptr = base_malloc(size);
	if (!new_ptr)
		return (unlock_and_return(NULL));
	move_content_to_new_location(ptr, new_ptr, (*ptr_block)->size, size);
	remove_block(ptr_zone, ptr_block);
	return (unlock_and_return(new_ptr));
}
