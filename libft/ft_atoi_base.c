/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:11:16 by avishnev          #+#    #+#             */
/*   Updated: 2018/01/17 14:23:28 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_in_base(char c, int base, char let)
{
	if (base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= let && c <= (let + base - 10)));
}

static	int	up_low(char *str, int base)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'A' + base)
			return (1);
		if (str[i] >= 'a' && str[i] <= 'a' + base)
			return (0);
		i++;
	}
	return (1);
}

int			ft_atoi_base(char *str, int base)
{
	int		value;
	int		sign;
	char	chr;

	value = 0;
	if (base < 2 || base > 16)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
			|| *str == '\r' || *str == '\v')
		str++;
	sign = (*str == '-') ? -1 : 1;
	chr = up_low(str, base) ? 'A' : 'a';
	if (*str == '-' || *str == '+')
		str++;
	if (base == 16 && *str == '0' && ft_tolower(*(str + 1)) == 'x')
		str += 2;
	while (check_in_base(*str, base, chr))
	{
		if (*str - chr >= 0)
			value = value * base + (*str - chr + 10);
		else
			value = value * base + (*str - '0');
		str++;
	}
	return (value * sign);
}
