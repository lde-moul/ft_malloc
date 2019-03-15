/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 19:53:26 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/21 18:40:48 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *b;

	b = (unsigned char*)s;
	while (n--)
	{
		if (*b == (unsigned char)c)
			return (b);
		b++;
	}
	return (NULL);
}
