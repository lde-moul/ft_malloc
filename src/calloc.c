/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:15:31 by lde-moul          #+#    #+#             */
/*   Updated: 2021/11/29 16:23:02 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	fill_with_zeroes(void *ptr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
}

void	*calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!(count && size && count <= SIZE_MAX / size))
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	ptr = base_malloc(count * size);
	if (ptr)
		fill_with_zeroes(ptr, count * size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
