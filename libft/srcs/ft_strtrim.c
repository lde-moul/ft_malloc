/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 20:37:57 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/22 18:03:01 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*trim_end(char const *s)
{
	while (*s)
		s++;
	s--;
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s--;
	return ((char*)s);
}

char		*ft_strtrim(char const *s)
{
	char	*ts;
	char	*start;
	char	*tmp;
	size_t	len;

	if (!s)
		return (NULL);
	start = (char*)s;
	while (*start == ' ' || *start == '\n' || *start == '\t')
		start++;
	if (*start)
		len = trim_end(start) - start + 1;
	else
		len = 0;
	ts = (char*)malloc((len + 1) * sizeof(char));
	if (!ts)
		return (NULL);
	tmp = ts;
	while (len--)
		*(ts++) = *(start++);
	*ts = '\0';
	return (tmp);
}
