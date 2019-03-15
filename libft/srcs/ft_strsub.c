/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 20:12:25 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/22 18:06:54 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *ss;
	char *r;

	if (!s)
		return (NULL);
	ss = (char*)malloc((len + 1) * sizeof(char));
	if (!ss)
		return (NULL);
	r = ss;
	s += start;
	while (len--)
		*(ss++) = *(s++);
	*ss = '\0';
	return (r);
}
