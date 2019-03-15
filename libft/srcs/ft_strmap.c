/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 19:45:03 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/22 18:05:47 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *ns;
	char *r;

	if (!s)
		return (NULL);
	ns = (char*)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ns)
		return (NULL);
	r = ns;
	while (*s)
		*(ns++) = f(*(s++));
	*ns = '\0';
	return (r);
}
