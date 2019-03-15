/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 20:18:58 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/19 18:57:06 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char		*s2;
	const char	*s3;
	size_t		n;

	n = 1;
	s3 = s1;
	while (*(s3++))
		n++;
	s2 = (char*)malloc(n);
	if (!s2)
		return (NULL);
	ft_strcpy(s2, s1);
	return (s2);
}
