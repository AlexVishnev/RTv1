/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:33:36 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/10 19:33:38 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	sizenew(char *str, char c)
{
	size_t	i;

	i = ft_strlen(str);
	while (*str++ != '\0')
	{
		if (*str == c)
			i--;
	}
	return (i);
}

char			*ft_delchr(char *s, char c)
{
	char	*buff;
	size_t	j;
	size_t	a;

	j = 0;
	a = 0;
	if (!(buff = (char *)malloc(sizeof(char) * (sizenew(s, c)))))
		return (NULL);
	while (s[j] != '\0')
	{
		if (s[j] == c && s[j] != '\0')
			j += 1;
		if (s[j] != c)
			buff[a++] = s[j];
		j++;
	}
	buff[j] = '\0';
	return (buff);
}
