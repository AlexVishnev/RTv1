/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:07:01 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/04 20:07:02 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*find_word_end(const char *s, char c)
{
	char	*len;

	len = ft_strchr(s, c);
	if (len)
		return (len);
	return (ft_strchr(s, '\0'));
}

static char		*nxtword(const char **s, char c)
{
	char	*next;
	size_t	lenh;
	size_t	i;

	while (**s == c)
		(*s)++;
	lenh = find_word_end(*s, c) - *s;
	if (!(next = ft_memalloc(lenh + 1)))
		return (NULL);
	i = 0;
	while (i < lenh)
	{
		next[i] = (*s)[i];
		i++;
	}
	*s += lenh + 1;
	return (next);
}

static size_t	cword(const char *s, char c)
{
	size_t	cwrd;
	int		i;

	i = 0;
	cwrd = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		cwrd++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (cwrd);
}

char			**ft_strsplit(const char *s, char c)
{
	char	**buff;
	size_t	nbr;
	size_t	i;

	if (!s)
		return (NULL);
	nbr = cword(s, c);
	if (!(buff = (char **)malloc(sizeof(char*) * (nbr + 2))))
		return (NULL);
	i = 0;
	while (i < nbr)
	{
		buff[i] = nxtword(&s, c);
		if (buff[i] == NULL)
			return (NULL);
		i++;
	}
	buff[i] = NULL;
	return (buff);
}
