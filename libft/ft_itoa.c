/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 10:32:57 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/06 10:32:59 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isneg(int n)
{
	return ((n < 0) ? -n : n);
}

static int	sizeofstr(int n)
{
	int	size;

	size = (n <= 0) ? 1 : 0;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(int n)
{
	char	*buff;
	int		sign;
	int		size;

	sign = (n < 0) ? -1 : 1;
	size = sizeofstr(n);
	buff = (char *)malloc(sizeof(char) * (size + 1));
	if (buff == NULL)
		return (NULL);
	buff[size] = '\0';
	size--;
	while (size >= 0)
	{
		buff[size] = '0' + isneg(n % 10);
		n = isneg(n / 10);
		size--;
	}
	if (sign == -1)
		buff[0] = '-';
	return (buff);
}
