/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 13:58:02 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/03 13:58:04 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	length;

	if (!*str2)
		return ((char *)str1);
	length = ft_strlen(str2);
	while (*str1 != '\0' && len >= length)
	{
		if (ft_strncmp(str1, str2, length) == 0)
			return ((char *)str1);
		str1++;
		len--;
	}
	return (NULL);
}
