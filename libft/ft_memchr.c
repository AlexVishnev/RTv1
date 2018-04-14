/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 09:40:48 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/03 09:40:50 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	chr;
	unsigned char	*buff;

	chr = (unsigned char)c;
	buff = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (buff[i] == chr)
			return (&buff[i]);
		i++;
	}
	return (NULL);
}
