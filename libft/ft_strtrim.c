/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 18:47:47 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/04 18:47:48 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char		*ft_strtrim(char const *s)
{
	unsigned int	i;
	size_t			len;
	char			*buff;

	if (!s)
		return (0);
	i = 0;
	while (space(s[i]))
		i++;
	len = ft_strlen(s) - 1;
	while (len > i && space(s[len]))
		len--;
	if (len < i)
		return (buff = ft_strdup(""));
	return (buff = ft_strsub(s, i, len - (size_t)i + 1));
}
