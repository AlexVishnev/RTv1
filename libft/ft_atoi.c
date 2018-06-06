/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:18:18 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/06 15:18:31 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	rez;

	i = 0;
	sign = 1;
	rez = 0;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\r' || str[i] == '\f'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		rez = (rez * 10) + (str[i] - '0');
		i++;
	}
	if (rez > 9223372036854775807)
		return ((sign == 1) ? -1 : 0);
	return ((int)(rez * sign));
}

unsigned int	ft_u_atoi(const char *str)
{
	int					i;
	unsigned int		rez;

	i = 0;
	rez = 0;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\r' || str[i] == '\f'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		rez = (rez * 10) + (str[i] - '0');
		i++;
	}
	return (rez);
}

#include <stdio.h>
float			ft_atof(char *s, char c)
{
	float	r;
	float	t;
	int		l;
	int		i;
	char	*d;

	l = 0;
	i = -1;
	r = ft_atoi(s);
	if (!(d = ft_strchr(s, '.')))
		return r;
	while (s[++i] != '.' && *s)
		l++;
	t = ft_atoi(ft_strchr(s, '.') + 1) / pow(10, ft_unstrlen(s, c) - l - 1);
	r += t;
	return (r);
}
