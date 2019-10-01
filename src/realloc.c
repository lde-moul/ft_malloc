/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:17:26 by lde-moul          #+#    #+#             */
/*   Updated: 2019/09/17 19:22:36 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	move_content_to_new_location(void *old_ptr, void *new_ptr,
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

void		*realloc(void *ptr, size_t size)
{
	t_zone	**ptr_zone;
	t_block	**ptr_block;
	void	*new_ptr;

	find_block((t_block*)ptr - 1, &ptr_zone, &ptr_block); // !!!
	if (enough_space_after_block(*ptr_zone, *ptr_block,
		size - (*ptr_block)->size))
	{
		(*ptr_block)->size = size;
		return (ptr);
	}
	else
	{
		new_ptr = malloc(size); // !!!
		move_content_to_new_location(ptr, new_ptr, (*ptr_block)->size, size);
		remove_block(ptr_zone, ptr_block);
		return (new_ptr);
	}
}
