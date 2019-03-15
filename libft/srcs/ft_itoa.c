/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:45:40 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/21 17:36:47 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	init(int n, int *i, size_t *len)
{
	if (n >= 0)
	{
		*i = 1;
		*len = 1;
		while (*i <= n / 10)
		{
			*i *= 10;
			(*len)++;
		}
	}
	else
	{
		*i = -1;
		*len = 2;
		while (*i >= n / 10)
		{
			*i *= 10;
			(*len)++;
		}
	}
}

char		*ft_itoa(int n)
{
	char	*s;
	int		i;
	size_t	len;

	init(n, &i, &len);
	s = (char*)malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	if (n < 0)
		*(s++) = '-';
	while (i)
	{
		*(s++) = n / i + '0';
		n %= i;
		i /= 10;
	}
	*s = '\0';
	return (s - len);
}
