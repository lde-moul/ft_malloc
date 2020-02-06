/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:17:26 by lde-moul          #+#    #+#             */
/*   Updated: 2020/02/06 19:15:12 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*unlock_and_return(void *ptr)
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

static void		move_content_to_new_location(void *old_ptr, void *new_ptr,
	size_t old_size, size_t new_size)
{
	int	i;
	int	n;

	n = new_size > old_size ? old_size : new_size;
	i = 0;
	while (i < n)
	{
		((char*)new_ptr)[i] = ((char*)old_ptr)[i];
		i++;
	}
}

static int		try_simple_cases(void *ptr, size_t size, void **ptr_new_ptr)
{
	t_block	*block;

	if (!ptr)
	{
		*ptr_new_ptr = base_malloc(size);
		return (1);
	}
	block = block_from_ptr(ptr);
	*ptr_new_ptr = ptr;
	return (size <= block->size
		|| (block->next && size <= (uintptr_t)block->next - block_end(block)));
}

void			*realloc(void *ptr, size_t size)
{
	t_zone	**ptr_zone;
	t_block	**ptr_block;
	void	*new_ptr;

	pthread_mutex_lock(&g_mutex);
	if (try_simple_cases(ptr, size, &new_ptr))
		return (unlock_and_return(new_ptr));
	find_block(block_from_ptr(ptr), &ptr_zone, &ptr_block);
	if (!ptr_block)
		return (unlock_and_return(NULL));
	else if ((*ptr_block)->size + space_after_block(*ptr_zone, *ptr_block)
		>= size && size)
	{
		(*ptr_block)->size = size;
		return (unlock_and_return(ptr));
	}
	else
	{
		new_ptr = base_malloc(size);
		if (!new_ptr)
			return (unlock_and_return(NULL));
		move_content_to_new_location(ptr, new_ptr, (*ptr_block)->size, size);
		remove_block(ptr_zone, ptr_block);
		return (unlock_and_return(new_ptr));
	}
}
