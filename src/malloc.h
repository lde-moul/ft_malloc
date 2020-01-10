/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:33:36 by lde-moul          #+#    #+#             */
/*   Updated: 2020/01/10 18:35:37 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# include <stdint.h>

# define TINY	64
# define SMALL	1024

typedef struct	s_block
{
	struct s_block	*next;
	size_t			size;
}				t_block;

typedef struct	s_zone
{
	struct s_zone	*next;
	t_block			*blocks;
	size_t			size;
	int				type;
}				t_zone;

extern t_zone	*g_zones;

void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			free(void *ptr);
void			show_alloc_mem(void);

uintptr_t		zone_end(t_zone *zone);
uintptr_t		block_end(t_block *block);
size_t			space_after_block(t_zone *zone, t_block *block);
void			find_block(t_block *block_to_find,
					t_zone ***ptr_found_zone, t_block ***ptr_found_block);
void			remove_block(t_zone **ptr_zone, t_block **ptr_block);

#endif
