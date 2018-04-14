/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:39:23 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/06 14:40:13 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str1, const char *str2)
{
	size_t	len;

	len = ft_strlen(str2);
	if (*str2 != '\0')
	{
		while (ft_strncmp(str1, str2, len) != 0)
		{
			if (*str1 == '\0')
				return (NULL);
			str1++;
		}
	}
	return ((char *)str1);
}
