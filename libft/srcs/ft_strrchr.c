/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 16:37:37 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/19 16:46:38 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char *r;

	if (!((char)c))
	{
		while (*s)
			s++;
		return ((char*)s);
	}
	r = NULL;
	while (*s)
	{
		if (*s == (char)c)
			r = (char*)s;
		s++;
	}
	return (r);
}
