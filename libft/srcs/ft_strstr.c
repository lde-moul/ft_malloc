/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 16:47:11 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/19 17:22:31 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *big, const char *little)
{
	char *s1;
	char *s2;

	if (!(*little))
		return ((char*)big);
	while (*big)
	{
		s1 = (char*)big;
		s2 = (char*)little;
		while (*(s1++) == *s2 && *s2)
			s2++;
		if (!(*s2))
			return (char*)big;
		big++;
	}
	return (NULL);
}
