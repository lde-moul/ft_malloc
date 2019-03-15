/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:46:16 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/22 18:07:18 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_fields(char const *s, char c)
{
	size_t n;

	n = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		n++;
		while (*s != c && *s)
			s++;
		while (*s == c)
			s++;
	}
	return (n);
}

static size_t	count_chars(char const *s, char c)
{
	size_t n;

	n = 0;
	while (*s != c && *s)
	{
		n++;
		s++;
	}
	return (n);
}

static char		*add_field(char **t, size_t i, char const *s, char c)
{
	size_t	n;
	char	*tmp;

	n = count_chars(s, c);
	t[i] = (char*)malloc((n + 1) * sizeof(char));
	if (!t[i])
	{
		while (i--)
			free(t[i]);
		free(t);
		return (NULL);
	}
	tmp = t[i];
	while (n--)
		*(tmp++) = *(s++);
	*tmp = '\0';
	return ((char*)s);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**t;
	size_t	fields;
	size_t	i;

	if (!s)
		return (NULL);
	fields = count_fields(s, c);
	t = (char**)malloc((fields + 1) * sizeof(char*));
	if (!t)
		return (NULL);
	i = 0;
	while (fields--)
	{
		while (*s == c)
			s++;
		s = add_field(t, i, s, c);
		if (!s)
			return (NULL);
		i++;
	}
	t[i] = NULL;
	return (t);
}
