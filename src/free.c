/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 15:48:30 by lde-moul          #+#    #+#             */
/*   Updated: 2020/01/21 20:43:07 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free(void *ptr)
{
	t_zone	**ptr_zone;
	t_block	**ptr_block;

	if (!ptr)
		return ;
	find_block(block_from_ptr(ptr), &ptr_zone, &ptr_block);
	if (!ptr_block)
		return ;
	remove_block(ptr_zone, ptr_block);
}
