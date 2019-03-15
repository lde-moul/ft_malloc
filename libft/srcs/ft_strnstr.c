/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 17:27:54 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/19 17:45:32 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*s1;
	char	*s2;
	size_t	l;

	if (!(*little))
		return ((char*)big);
	while (*big && len)
	{
		s1 = (char*)big;
		s2 = (char*)little;
		l = len;
		while (*(s1++) == *s2 && *s2 && l--)
			s2++;
		if (!(*s2))
			return (char*)big;
		big++;
		len--;
	}
	return (NULL);
}
