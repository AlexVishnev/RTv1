/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_baxe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 20:14:04 by avishnev          #+#    #+#             */
/*   Updated: 2018/01/17 14:25:09 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_pow(int nb, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (nb * ft_pow(nb, pow - 1));
}

char	*ft_itoa_base(int value, int base)
{
	int		i;
	char	*buff;
	int		sign;

	i = 1;
	sign = 0;
	if (value < 0)
	{
		if (base == 10)
			sign = 1;
		value *= -1;
	}
	while (ft_pow(base, i) - 1 < value)
		i++;
	buff = (char*)malloc(sizeof(buff) * i);
	buff[i + sign] = '\0';
	while (i-- > 0)
	{
		buff[i + sign] = (value % base) + (value % base > 9 ? 'A' - 10 : '0');
		value = value / base;
	}
	if (sign)
		buff[0] = '-';
	return (buff);
}
