/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:33:36 by lde-moul          #+#    #+#             */
/*   Updated: 2022/02/07 18:57:31 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# include <stdint.h>
# include <pthread.h>

# define TINY	64
# define SMALL	512

# define ALIGN	16

typedef struct s_block
{
	struct s_block	*next;
	size_t			size;
}				t_block;

typedef struct s_zone
{
	struct s_zone	*next;
	t_block			*blocks;
	size_t			size;
	int				type;
}				t_zone;

typedef struct s_state
{
	t_zone	*zones;
	int		empty_zone_ready[3];
}				t_state;

extern t_state			g_state;
extern pthread_mutex_t	g_mutex;

void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			*calloc(size_t count, size_t size);
void			free(void *ptr);
void			show_alloc_mem(void);

void			*base_malloc(size_t size);
void			find_free_space(size_t size,
					t_zone **ptr_zone, t_block **ptr_block);
uintptr_t		zone_end(t_zone *zone);
void			get_zone_size_and_type(size_t block_size,
					size_t *zone_size, int *zone_type);
void			*align_up(void *ptr, size_t size);
void			*align_down(void *ptr, size_t size);
uintptr_t		block_end(t_block *block);
void			*block_from_ptr(void *ptr);
void			find_ptr(void *ptr_to_find,
					t_zone ***ptr_found_zone, t_block ***ptr_found_block);
void			remove_block(t_zone **ptr_zone, t_block **ptr_block);

#endif
