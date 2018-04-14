/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 14:38:10 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/03 14:38:12 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*buff;
	unsigned char	*buff1;

	buff = (unsigned char *)str1;
	buff1 = (unsigned char *)str2;
	i = -1;
	while ((*buff || *buff1) && ++i < n)
	{
		if (*buff != *buff1)
			return (*buff - *buff1);
		buff++;
		buff1++;
	}
	return (0);
}
