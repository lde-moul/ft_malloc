/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 20:23:06 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/22 18:08:45 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *ns;
	char *r;

	if (!s1 || !s2)
		return (NULL);
	ns = (char*)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ns)
		return (NULL);
	r = ns;
	while (*s1)
		*(ns++) = *(s1++);
	while (*s2)
		*(ns++) = *(s2++);
	*ns = '\0';
	return (r);
}
