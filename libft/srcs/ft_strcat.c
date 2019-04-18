/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 14:55:32 by lde-moul          #+#    #+#             */
/*   Updated: 2016/11/19 15:02:51 by lde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *s1, const char *s2)
{
	char *s3;

	s3 = s1;
	while (*s3)
		s3++;
	while (*s2)
		*(s3++) = *(s2++);
	*s3 = '\0';
	return (s1);
}