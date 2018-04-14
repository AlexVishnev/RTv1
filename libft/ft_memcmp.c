/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 09:41:48 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/03 09:41:50 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*buff;
	unsigned char	*buff1;

	buff = (unsigned char *)s1;
	buff1 = (unsigned char *)s2;
	if (s1 == s2 || n == 0)
		return (0);
	while (n--)
	{
		if (*buff != *buff1)
			return (*buff - *buff1);
		if (n)
		{
			buff++;
			buff1++;
		}
	}
	return (0);
}
