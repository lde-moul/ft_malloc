/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 15:48:30 by lde-moul          #+#    #+#             */
/*   Updated: 2019/10/01 19:45:21 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free(void *ptr)
{
	t_zone	**ptr_zone;
	t_block	**ptr_block;

	if (!ptr)
		return ;
	find_block((t_block*)ptr - 1, &ptr_zone, &ptr_block);
	if (!ptr_block)
		return ;
	remove_block(ptr_zone, ptr_block);
}
