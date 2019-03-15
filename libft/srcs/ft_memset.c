/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:38:34 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/21 18:41:38 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*t;
	unsigned char	v;

	t = (unsigned char*)b;
	v = (unsigned char)c;
	while (len--)
		*(t++) = v;
	return (b);
}
