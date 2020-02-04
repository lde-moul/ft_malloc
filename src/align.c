/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:55:15 by lde-moul          #+#    #+#             */
/*   Updated: 2020/02/04 20:58:54 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*align_up(void *ptr, size_t size)
{
	return ((void*)(((uintptr_t)ptr + (size - 1)) / size * size));
}

void	*align_down(void *ptr, size_t size)
{
	return (void*)((uintptr_t)ptr / size * size);
}
