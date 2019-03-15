/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 18:53:39 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/21 18:40:03 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *d;
	unsigned char *s;

	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	if (s < d && s + len - 1 >= d)
	{
		d = d + len - 1;
		s = s + len - 1;
		while (len--)
			*(d--) = *(s--);
	}
	else if (s != d)
	{
		while (len--)
			*(d++) = *(s++);
	}
	return (dst);
}
