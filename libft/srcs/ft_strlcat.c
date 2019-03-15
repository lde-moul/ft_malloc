/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 15:07:09 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/22 15:35:58 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	n;

	n = 0;
	while (*dst && n + 1 < size)
	{
		dst++;
		n++;
	}
	if (*dst)
	{
		while (*(src++))
			size++;
		return (size);
	}
	while (*src && n + 1 < size)
	{
		*(dst++) = *(src++);
		n++;
	}
	*dst = '\0';
	while (*(src++))
		n++;
	return (n);
}
