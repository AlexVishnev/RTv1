/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:59:48 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/06 14:59:50 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *restrict d, const void *restrict s, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*src;
	unsigned char	chr;

	i = 0;
	dest = (unsigned char *)d;
	src = (unsigned char *)s;
	chr = (unsigned char)c;
	while (n > i)
	{
		dest[i] = src[i];
		if (src[i] == chr)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
