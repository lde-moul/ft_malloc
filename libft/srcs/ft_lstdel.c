/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 19:08:47 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/24 14:23:16 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *elem;
	t_list *next;

	if (!alst)
		return ;
	elem = *alst;
	if (del)
		while (elem)
		{
			next = elem->next;
			del(elem->content, elem->content_size);
			free(elem);
			elem = next;
		}
	else
		while (elem)
		{
			next = elem->next;
			free(elem->content);
			free(elem);
			elem = next;
		}
	*alst = NULL;
}
