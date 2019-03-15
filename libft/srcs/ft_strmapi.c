/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 20:02:27 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/22 18:05:56 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ns;
	char			*r;
	unsigned int	i;

	if (!s)
		return (NULL);
	ns = (char*)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ns)
		return (NULL);
	r = ns;
	i = 0;
	while (*s)
		*(ns++) = f(i++, *(s++));
	*ns = '\0';
	return (r);
}
