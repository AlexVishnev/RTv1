/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stprbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:03:06 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/21 15:03:08 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int i;
	int l;

	if (!s2)
		return (NULL);
	l = ft_strlen(s2);
	i = 0;
	while (*s1)
	{
		while (i < l)
		{
			if (s2[i] == *s1)
				return ((char *)s1);
			i++;
		}
		s1++;
	}
	return (NULL);
}
