/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 19:28:56 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/24 14:02:47 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *newlist;
	t_list *newelem;
	t_list **alst;

	if (!lst || !f)
		return (NULL);
	newlist = NULL;
	alst = &newlist;
	while (lst)
	{
		newelem = f(lst);
		if (!newelem)
			return (NULL);
		if (!newlist)
			newlist = newelem;
		*alst = newelem;
		alst = &newelem->next;
		lst = lst->next;
	}
	newelem->next = NULL;
	return (newlist);
}
