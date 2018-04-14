/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:35:29 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/04 17:35:32 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buff;
	int		len;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len = (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	i = 0;
	if (!(buff = (char*)malloc(sizeof(char) * (len))))
		return (NULL);
	if (buff)
	{
		while (*s1)
			buff[i++] = *s1++;
		while (*s2)
			buff[i++] = *s2++;
		buff[i] = '\0';
		return (buff);
	}
	return (NULL);
}
