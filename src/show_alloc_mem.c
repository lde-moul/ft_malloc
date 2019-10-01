/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:37:05 by lde-moul          #+#    #+#             */
/*   Updated: 2019/09/18 19:20:29 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

static void	print_number(uintptr_t n, int base)
{
	uintptr_t	m;
	char		s[32];
	int			digit;
	int			i;

	m = 1;
	while (m <= n / base)
		m *= base;
	i = 0;
	while (m)
	{
		digit = n / m;
		s[i++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
		n %= m;
		m /= base;
	}
	write(1, s, i);
}

static void	print_zone(t_zone *zone)
{
	if (zone->type == 0)
		write(1, "TINY : 0x", 9);
	else if (zone->type == 1)
		write(1, "SMALL : 0x", 10);
	else
		write(1, "LARGE : 0x", 10);
	print_number((uintptr_t)zone, 16);
	write(1, "\n", 1);
}

static void	print_block(t_block *block)
{
	write(1, "0x", 2);
	print_number((uintptr_t)block, 16);
	write(1, " - 0x", 5);
	print_number(block_end(block), 16);
	write(1, " : ", 3);
	print_number(block->size, 10);
	write(1, " octets\n", 8);
}

void		show_alloc_mem(void)
{
	t_zone	*zone;
	t_block	*block;

	zone = g_zones;
	while (zone)
	{
		print_zone(zone);
		block = zone->blocks;
		while (block)
		{
			print_block(block);
			block = block->next;
		}
		zone = zone->next;
	}
}
