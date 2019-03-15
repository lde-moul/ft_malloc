/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelfrom.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 19:29:15 by lde-moul          #+#    #+#             */
/*   Updated: 2016/12/07 19:29:17 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelfrom(t_list **lst, t_list **alst, void (*del)(void*, size_t))
{
	t_list *prev;

	if (!alst)
		return ;
	prev = *lst;
	if (prev == *alst)
		*lst = prev->next;
	else
		while (prev->next != *alst)
			prev = prev->next;
	prev->next = (*alst)->next;
	ft_lstdelone(alst, del);
}
