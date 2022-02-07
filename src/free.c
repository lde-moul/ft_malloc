/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 15:48:30 by lde-moul          #+#    #+#             */
/*   Updated: 2022/02/07 18:58:51 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free(void *ptr)
{
	t_zone	**ptr_zone;
	t_block	**ptr_block;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mutex);
	find_ptr(ptr, &ptr_zone, &ptr_block);
	if (ptr_block)
		remove_block(ptr_zone, ptr_block);
	pthread_mutex_unlock(&g_mutex);
}
